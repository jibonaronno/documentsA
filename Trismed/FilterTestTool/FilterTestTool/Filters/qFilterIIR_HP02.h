#ifndef QFILTERIIR_HP02_H
#define QFILTERIIR_HP02_H

#include "qAbstractFilter.h"
#define USE_BUTTERWORTH_0_2HZ_1ST_ORDER
#undef MWSPT_NSEC

#ifdef USE_BUTTERWORTH_0_2HZ_1ST_ORDER
#define MWSPT_NSEC 3
#else
#define MWSPT_NSEC 3
#endif

class qFilterIIR_HP02 : public qAbstractFilter
{
public:
    qFilterIIR_HP02();
    virtual void InitLead(int lead);
    virtual int GetFrequencyIndex() { return DRF_02; }

protected:
    virtual void privInit();
    virtual int32_t privFilter(int32_t sample, int lead);

private:
    double x[AMP_IN_LEADS][MWSPT_NSEC][3];
    double y[AMP_IN_LEADS][MWSPT_NSEC][3];
};

#endif // QFILTERIIR_HP02_H
