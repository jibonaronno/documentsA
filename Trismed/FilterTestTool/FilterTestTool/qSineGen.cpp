#include "qSineGen.h"

qSineGen::qSineGen(double signalFrequency, int samplingFrec, double resolution)
    : m_signalFreq{signalFrequency}, m_samplingFrec{samplingFrec}, m_resolution{resolution}, m_amplitude{1},
      m_offset{0}
{

}

void qSineGen::setSignalDuration(int durationS)
{
    m_durationS = durationS;
    signalVector.clear();
}

void qSineGen::setSignalAmplitude(double amplitudeMV)
{
    m_amplitude = amplitudeMV/m_resolution;
    signalVector.clear();
}

void qSineGen::setOffset_mV(double offset_mV)
{
    m_offset = offset_mV/(m_resolution);
    signalVector.clear();
}

const QVector<int32_t> &qSineGen::getSignal()
{
    if(signalVector.isEmpty()) {
        for(int i=0; i<m_durationS*m_samplingFrec; i++) {
            const double x = static_cast<double>(i) / (m_samplingFrec/m_signalFreq);
            int32_t sample = static_cast<int32_t>(m_offset + (m_amplitude * cos(2*M_PI * x)));
            signalVector << sample;
        }
    }
    return signalVector;
}
