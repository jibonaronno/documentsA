#include "qAbstractFilter.h"

#define DELAY_ONLY_PACEMAKER
qAbstractFilter::qAbstractFilter(double filterDelay)
{
    m_filterDelay = filterDelay;
#ifdef CARDIPIA
    initDelay();
#endif
}

qAbstractFilter::~qAbstractFilter()
{

}

void qAbstractFilter::Init()
{
    privInit();
#ifdef CARDIPIA
    initDelay();
#endif
}

int32_t qAbstractFilter::Filter(int32_t sample)
{
    return privFilter(sample, 0);
}

QVector<int32_t> qAbstractFilter::Filter(const QVector<int32_t> &inSignal)
{
    privInit();
    output.clear();
    foreach (int32_t sample, inSignal) {
        output << privFilter(sample, 0);
    }
    return output;
}

QVector<int32_t> qAbstractFilter::Filter(const QVector<int32_t> &inSignal, int startIndex, int endIndex)
{
    privInit();
    output.clear();
    for(int i = startIndex; i < endIndex; i++) {
        output << privFilter(inSignal.at(i), 0);
    }
    return output;
}

double qAbstractFilter::GetDelay()
{
#ifdef FORCE_DELAY_0
    return 0;
#else
    return m_filterDelay;
#endif
}

#ifdef CARDIPIA
void qAbstractFilter::initDelay()
{
    listExtra.clear();
    listExtra.resize(GetDelay()<1?1:GetDelay(), ELECTRODEMASK);
}

void qAbstractFilter::Filter(ampsample *sample)
{
    for(int i = 0; i < AMP_IN_LEADS; i++) {
        sample->leads[i] = privFilter(sample->leads[i], i);
    }
    delayExtraData(*sample);
}

void qAbstractFilter::delayExtraData(ampsample &sample)
{
    unsigned short extra;
    if(m_filterDelay == 0)
        return;
    extra = listExtra.front();
    listExtra.pop_front();
    listExtra.push_back(sample.extra);
#ifdef DELAY_ONLY_PACEMAKER
    sample.extra = (sample.extra & (~AMP_PACEMAKER_MASK)) | (extra & AMP_PACEMAKER_MASK);
#else
    sample.extra = extra;
#endif
}
#endif
