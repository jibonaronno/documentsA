#ifndef QPULSESIGNAL_H
#define QPULSESIGNAL_H

#include <QVector>
#include <stdint.h>
#include <math.h>

using namespace std;

class qPulseSignal
{
public:
    qPulseSignal(int samplingFrec = 500, double resolution = 0.002686203);
    void setPulseInformation(int width_ms, int period_ms, int pulseCount, double pulseAmplitude_mV);
    const QVector<int32_t> &getSignal();

private:
    int m_samplingFrec;
    double m_resolution;
    int m_width_ms;
    int m_period_ms;
    int m_pulseCount;
    double m_pulseAmplitude_mV;

    QVector<int32_t> signalVector;

    int msToSamples(int ms);
};

#endif // QPULSESIGNAL_H
