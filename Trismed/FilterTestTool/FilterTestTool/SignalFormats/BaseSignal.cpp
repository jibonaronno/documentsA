#include "BaseSignal.h"

BaseSignal::BaseSignal(QObject *parent) : QObject(parent)
  , resolution(0.001f), samplingFreq(500)
{
    pacemakerQueue = nullptr;
    samplesQueue = nullptr;
    memset(signalBuffer, 0, sizeof(short)*12*5000);
}

BaseSignal::~BaseSignal()
{
    delete pacemakerQueue;
    delete samplesQueue;
}

FastQueue<unsigned short> *BaseSignal::GetPacemakerQueue()
{
    return pacemakerQueue;
}

FastQueue<int> *BaseSignal::GetSamplesQueue()
{
    return samplesQueue;
}

#ifndef MEASUREMENTS_TESTER
QVector<int32_t> BaseSignal::GetChannel(int lead) {
    return m_leads[lead];
}
#else
#include "../../QCardipia/qcardipia/Filters/qFilterAC60.h"
#include "../../QCardipia/qcardipia/Filters/qFilterMUS35.h"
void BaseSignal::FilterSignal()
{
    qFilterAC60 ac60filter;
    qFilterMUS35 mus35Filter;
    for(int ch = 0; ch<12; ch++) {
        ac60filter.Init();
        mus35Filter.Init();
        for(int sample=0; sample<5000; sample++) {
            signalBuffer[ch*5000+sample] = static_cast<short>(ac60filter.Filter(signalBuffer[ch*5000+sample]));
            //signalBuffer[ch*5000+sample] = static_cast<short>(mus35Filter.Filter(signalBuffer[ch*5000+sample]));
        }
    }

#if 1
    /* correcting the filter delay */
    int filterDelay = static_cast<int>(/*mus35Filter.GetDelay() +*/ ac60filter.GetDelay());
    for(int ch = 0; ch<12; ch++) {
        for(int sample=0; sample<(5000-filterDelay); sample++) {
            signalBuffer[ch*5000+sample] = signalBuffer[ch*5000+sample+filterDelay];
        }
        for(int sample=(4999-filterDelay); sample<5000; sample++) {
            //signalBuffer[ch*5000+sample] = signalBuffer[ch*5000+(filterDelay)];
            signalBuffer[ch*5000+sample] = signalBuffer[ch*5000+(4999-filterDelay)];
        }
    }
#endif
}

#include <math.h>
void BaseSignal::ApplyPhasor(double rv)
{
    double M, Sigma;
    for(int i=0; i<5000; i++) {
        M = sqrt(pow(rv,2)+pow(signalBuffer[i],2));
        Sigma = pow(tan(signalBuffer[i]/rv), -1);
        //qDebug() << signalBuffer[i] << M << Sigma;
        //qDebug() << signalBuffer[i];
    }
}

void BaseSignal::PerformMeasurements(bool applyFilter)
{
    if(applyFilter) {
        FilterSignal();
    }
    ecgmeasurements_SetResolution(resolution);
    ecgmeasurements_SetECG(signalBuffer);
    unsigned char pcmkData[5000] = {0u};
    ecgmeasurements_SetPacemaker(pcmkData);
    ecganalyzer_Analyze(35);
    Medic *medic = ecgmeasurements_GetMedicPointer();
#ifdef OLD_ANALYZER
    Pd_ms = 0;
#else
    Pd_ms = medic->globalPd;//Pd[0];
#endif
    PQi_ms = medic->average_PR;//PR[0];
    QRSd_ms = medic->QRSd;
    QTi_ms = medic->average_QT;//QT[0];

    // filling up the information for the ECG browser
    if(pacemakerQueue)
        delete pacemakerQueue;
    pacemakerQueue = new FastQueue<unsigned short>(5000);
    unsigned short dummyPcmData[5000] = {0};
    pacemakerQueue->push(dummyPcmData, 5000);

    if(samplesQueue)
        delete samplesQueue;

    samplesQueue = new FastQueue<int>(5000*12);
    int li=0;
    while(!samplesQueue->isFull()) {
        for(int channel=0; channel<12; channel++) {
            int value = signalBuffer[li + channel*5000];
            samplesQueue->push(&value, 1);
        }
        li++;
    }
    ApplyPhasor(0.003);

    for(int lead=0;lead<12;lead++) {
        perLeadMeassurements[lead].P1d_ms = static_cast<int>(round(medic->Pd[lead]));
        perLeadMeassurements[lead].P1a_uV = static_cast<int>(round(medic->Pa[lead]*1000));
        perLeadMeassurements[lead].P2d_ms = 0;
        perLeadMeassurements[lead].P2a_uV = 0;
        perLeadMeassurements[lead].qrsType = N;
        perLeadMeassurements[lead].Qd_ms = static_cast<int>(round(medic->Qd[lead]));
        perLeadMeassurements[lead].Qa_uV = static_cast<int>(round(medic->Qa[lead]*1000));
        perLeadMeassurements[lead].Rd_ms = static_cast<int>(round(medic->Rd[lead]));
        perLeadMeassurements[lead].Ra_uV = static_cast<int>(round(medic->Ra[lead]*1000));
        perLeadMeassurements[lead].Sd_ms = static_cast<int>(round(medic->Sd[lead]));
        perLeadMeassurements[lead].Sa_uV = static_cast<int>(round(medic->Sa[lead]*1000));
        perLeadMeassurements[lead].QRSd_ms = static_cast<int>(round(medic->Qd[lead]+medic->Rd[lead]+medic->Sd[lead]));
        perLeadMeassurements[lead].Ja_uV = static_cast<int>(round(medic->STonset[lead]*1000));
        perLeadMeassurements[lead].ST20a_uV = static_cast<int>(round(medic->STmiddle[lead]*1000));
        perLeadMeassurements[lead].ST40a_uV = static_cast<int>(round(medic->STmiddle[lead]*1000));
        perLeadMeassurements[lead].ST60a_uV = static_cast<int>(round(medic->STmiddle[lead]*1000));
        perLeadMeassurements[lead].ST80a_uV = static_cast<int>(round(medic->STmiddle[lead]*1000));
        perLeadMeassurements[lead].Ta_uV = static_cast<int>(round(medic->Ta[lead]*1000));
    }
}

globalIntervalsData_t BaseSignal::GetMeasuredData()
{
    globalIntervalsData_t results;
    results.P_Duration = Pd_ms;
    results.PQ_Interval = PQi_ms;
    results.QRS_Duration = QRSd_ms;
    results.QT_Interval = QTi_ms;
    results.signalIndex = signalIndex;
    results.excluded_Pd = false;
    results.excluded_PQi = false;
    results.excluded_QRSd = false;
    results.excluded_QTi = false;
    return results;
}
#endif
