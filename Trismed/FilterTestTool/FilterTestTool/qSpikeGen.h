#ifndef QSPIKEGEN_H
#define QSPIKEGEN_H

#include <QVector>
#include <stdint.h>
#include <math.h>

class qSpikeGen
{
public:
    qSpikeGen(int samplingFrec = 500, double resolution = 0.002686203);
    void setSignalDuration(int durationS);
    void setPeriod(int period_ms);
    void setSignalAmplitude(double amplitudeMV);
    void setPikeWidth(double spikeWidth_ms);
    void setRaiseTime(double raiseTime_us);
    const QVector<int32_t> &getSignal();
private:
    double m_signalFreq;
    int m_samplingFrec;
    double m_resolution;
    int m_durationS;
    double m_amplitude;
    int m_period_ms;
    double m_spikeWidth_ms;
    double m_raiseTime_samples;
    QVector<int32_t> signalVector;
};

#endif // QSPIKEGEN_H
