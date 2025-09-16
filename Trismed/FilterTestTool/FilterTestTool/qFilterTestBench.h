#ifndef QFILTERTESTBENCH_H
#define QFILTERTESTBENCH_H

#include <QObject>
#include <QVector>
#include <QPointF>
#include "Filters/qAbstractFilter.h"
#include "qECG_RAW_File.h"
#include "SignalFormats/BaseSignal.h"

class qFilterTestBench : public QObject
{
    Q_OBJECT
public:
    explicit qFilterTestBench(qAbstractFilter *filter = nullptr, QObject *parent = nullptr);
    void SetResolution(double resolution);
    void SetFilter(qAbstractFilter *filter);
    void SetFiltersList(QList<qAbstractFilter*> filtersList);
    void SetPacemakerSpikeParams(double paceAmp_mV, double paceWidth, double spikePeriod);
    void SetSignalProperties(double AmplitudMV, int DurationS, int SamplingFrequency);
    void SetupOutputParameters(double frequency, double timeS);
    void SetFrequencySweep(double lowestFreq, double highestFreq, double frequencySteep);
    void SetFixFilterDelay(bool fix);
    double GetTotalFilterDelay();
    void Process();
    void FilterSignal(BaseSignal *basesignal);
    void FilterSignal(qECG_RAW_File &rawFile);
    void FilterSignal(QVector<int32_t> &originalSignal);
    void FilterSignal(QVector<int32_t> &originalSignal, QVector<int> filterResetIndexes);
    QVector<QPointF> GetResult();

    QVector<QPointF> GetOriginalSignal();
    QVector<QPointF> GetFilteredSignal();

    QVector<QPointF> GetStepSignal();
    QVector<QPointF> GetFilteredStepSignal();

    QVector<QPointF> GetImpulseSignal() { return m_impulseSignal; }
    QVector<QPointF> GetFilteredImpulseSignal() { return m_impulseFilteredSignal; }

signals:
    void sProgress(int);

private:
    double m_lowestFreq;
    double m_highestFreq;
    double m_frequencyStep;
    double m_AmplitudMV;
    double m_outputFrequency;
    double m_resolution;
    int m_DurationS;
    int m_SamplingFrequency;
    double m_timeToSave;
    bool m_fixFilterDelay;
    QVector<QPointF> acSweepResult;
    QVector<QPointF> m_originalSignal;
    QVector<QPointF> m_filteredSignal;
    qAbstractFilter *m_filter;
    QList<qAbstractFilter*> m_filtersList;

    QVector<QPointF> m_stepSignal;
    QVector<QPointF> m_stepFilteredSignal;

    QVector<QPointF> m_impulseSignal;
    QVector<QPointF> m_impulseFilteredSignal;


    enum slope_t { up, down };
    struct ZeroCross_t {
        int32_t index;
        slope_t slope;
    };

    QVector<ZeroCross_t> detectZeroCorssings(QVector<int32_t> &signal);
};

#endif // QFILTERTESTBENCH_H
