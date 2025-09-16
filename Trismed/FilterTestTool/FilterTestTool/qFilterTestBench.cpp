#include "qFilterTestBench.h"
#include <QDebug>
#include <stdint.h>
#include "qSineGen.h"
#include "qStepSignal.h"
#include "qPulsesignal.h"
#include "qSpikeGen.h"
#include "qImpulseSignal.h"

qFilterTestBench::qFilterTestBench(qAbstractFilter *filter, QObject *parent)
    : QObject(parent), m_filter{filter}
{
    m_fixFilterDelay = false;
    m_resolution = 0.000286102;//0.002686203 / 4;
}

void qFilterTestBench::SetResolution(double resolution)
{
    m_resolution = resolution;
}

void qFilterTestBench::SetFilter(qAbstractFilter *filter)
{
    m_filter = filter;
    m_filtersList.clear();
}

void qFilterTestBench::SetFiltersList(QList<qAbstractFilter *> filtersList)
{
    m_filter = nullptr;
    m_filtersList = filtersList;
}

void qFilterTestBench::SetPacemakerSpikeParams(double paceAmp_mV, double paceWidth, double spikePeriod)
{

}

void qFilterTestBench::SetSignalProperties(double AmplitudMV, int DurationS, int SamplingFrequency)
{
    m_AmplitudMV = AmplitudMV;
    m_DurationS = DurationS;
    m_SamplingFrequency = SamplingFrequency;
}

void qFilterTestBench::SetupOutputParameters(double frequency, double timeS)
{
    m_outputFrequency = frequency;
    m_timeToSave = timeS;
}

void qFilterTestBench::SetFrequencySweep(double lowestFreq, double highestFreq, double frequencyStep)
{
    m_lowestFreq = lowestFreq;
    m_highestFreq = highestFreq;
    m_frequencyStep = frequencyStep;
}

void qFilterTestBench::SetFixFilterDelay(bool fix)
{
    m_fixFilterDelay = fix;
}

double qFilterTestBench::GetTotalFilterDelay()
{
    double totalSamplesDelay = 0;
    for( auto filter : m_filtersList) {
        totalSamplesDelay += filter->GetDelay();
    }
    return totalSamplesDelay;
}

