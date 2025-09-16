#include "qSpikeGen.h"

qSpikeGen::qSpikeGen(int samplingFrec, double resolution)
    : m_samplingFrec{samplingFrec}, m_resolution{resolution}, m_durationS{30}, m_amplitude{250}, m_period_ms{1000}, m_spikeWidth_ms{2}
{

}

void qSpikeGen::setSignalDuration(int durationS)
{
    m_durationS = durationS;
    signalVector.clear();
}

void qSpikeGen::setPeriod(int period_ms)
{
    m_period_ms = period_ms;
    signalVector.clear();
}

void qSpikeGen::setSignalAmplitude(double amplitudeMV)
{
    m_amplitude = amplitudeMV/m_resolution;
    signalVector.clear();
}

void qSpikeGen::setPikeWidth(double spikeWidth_ms)
{
    m_spikeWidth_ms = spikeWidth_ms;
}

#define US_TO_SAMPLE(ms) ( ( ms ) / ( 1000000.0/m_samplingFrec ) )
#define MS_TO_SAMPLE(ms) ( ( ms ) / ( 1000.0/m_samplingFrec ) )
void qSpikeGen::setRaiseTime(double raiseTime_us)
{
    m_raiseTime_samples = US_TO_SAMPLE(raiseTime_us);
}

const QVector<int32_t> &qSpikeGen::getSignal()
{
    bool oposite=0;
    if(signalVector.isEmpty()) {
        int widthSamples=0;
        int edgeCount = 0;
        int every_samples = MS_TO_SAMPLE(m_period_ms);
        for(int i=0; i<m_durationS*m_samplingFrec; i++) {
            int32_t sample = 0;
            if(i%every_samples == 0 && i != 0) {
                widthSamples = MS_TO_SAMPLE(m_spikeWidth_ms);
                edgeCount = m_raiseTime_samples;
            }
            if(widthSamples) {
                widthSamples--;
                if(edgeCount != 0 ) {
                    sample = static_cast<int32_t>(m_amplitude/edgeCount);
                    edgeCount--;
                } else if(widthSamples < m_raiseTime_samples) {
                    oposite = true;
                    edgeCount = m_raiseTime_samples;
                    sample = static_cast<int32_t>(m_amplitude/edgeCount);
                    edgeCount++;
                } else {
                    sample = static_cast<int32_t>(m_amplitude);
                }
            }
            signalVector << sample;
        }
    }
    return signalVector;
}
