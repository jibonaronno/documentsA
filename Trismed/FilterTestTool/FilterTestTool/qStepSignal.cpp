#include "qStepSignal.h"

qStepSignal::qStepSignal(int samplingFrec, double resolution) :
    m_samplingFrec(samplingFrec),
    m_resolution(resolution),
    m_durationS(10),
    m_amplitude(1)
{
}

void qStepSignal::setSignalDuration(int durationS)
{
    m_durationS = durationS;
}

void qStepSignal::setSignalAmplitude(double amplitudeMV)
{
    m_amplitude = amplitudeMV;
}

const QVector<int32_t> &qStepSignal::getSignal()
{
    int samplesToMake = m_durationS*m_samplingFrec;
    signalVector.clear();
    int value = 0;
    for(int i=0; i<samplesToMake; i++) {
        if(i< 500) {
            value = 0;
        } else {
            value = static_cast<int>(m_amplitude/m_resolution);
        }
        signalVector.append(value);
    }
    return signalVector;
}
