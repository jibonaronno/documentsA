#include "qFilterDrift.h"

qFilterDrift::qFilterDrift()
    : qAbstractFilter(0)
{
    m_driftFreq = DRF_005;
    m_bufferSize = 1;
    for(int i=0;i<(AMP_IN_LEADS); i++)
        xd[i] = nullptr;
    privInit();
}

qFilterDrift::~qFilterDrift()
{
    for(int i = 0; i < AMP_IN_LEADS; i++)
        delete [] xd[i];
}

void qFilterDrift::InitLead(int lead)
{
    yd0[lead] = 0;
    yd1[lead] = 0;
    nd[lead] = static_cast<int32_t>(m_bufferSize-1);
    memset(xd[lead], 0, sizeof(int)*2*static_cast<unsigned long>(m_bufferSize));
}

void qFilterDrift::SetFrequency(TDriftFilters frequency)
{
    m_driftFreq = frequency;
    switch(frequency) {
    case DRF_01:
        m_bufferSize = 3400;     // 0.1Hz
        m_filterDelay = 1700;
        break;
    case DRF_015:   // ok
        m_bufferSize = 2250;     // 0.15Hz
        m_filterDelay = 1125;
        break;
    case DRF_02:    //ok
        m_bufferSize = 1700;    // 0.2Hz
        m_filterDelay = 850;
        break;
    case DRF_025:   //ok
        m_bufferSize = 1350;     // 0.25Hz
        m_filterDelay = 675;
        break;
    case DRF_032:   //ok
        m_bufferSize = 1048;     // 0.32Hz
        m_filterDelay = 524;
        break;
    case DRF_05:    //ok
        m_bufferSize = 672;      // 0.5Hz
        m_filterDelay = 336;
        break;
    case DRF_067:   //ok
        m_bufferSize = 500;        // 0.65Hz
        m_filterDelay = 250;
        break;
    default:    /* DRF_005 or some unknown value */
        m_driftFreq = DRF_005;
        m_bufferSize = 1;    /* any small value, it will do nothing anyway */
        m_filterDelay = 0;
        break;
    }
    privInit();
#ifdef CARDIPIA
    initDelay();
#endif
}

QStringList qFilterDrift::getDriftFilters()
{
    QStringList list;
    list << "0.05Hz" << "0.5Hz" << "0.1Hz" << "0.2Hz" << "0.15Hz" << "0.25Hz" << "0.32Hz" << "0.67Hz";
    return list;
}

void qFilterDrift::privInit()
{
    for(int i=0; i<(AMP_IN_LEADS); i++)
        delete [] xd[i];
    for(int i=0;i<(AMP_IN_LEADS); i++)
        xd[i] = new int[static_cast<unsigned long>(m_bufferSize)*2];
    memset(yd0, 0, sizeof(long int)*AMP_IN_LEADS);
    memset(yd1, 0, sizeof(long int)*AMP_IN_LEADS);
    for(int i=0; i<(AMP_IN_LEADS); i++) {
        memset(xd[i], 0, sizeof(int)*2*static_cast<unsigned long>(m_bufferSize));
        nd[i] = static_cast<int32_t>(m_bufferSize-1);
    }
}

int32_t qFilterDrift::privFilter(int32_t sample, int lead)
{
    int32_t dptr=0;
    int drift_val;
    if(m_driftFreq == DRF_005) return sample;
    dptr = nd[lead];
    xd[lead][dptr] = xd[lead][dptr + m_bufferSize] = sample;
    yd0[lead] = yd1[lead] + xd[lead][dptr] - xd[lead][dptr + m_bufferSize - 1];
    yd1[lead] = yd0[lead];
    if (--nd[lead] < 0)
        nd[lead] = m_bufferSize - 1;
    drift_val = xd[lead][dptr + (m_bufferSize/2)] - (yd0[lead] / m_bufferSize);
    sample = drift_val;
    return sample;
}
