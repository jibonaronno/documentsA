#include "qPulsesignal.h"

qPulseSignal::qPulseSignal(int samplingFrec, double resolution)
{
    m_samplingFrec = samplingFrec;
    m_resolution = resolution;
}

void qPulseSignal::setPulseInformation(int width_ms, int period_ms, int pulseCount, double pulseAmplitude_mV)
{
    m_width_ms = width_ms;
    m_period_ms = period_ms;
    m_pulseCount = pulseCount;
    m_pulseAmplitude_mV = pulseAmplitude_mV;
}

const QVector<int32_t> &qPulseSignal::getSignal()
{
    int pulsePeriod_samples = msToSamples(m_period_ms);
    int nextPulseStart_Samples = pulsePeriod_samples;
    int pulseWidth_samples = msToSamples(m_width_ms);

    int samplesToMake = pulseWidth_samples*m_pulseCount + pulsePeriod_samples*(m_pulseCount+1);
    signalVector.clear();
    bool needToUpdatePulseStart = false;
    for(int i=0; i<samplesToMake; i++) {
        if(i >= nextPulseStart_Samples && i<(nextPulseStart_Samples+pulseWidth_samples) ) {
            needToUpdatePulseStart = true;
            signalVector.append(static_cast<int>(m_pulseAmplitude_mV/m_resolution));
        } else {
            signalVector.append(0);
            if(needToUpdatePulseStart) {
                nextPulseStart_Samples += pulseWidth_samples + pulsePeriod_samples;
                needToUpdatePulseStart = false;
            }
        }

    }
    return signalVector;
}

int qPulseSignal::msToSamples(int ms)
{
    return ms/(1000/m_samplingFrec);
}
