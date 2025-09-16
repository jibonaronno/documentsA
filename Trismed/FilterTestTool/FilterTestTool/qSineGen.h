#ifndef QSINEGEN_H
#define QSINEGEN_H

#include <QVector>
#include <stdint.h>
#include <math.h>

using namespace std;

class qSineGen
{
public:
    qSineGen(double signalFrequency, int samplingFrec = 500, double resolution = 0.002686203);
    void setSignalDuration(int durationS);
    void setSignalAmplitude(double amplitudeMV);
    void setOffset_mV(double offset_mV);
    const QVector<int32_t>& getSignal();
private:
    double m_signalFreq;
    int m_samplingFrec;
    double m_resolution;
    int m_durationS;
    double m_amplitude;
    double m_offset;
    QVector<int32_t> signalVector;
};

#endif // QSINEGEN_H
