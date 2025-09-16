#include "qImpulseSignal.h"

qImpulseSignal::qImpulseSignal(int samplingFrec, double resolution) :
    m_samplingFrec(samplingFrec),
    m_resolution(resolution),
    m_durationS(10),
    m_amplitude(1)
{

}

void qImpulseSignal::setSignalDuration(int durationS)
{
    m_durationS = durationS;
}

void qImpulseSignal::setSignalAmplitude(double amplitudeMV)
{
    m_amplitude = amplitudeMV;
}

const QVector<int32_t> &qImpulseSignal::getSignal()
{
    int samplesToMake = m_durationS*m_samplingFrec;
    signalVector.clear();
    for(int i=0; i<samplesToMake; i++) {
        if(i == 500) {
            signalVector.append(static_cast<int>(m_amplitude/m_resolution));
        } else {
            signalVector.append(0);
        }

    }
    return signalVector;
}
