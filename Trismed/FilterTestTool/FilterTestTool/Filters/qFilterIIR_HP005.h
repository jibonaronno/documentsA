#ifndef QFILTERIIR_HP005_H
#define QFILTERIIR_HP005_H

#include "qAbstractFilter.h"

#define USE_1ST_ORDER_IIR_ADS1298
#ifdef USE_1ST_ORDER_IIR_ADS1298

#else
#define USE_BUTTERWORTH_0_05HZ_1ST_ORDER

#undef MWSPT_NSEC

#ifdef USE_BUTTERWORTH_0_05HZ_1ST_ORDER
#define MWSPT_NSEC 3
#else
#define MWSPT_NSEC 7
#endif
#endif

class qFilterIIR_HP005 : public qAbstractFilter
{
public:
    qFilterIIR_HP005();
    virtual void InitLead(int lead);
    virtual int GetFrequencyIndex() { return DRF_005; }

protected:
    virtual void privInit();
    virtual int32_t privFilter(int32_t sample, int lead);

private:
#ifdef USE_1ST_ORDER_IIR_ADS1298
    float x[AMP_IN_LEADS];
    float y[AMP_IN_LEADS];
#else
    double x[AMP_IN_LEADS][MWSPT_NSEC][3];
    double y[AMP_IN_LEADS][MWSPT_NSEC][3];
#endif
};

#endif // QFILTERIIR_HP005_H
