#include "CTSSignal_CYC.h"
#include <QStringList>
#ifdef MEASUREMENTS_TESTER
#include "CTS_RefferenceData.h"
#else
#include <QDir>
#endif

#define CTS_SIGNAL_NAMES "../FilterTestTool/CTS_Database/%1"
#define CTS_PATH "../FilterTestTool/CTS_Database/"

#ifdef MEASUREMENTS_TESTER
CTSSignal_CYC::CTSSignal_CYC(unsigned int index, QObject *parent) : BaseSignal(parent)
{
    reportSignalName = CTS_RefferenceData::GetSignalName(index);
    LoadFile();
}
#else
QStringList CTSSignal_CYC::GetFileLists()
{
    QDir searchFolder(CTS_PATH);
    searchFolder.setNameFilters(QStringList() << "*.CYC");
    QStringList fileList = searchFolder.entryList(QDir::NoFilter, QDir::NoSort);
    return fileList;
}

CTSSignal_CYC::CTSSignal_CYC(QString filename, QObject *parent) : BaseSignal(parent)
{
    reportSignalName = filename;
    LoadFile();
}
#endif

void CTSSignal_CYC::LoadFile()
{
    signalFilename = QString(CTS_SIGNAL_NAMES).arg(reportSignalName);
    QFile textFile(signalFilename);

    textFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream textStream(&textFile);
    int sampleIndex = 0;
    QString line = textStream.readLine();
    QStringList samplesList = line.split(QRegExp("[\t ]+"), QString::SkipEmptyParts);
    double inputSamplinqFreq = samplesList.at(2).toDouble();
    int fileSamplesCount = samplesList.at(0).toInt();
    int samplingStep = static_cast<int>(inputSamplinqFreq/samplingFreq);

    QStringList fullFile;
    int skipCounter=0;
    int cycleSamplesCount=0;
    for(cycleSamplesCount=0; cycleSamplesCount<fileSamplesCount; cycleSamplesCount++) {
        if(skipCounter==0) {
            fullFile.append(textStream.readLine());
        } else {
            textStream.readLine(); // drop this sample
        }
        skipCounter++;
        if(skipCounter >= samplingStep) {
            skipCounter = 0;
        }
    }

    cycleSamplesCount = fullFile.count();

    short *cycleBuffer = new short [static_cast<unsigned int>(12 * cycleSamplesCount)];
    for(int i=0; i<cycleSamplesCount; i++) {
        samplesList = fullFile[i].split(QRegExp("[\t ]+"), QString::SkipEmptyParts);
        if(samplesList.count() != 8) {
            break;
        }
        short I = samplesList[0].toShort();
        short II = samplesList[1].toShort();
        cycleBuffer[i] = I;
        cycleBuffer[i+1*cycleSamplesCount] = II;
        cycleBuffer[i+2*cycleSamplesCount] = II - I;         // III
        cycleBuffer[i+3*cycleSamplesCount] = -(II+I) / 2;    // aVR
        cycleBuffer[i+4*cycleSamplesCount] = I - II / 2;     // aVL
        cycleBuffer[i+5*cycleSamplesCount] = II - I / 2;     // aVF
        cycleBuffer[i+6*cycleSamplesCount] = samplesList[2].toShort();
        cycleBuffer[i+7*cycleSamplesCount] = samplesList[3].toShort();
        cycleBuffer[i+8*cycleSamplesCount] = samplesList[4].toShort();
        cycleBuffer[i+9*cycleSamplesCount] = samplesList[5].toShort();
        cycleBuffer[i+10*cycleSamplesCount] = samplesList[6].toShort();
        cycleBuffer[i+11*cycleSamplesCount] = samplesList[7].toShort();
    }

    int cycleSampleIndex = 0;
    while (sampleIndex < 5000) {
        for(int channelIndex=0; channelIndex < 12; channelIndex++) {
            signalBuffer[sampleIndex + 5000*channelIndex] = cycleBuffer[cycleSampleIndex+channelIndex*cycleSamplesCount];
        }
        sampleIndex++;
        cycleSampleIndex++;
        if(cycleSampleIndex >= cycleSamplesCount)
            cycleSampleIndex = 0;
    }
    delete []cycleBuffer;
#ifndef MEASUREMENTS_TESTER
    LoadDataVector();
#endif
}

