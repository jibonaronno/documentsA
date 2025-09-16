#ifndef QIMPULSESIGNAL_H
#define QIMPULSESIGNAL_H

#include <QVector>
#include <stdint.h>
#include <math.h>

using namespace std;

class qImpulseSignal
{
public:
    qImpulseSignal(int samplingFrec = 500, double resolution = 0.002686203);
    void setSignalDuration(int durationS);
    void setSignalAmplitude(double amplitudeMV);
    const QVector<int32_t> &getSignal();

private:
    int m_samplingFrec;
    double m_resolution;
    int m_durationS;
    double m_amplitude;
    QVector<int32_t> signalVector;
};

#endif // QIMPULSESIGNAL_H
