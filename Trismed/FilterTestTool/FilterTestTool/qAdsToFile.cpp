#include "qAdsToFile.h"
#include <QFile>
#include <QDateTime>
#include <QDebug>

static const QString head = "ECG_ADS";

qAdsToFile::qAdsToFile(QObject *parent) :
    QObject(parent)
{
    m_resolution = 0;
    m_numSamples = 0;
    if(parent != nullptr) {
        connect(static_cast<qAcq_Ads1298*>(parent), SIGNAL(sNewSamples()), this, SLOT(onNewSamples()));
    }
    samplesQueue = new FastQueue<Raw_Tx_t>(100);
    QDateTime now = QDateTime::currentDateTime();
    QString fileName = QString("%1.AdsRaw").arg(now.toString("ddMMyyyy-hhmmss"));
    m_file = new QFile(fileName);
    m_file->open(QIODevice::OpenModeFlag::WriteOnly);
    m_file->write(head.toLatin1().constData(), head.length());
    m_file->write(reinterpret_cast<char*>(&m_resolution), sizeof(double));
    m_file->write(reinterpret_cast<char*>(&m_numSamples), sizeof(int64_t));
}

qAdsToFile::~qAdsToFile()
{
    delete samplesQueue;
    m_file->seek(sizeof(double)+head.length());
    m_file->write(reinterpret_cast<char*>(&m_numSamples), sizeof(int64_t));
    m_file->close();
    delete m_file;
}

bool qAdsToFile::Load(QString fileName)
{
    samples.clear();
    QFile file(fileName);
    file.open(QIODevice::OpenModeFlag::ReadOnly);
    if(file.isOpen()) {
        char lhead[8]={0};
        file.read(lhead, head.length());
        if(head.contains(lhead)) {
            file.read(reinterpret_cast<char*>(&m_resolution), sizeof(double));
            m_resolution = 2.8612E-04;
            int64_t numSamples;
            file.read(reinterpret_cast<char*>(&numSamples), sizeof(int64_t));
            Raw_Tx_t sample;
            for(int64_t i=0; i<numSamples; i++) {
                file.read(reinterpret_cast<char*>(&sample), sizeof(Raw_Tx_t));
                samples.push_back(sample);
            }
            return true;
        } else {
            qDebug() << "wrong file format";
        }
    } else
        qDebug() << "File not found";
    return false;
}

QVector<int32_t> qAdsToFile::GetLead(int lead)
{
    QVector<int32_t> leadVector;
    foreach(Raw_Tx_t sample, samples) {
        leadVector.push_back(sample.frame.Leads[lead]);
    }
    return leadVector;
}

double qAdsToFile::GetResolution()
{
    return m_resolution;
}

int qAdsToFile::SamplesCount()
{
    return samples.count();
}

/** ADS1298_Status (uint32_t only bits 0-23 are used)
*  1 => electrode is off, 0 => electrode connected
*  bits  23                                                            0
*       +---------------------------------------------------------------+
*       | 1 | 1 | 0 | 0 | LOFF_STATP[7:0] | LOFF_STATN[7:0] | GPIO[7:4] |
*       +---------------------------------------------------------------+
*/
#define ADS_V6  0x080000u
#define ADS_V5  0x040000u
#define ADS_V4  0x020000u
#define ADS_V3  0x010000u
#define ADS_V2  0x008000u
#define ADS_V1  0x004000u
#define ADS_LL  0x002000u
#define ADS_LA  0x001000u
#define ADS_RA  0x000010u

#define MASK_SOME_ELECTRODE_OFF (ADS_V6 | ADS_V5 | ADS_V4 | ADS_V3 | ADS_V2 | ADS_V1 | ADS_LL | ADS_LA | ADS_RA)

/** Extra (uint16_t) format
*   +-----------------------------------------------------+
*   | LF | 0  | 0  | 0  | PCM_POL | PM | CABLEOFF | eFail |     LSB
*   +----+----+----+----+---------+----+----------+-------+
*   | V6 | V5 | V4 | V3 | V2      | V1 | LA       | RA    |     MSB
*   +-----------------------------------------------------+
*   Note: In Cardipia CABLEOFF bit is not used and the eFail bit is used as
*   CableOff detection.
*/
#define V6 0x8000u   /* 1 => ok, 0 => fail */
#define V5 0x4000u   /* 1 => ok, 0 => fail */
#define V4 0x2000u   /* 1 => ok, 0 => fail */
#define V3 0x1000u   /* 1 => ok, 0 => fail */
#define V2 0x0800u   /* 1 => ok, 0 => fail */
#define V1 0x0400u   /* 1 => ok, 0 => fail */
#define LA 0x0200u   /* 1 => ok, 0 => fail */
#define RA 0x0100u   /* 1 => ok, 0 => fail */
#define LF 0x0080u   /* 1 => ok, 0 => fail */

static uint16_t ADS1298Status_To_Extra(uint32_t Status) {
    uint16_t extra = 0xff40;
    if(Status & ADS_V6) extra &= (~V6);
    if(Status & ADS_V5) extra &= (~V5);
    if(Status & ADS_V4) extra &= (~V4);
    if(Status & ADS_V3) extra &= (~V3);
    if(Status & ADS_V2) extra &= (~V2);
    if(Status & ADS_V1) extra &= (~V1);
    if(Status & ADS_LL) extra &= (~LF);
    if(Status & ADS_LA) extra &= (~LA);
    if(Status & ADS_RA) extra &= (~RA);
    return extra;
}

leadoffChange qAdsToFile::GetNextElectrodeChangeIndex(int currentIndex)
{
    leadoffChange extraChange;
    if(currentIndex < 0) {
        extraChange.extra = ADS1298Status_To_Extra(samples.at(0).frame.Status);
        extraChange.index = 0;
    } else {
        uint32_t currentStatus = samples.at(currentIndex).frame.Status & MASK_SOME_ELECTRODE_OFF;
        uint32_t extra;
        for(int i = currentIndex; i < samples.count(); i++) {
            extra = samples.at(i).frame.Status & MASK_SOME_ELECTRODE_OFF;
            if(currentStatus != extra) {
                extraChange.extra = ADS1298Status_To_Extra(samples.at(currentIndex).frame.Status);
                extraChange.index = i;
                return extraChange;
            }
        }
        extraChange.index = -1;
    }
    return extraChange;
}

void qAdsToFile::onNewSamples()
{
    Raw_Tx_t *buffer;
    samplesQueue->lock();
    uint32_t items = static_cast<uint32_t>(samplesQueue->size());
    if(items > 0) {
        m_numSamples += items;
        buffer = new Raw_Tx_t[items];
        samplesQueue->popAll(buffer);
        m_file->write(reinterpret_cast<char*>(buffer), items*sizeof(Raw_Tx_t));
        delete [] buffer;
    }
    samplesQueue->unlock();
}