void qFilterTestBench::Process()
{
    acSweepResult.clear();
    m_originalSignal.clear();
    m_filteredSignal.clear();
    double percent=0;
    double totalIterations = abs(static_cast<int32_t>((m_highestFreq - m_lowestFreq) / m_frequencyStep));
    double percentIncrement =  100/totalIterations;
    for(double freq = m_lowestFreq; freq <= m_highestFreq; freq += m_frequencyStep) {
        qSineGen currentSine(freq, m_SamplingFrequency, m_resolution);
        currentSine.setSignalAmplitude(m_AmplitudMV/2);
        currentSine.setSignalDuration(m_DurationS);
        QVector<int32_t> filteredSignal;
        QVector<int32_t> originalSignal;
        if(m_filter) {
            filteredSignal = m_filter->Filter(currentSine.getSignal());
        } else if(!m_filtersList.isEmpty()) {
            originalSignal = currentSine.getSignal();
            if(m_originalSignal.isEmpty() && freq >= m_outputFrequency) {
                m_timeToSave = m_timeToSave * m_SamplingFrequency;
                if(m_timeToSave > originalSignal.count())
                    m_timeToSave = originalSignal.count();
                for(int i=0; i<m_timeToSave; i++) {
                    m_originalSignal << QPointF(i, originalSignal.at(i)*m_resolution);
                }
            }
            double totalFilterDelay = 0;
            for( auto filter : m_filtersList) {
                originalSignal = filter->Filter(originalSignal);
                totalFilterDelay += filter->GetDelay();
            }
            filteredSignal = originalSignal;

            if(m_filteredSignal.isEmpty() && freq >= m_outputFrequency) {
                m_timeToSave = m_timeToSave * m_SamplingFrequency;
                if(m_timeToSave > filteredSignal.count())
                    m_timeToSave = filteredSignal.count();
                for(int i=0; i<m_timeToSave; i++) {
                    if(!m_fixFilterDelay || i>=totalFilterDelay)
                        m_filteredSignal << QPointF(m_fixFilterDelay?(i-totalFilterDelay):i, filteredSignal.at(i)*m_resolution);
                }
            }

        }
        int32_t max = INT32_MIN;
        int32_t min = INT32_MAX;
        for(int index = filteredSignal.count()/2; index < filteredSignal.count(); index++) {
            auto value = filteredSignal.at(index);
            if(max < value) max = value;
            if(min > value) min = value;
        }
        double filteredAmp = ((max-min)*m_resolution);
        filteredAmp = 20*log10(filteredAmp/m_AmplitudMV);
        acSweepResult << QPointF(freq, filteredAmp);
        percent += percentIncrement;
        emit sProgress(static_cast<int>(percent));
    }

#if 0
    QVector<int32_t> originalStep;
    const int duration_s = 30;
#if 1
#warning 2mV 0.5ms pacemaker spike
    qSpikeGen spikes(8000, m_resolution);
    spikes.setPeriod(588);
    spikes.setSignalDuration(duration_s);
    spikes.setSignalAmplitude(2);
    spikes.setPikeWidth(0.5);
    spikes.setRaiseTime(250/*100*/);
    originalStep = spikes.getSignal();
    qDebug() << INT32_MAX << "    " << INT32_MIN;
    for(int i=0; i<8000; i++) {
        qDebug() << originalStep[i];
    }
#else
#warning 1mV 40Hz sinewave + 250mV 2ms pacemaker spike
    qSineGen sine(40, m_SamplingFrequency, m_resolution);
    sine.setSignalDuration(duration_s);
    sine.setSignalAmplitude(1);
    sine.setOffset_mV(300);

    qSpikeGen spikes(m_SamplingFrequency, m_resolution);
    spikes.setPeriod(588);
    spikes.setSignalDuration(duration_s);
    spikes.setSignalAmplitude(250);
    spikes.setPikeWidth(2);
    originalStep = sine.getSignal();
    for(int i=0; i<originalStep.count(); i++) {
        originalStep[i]+=spikes.getSignal().at(i);
    }
    qDebug() << INT32_MAX << "    " << INT32_MIN;
    for(int i=0; i<500; i++) {
        qDebug() << originalStep[i];
    }
#endif
#else
    // Calculate step response

#if 1
    qPulseSignal pulseSignal(m_SamplingFrequency, m_resolution);
    pulseSignal.setPulseInformation(100, 20000, 2, 3);
    QVector<int32_t> originalStep = pulseSignal.getSignal();
#else
    qStepSignal stepSignal(m_SamplingFrequency, m_resolution);
    stepSignal.setSignalDuration(30);
    stepSignal.setSignalAmplitude(1);

    QVector<int32_t> originalStep = stepSignal.getSignal();
#endif
#endif

    m_stepSignal.clear();
    for(int i=0; i<originalStep.count(); i++) {
        m_stepSignal<< QPointF(i, originalStep.at(i)*m_resolution);
    }

    QVector<int32_t> filteredStepSignal = originalStep;

    double totalFilterDelay = 0;
    for( auto filter : m_filtersList) {
        filter->Init();
        filteredStepSignal = filter->Filter(filteredStepSignal);
        totalFilterDelay += filter->GetDelay();
    }

    m_stepFilteredSignal.clear();
    for(int i=0; i<filteredStepSignal.count(); i++) {
        if(!m_fixFilterDelay || i>=totalFilterDelay)
            m_stepFilteredSignal<< QPointF(m_fixFilterDelay?(i-totalFilterDelay):i, filteredStepSignal.at(i)*m_resolution);
    }

    // Calculate the Ipulse response
    qImpulseSignal impulseSignal(m_SamplingFrequency, m_resolution);
    impulseSignal.setSignalDuration(5);
    impulseSignal.setSignalAmplitude(1);
    QVector<int32_t> originalImpulse = impulseSignal.getSignal();
    m_impulseSignal.clear();
    m_impulseFilteredSignal.clear();

    for(int i=0; i<originalImpulse.count(); i++) {
        m_impulseSignal<< QPointF(i, originalImpulse.at(i)*m_resolution);
    }

    QVector<int32_t> filteredImpulseSignal = originalImpulse;

    for( auto filter : m_filtersList) {
        filter->Init();
        filteredImpulseSignal = filter->Filter(filteredImpulseSignal);
    }

    for(int i=0; i<filteredImpulseSignal.count(); i++) {
        if(!m_fixFilterDelay || i>=totalFilterDelay)
            m_impulseFilteredSignal<< QPointF(m_fixFilterDelay?(i-totalFilterDelay):i, filteredImpulseSignal.at(i)*m_resolution);
    }

    emit sProgress(100);
}

