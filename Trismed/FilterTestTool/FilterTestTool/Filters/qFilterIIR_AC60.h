#ifndef QFILTERIIR_AC60_H
#define QFILTERIIR_AC60_H

#include "qAbstractFilter.h"

#define USE_WINFILTER
#ifdef USE_WINFILTER
#define NCoef 4
#else
#define USE_AC60_NOTCH_Q20_APASS1
#undef MWSPT_NSEC

#ifdef USE_AC60_NOTCH_Q20_APASS1
#define MWSPT_NSEC 3
#else
#define MWSPT_NSEC 3
#endif
#endif

class qFilterIIR_AC60 : public qAbstractFilter
{
public:
    qFilterIIR_AC60();
    virtual void InitLead(int lead);
    virtual int GetFrequencyIndex() { return ACF_60; }

protected:
    virtual void privInit();
    virtual int32_t privFilter(int32_t sample, int lead);

private:
#ifdef USE_WINFILTER
    float y[AMP_IN_LEADS][NCoef+1]; //output samples
    float x[AMP_IN_LEADS][NCoef+1]; //input samples
#else
    double x[AMP_IN_LEADS][MWSPT_NSEC][3];
    double y[AMP_IN_LEADS][MWSPT_NSEC][3];
#endif
};

#endif // QFILTERIIR_AC60_H
