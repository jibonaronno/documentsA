#ifndef BASESIGNAL_H
#define BASESIGNAL_H

#include <QObject>
#include "queues/fastqueue.h"
#ifdef MEASUREMENTS_TESTER
#include "ecganalysis.h"
#include "ecgMeasurementDebug.h"
#include "CSE_RefferenceData.h"
#include "CTS_RefferenceData.h"
#else
#include <QVector>
#endif

enum SignalType_t {CSE, CTS, ECG};

class BaseSignal : public QObject
{
    Q_OBJECT
public:
    explicit BaseSignal(QObject *parent = nullptr);
    ~BaseSignal();
    void PerformMeasurements(bool applyFilter);
    FastQueue<unsigned short>* GetPacemakerQueue();
    FastQueue<int>* GetSamplesQueue();
    virtual QString GetResults() = 0;
    virtual SignalType_t  GetSignalType() = 0;

#ifdef MEASUREMENTS_TESTER
    globalIntervalsData_t GetMeasuredData();
    struct ctsPerLeadData perLeadMeassurements[12];
#else
    QVector<int32_t> GetChannel(int lead);
#endif

    short signalBuffer[12 * 5000];
    // Results:
    int Pd_ms;
    int PQi_ms;
    int QRSd_ms;
    int QTi_ms;
    unsigned int signalIndex;
    float resolution; /* mV/CU */
    const int samplingFreq; /* Hz */

    QString signalFilename;
    QString reportSignalName;

protected:
    FastQueue<unsigned short>* pacemakerQueue;
    FastQueue<int>* samplesQueue;
#ifdef MEASUREMENTS_TESTER
    virtual void FilterSignal();
    virtual void ApplyPhasor(double rv);
#else
    QVector< QVector<int32_t> > m_leads;
    int32_t m_channelCount;
#endif
};

#endif // BASESIGNAL_H