void CTSSignal_CYC::LoadDataVector()
{
    m_channelCount = 12;
    m_leads.clear();
    for(int32_t i=0; i<m_channelCount; i++) {
        m_leads << QVector<int32_t>();
    }

    for(int32_t channel=0; channel<m_channelCount; channel++) {
        for(uint32_t sampleIndex=0; sampleIndex < 5000; sampleIndex++) {
            m_leads[channel] << static_cast<int32_t>(signalBuffer[sampleIndex + 5000*channel]);
        }
    }
}
QString CTSSignal_CYC::GetResults()
{
#ifdef MEASUREMENTS_TESTER
    //ANE20000, Pd, PR, QRSd, QTi, 12x (Qd, Rd, Sd, P1a, P2a, Qa, Ra, Sa, Ja, ST20a, ST40a, ST60a, ST80a, Ta)
    QString nameAndGlobalValues = QString("%1, %2, %3, %4, %5")
            .arg(reportSignalName)
            .arg(QString::number(Pd_ms))
            .arg(QString::number(PQi_ms))
            .arg(QString::number(QRSd_ms))
            .arg(QString::number(QTi_ms));

    QString pearLeadInfo;
#if 1
    for(int lead=0; lead<12; lead++) {
        pearLeadInfo += QString(", %1")
                .arg(QString::number(perLeadMeassurements[lead].Qd_ms));
    }
    for(int lead=0; lead<12; lead++) {
        pearLeadInfo += QString(", %1")
                .arg(QString::number(perLeadMeassurements[lead].Rd_ms));
    }
    for(int lead=0; lead<12; lead++) {
        pearLeadInfo += QString(", %1")
                .arg(QString::number(perLeadMeassurements[lead].Sd_ms));
    }
    for(int lead=0; lead<12; lead++) {
        pearLeadInfo += QString(", %1")
                .arg(QString::number(perLeadMeassurements[lead].P1a_uV));
    }
    for(int lead=0; lead<12; lead++) {
        pearLeadInfo += QString(", %1")
                .arg(QString::number(perLeadMeassurements[lead].P2a_uV));
    }
    for(int lead=0; lead<12; lead++) {
        pearLeadInfo += QString(", %1")
                .arg(QString::number(perLeadMeassurements[lead].Qa_uV));
    }
    for(int lead=0; lead<12; lead++) {
        pearLeadInfo += QString(", %1")
                .arg(QString::number(perLeadMeassurements[lead].Ra_uV));
    }
    for(int lead=0; lead<12; lead++) {
        pearLeadInfo += QString(", %1")
                .arg(QString::number(perLeadMeassurements[lead].Sa_uV));
    }
    for(int lead=0; lead<12; lead++) {
        pearLeadInfo += QString(", %1")
                .arg(QString::number(perLeadMeassurements[lead].Ja_uV));
    }
    for(int lead=0; lead<12; lead++) {
        pearLeadInfo += QString(", %1")
                .arg(QString::number(perLeadMeassurements[lead].ST20a_uV));
    }
    for(int lead=0; lead<12; lead++) {
        pearLeadInfo += QString(", %1")
                .arg(QString::number(perLeadMeassurements[lead].ST40a_uV));
    }
    for(int lead=0; lead<12; lead++) {
        pearLeadInfo += QString(", %1")
                .arg(QString::number(perLeadMeassurements[lead].ST60a_uV));
    }
    for(int lead=0; lead<12; lead++) {
        pearLeadInfo += QString(", %1")
                .arg(QString::number(perLeadMeassurements[lead].ST80a_uV));
    }
    for(int lead=0; lead<12; lead++) {
        pearLeadInfo += QString(", %1")
                .arg(QString::number(perLeadMeassurements[lead].Ta_uV));
    }
#else
    //ANE20000, Pd, PR, QRSd, QTi, 12x (Qd, Rd, Sd, P1a, P2a, Qa, Ra, Sa, Ja, ST20a, ST40a, ST60a, ST80a, Ta)
    for(int lead=0; lead<12; lead++) {
        pearLeadInfo += QString(", %1, %2, %3, %4, %5, %6, %7, %8, %9, %10, %11, %12, %13, %14")
                .arg(QString::number(perLeadMeassurements[lead].Qd_ms))
                .arg(QString::number(perLeadMeassurements[lead].Rd_ms))
                .arg(QString::number(perLeadMeassurements[lead].Sd_ms))
                .arg(QString::number(perLeadMeassurements[lead].P1a_uV))
                .arg(QString::number(perLeadMeassurements[lead].P2a_uV))
                .arg(QString::number(perLeadMeassurements[lead].Qa_uV))
                .arg(QString::number(perLeadMeassurements[lead].Ra_uV))
                .arg(QString::number(perLeadMeassurements[lead].Sa_uV))
                .arg(QString::number(perLeadMeassurements[lead].Ja_uV))
                .arg(QString::number(perLeadMeassurements[lead].ST20a_uV))
                .arg(QString::number(perLeadMeassurements[lead].ST40a_uV))
                .arg(QString::number(perLeadMeassurements[lead].ST60a_uV))
                .arg(QString::number(perLeadMeassurements[lead].ST80a_uV))
                .arg(QString::number(perLeadMeassurements[lead].Ta_uV));
    }
#endif
    return (nameAndGlobalValues + pearLeadInfo);
#else
    return "";
#endif
}