void qFilterTestBench::FilterSignal(BaseSignal* basesignal)
{
    QVector<int32_t> originalSignal = basesignal->GetChannel(1);
    FilterSignal(originalSignal);
}

void qFilterTestBench::FilterSignal(qECG_RAW_File &rawFile)
{
    QVector<int32_t> originalSignal = rawFile.GetChannel(1);
    FilterSignal(originalSignal);
}

void qFilterTestBench::FilterSignal(QVector<int32_t> &originalSignal)
{
    m_originalSignal.clear();
    m_filteredSignal.clear();
    m_SamplingFrequency = 500;
    m_timeToSave = originalSignal.count() / m_SamplingFrequency;
    int i = 0;
    for(auto sample : originalSignal) {
        m_originalSignal << QPointF(i, sample*m_resolution);
        i++;
    }
    double totalFilterDelay = 0;
    for( auto filter : m_filtersList) {
        originalSignal = filter->Filter(originalSignal);
        totalFilterDelay += filter->GetDelay();
    }
    QVector<int32_t> filteredSignal = originalSignal;

    i=0;
    int dropedSamples=0;
    for(auto sample : filteredSignal) {
        if(!m_fixFilterDelay || dropedSamples >= totalFilterDelay) {
            m_filteredSignal << QPointF(i, sample*m_resolution);
            i++;
        } else
            dropedSamples++;
    }
}

void qFilterTestBench::FilterSignal(QVector<int32_t> &originalSignal, QVector<int> filterResetIndexes)
{
    m_originalSignal.clear();
    m_filteredSignal.clear();
    m_SamplingFrequency = 500;
    QVector <int32_t> filteredFragment;
    QVector <int32_t> filteredSignal;
    m_timeToSave = originalSignal.count() / m_SamplingFrequency;
    int i = 0;
    for(auto sample : originalSignal) {
        m_originalSignal << QPointF(i, sample*m_resolution);
        i++;
    }
    double totalFilterDelay = 0;

    int startIdx, endIdx;

    for( auto filter : m_filtersList) {
        i = 0;
        startIdx = 0;
        endIdx = originalSignal.count()-1;
        filteredSignal.clear();
        for (int idx=0; idx<filterResetIndexes.count()-1; idx++) {
            startIdx = filterResetIndexes.at(idx);
            endIdx = filterResetIndexes.at(idx+1);
            filteredFragment = filter->Filter(originalSignal, startIdx, endIdx);
            filteredSignal += filteredFragment;
        }
        if(startIdx != 0) {
            startIdx = endIdx;
            endIdx = originalSignal.count()-1;
        }
        filteredFragment = filter->Filter(originalSignal, startIdx, endIdx);
        filteredSignal += filteredFragment;
        originalSignal = filteredSignal;
        totalFilterDelay += filter->GetDelay();
    }


    i=0;
    int dropedSamples=0;
    for(auto sample : filteredSignal) {
        if(!m_fixFilterDelay || dropedSamples >= totalFilterDelay) {
            m_filteredSignal << QPointF(i, sample*m_resolution);
            i++;
        } else
            dropedSamples++;
    }
}

QVector<QPointF> qFilterTestBench::GetResult()
{
    if(acSweepResult.isEmpty())
        Process();
    return acSweepResult;
}

QVector<QPointF> qFilterTestBench::GetOriginalSignal()
{
    return m_originalSignal;
}

QVector<QPointF> qFilterTestBench::GetFilteredSignal()
{
    return m_filteredSignal;
}

QVector<QPointF> qFilterTestBench::GetStepSignal()
{
    return m_stepSignal;
}

QVector<QPointF> qFilterTestBench::GetFilteredStepSignal()
{
    return m_stepFilteredSignal;
}

QVector<qFilterTestBench::ZeroCross_t> qFilterTestBench::detectZeroCorssings(QVector<int32_t> &signal)
{
    ZeroCross_t zeroCross;
    QVector<qFilterTestBench::ZeroCross_t> ZeroCrosses;
    bool newZeroCross = false;
    for (int i=0; i<signal.count()-1; i++) {
        if(signal.at(i+1) < 0 && signal.at(i) >= 0) {
            zeroCross.index = i;
            zeroCross.slope = up;
            newZeroCross = true;
        } else if(signal.at(i+1) >= 0 && signal.at(i) < 0) {
            zeroCross.index = i;
            zeroCross.slope = down;
            newZeroCross = true;
        }
        if(newZeroCross) {
            newZeroCross = false;
            ZeroCrosses << zeroCross;
        }
    }
    return ZeroCrosses;
}
