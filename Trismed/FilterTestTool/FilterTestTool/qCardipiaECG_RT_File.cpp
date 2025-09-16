#include "qCardipiaECG_RT_File.h"
#include <QDebug>
#include <QDateTime>

const QString head = "ECGTR";
#ifdef CARDIPIA
extern float AMP_RESOLUTION;
#else
static double AMP_RESOLUTION = 0.002686203 / 4;
#endif

QDebug operator<< (QDebug d, const leadoffChange &loff) {
    d << "[" << loff.index << ", " << "0x" << QString::number(loff.extra, 16).toLatin1().constData() << "]";
    return d;
}

qCardipiaECG_RT_File::qCardipiaECG_RT_File(QObject *parent) : QObject(parent)
{
    m_resolution = AMP_RESOLUTION;
}

void qCardipiaECG_RT_File::Save(QString fileName)
{
    if(fileName.isEmpty()) {
        QDateTime now = QDateTime::currentDateTime();
        fileName = now.toString("ddMMyyyy-hhmmss");
    }
    if(!fileName.contains(".ecgrt")) {
        fileName += ".ecgrt";
    }
    QFile file(fileName);
    file.open(QIODevice::OpenModeFlag::WriteOnly);
    file.write(head.toLatin1().constData(), head.length());
    file.write(reinterpret_cast<char*>(&m_resolution), sizeof(double));
    int64_t numSamples = samples.count();
    file.write(reinterpret_cast<char*>(&numSamples), sizeof(int64_t));
    foreach(ampsample sample, samples) {
        file.write(reinterpret_cast<char*>(&sample), sizeof(ampsample));
    }
    file.close();
}

bool qCardipiaECG_RT_File::Load(QString fileName)
{
    samples.clear();
    QFile file(fileName);
    file.open(QIODevice::OpenModeFlag::ReadOnly);
    if(file.isOpen()) {
        char lhead[6]={0};
        file.read(lhead, head.length());
        if(head.contains(lhead)) {
            file.read(reinterpret_cast<char*>(&m_resolution), sizeof(double));
            int64_t numSamples;
            file.read(reinterpret_cast<char*>(&numSamples), sizeof(int64_t));
            ampsample sample;
            for(int64_t i=0; i<numSamples; i++) {
                file.read(reinterpret_cast<char*>(&sample), sizeof(ampsample));
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

void qCardipiaECG_RT_File::AddSample(ampsample sample)
{
    samples.push_back(sample);
}

QVector<int32_t> qCardipiaECG_RT_File::GetLead(int lead)
{
    QVector<int32_t> leadVector;
    foreach(ampsample sample, samples) {
        leadVector.push_back(sample.leads[lead]);
    }
    return leadVector;
}

leadoffChange qCardipiaECG_RT_File::GetNextElectrodeChangeIndex(int currentIndex)
{
    leadoffChange extraChange;
    if(currentIndex < 0) {
        extraChange.extra = samples.at(0).extra;
        extraChange.index = 0;
    } else {
        uint16_t currentExtra = samples.at(currentIndex).extra;
        uint16_t extra;
        for(int i = currentIndex; i < samples.count(); i++) {
            extra = samples.at(i).extra;
            if(currentExtra != extra) {
                extraChange.extra = extra;
                extraChange.index = i;
                return extraChange;
            }
        }
        extraChange.index = -1;
    }
    return extraChange;
}

double qCardipiaECG_RT_File::GetResolution()
{
    return m_resolution;
}

int qCardipiaECG_RT_File::SamplesCount()
{
    return samples.count();
}
