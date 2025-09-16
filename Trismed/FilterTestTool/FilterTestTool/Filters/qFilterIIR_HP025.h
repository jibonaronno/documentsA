#ifndef QFILTERIIR_HP025_H
#define QFILTERIIR_HP025_H

#include "qAbstractFilter.h"

#define USE_BUTTERWORTH_0_25HZ_1ST_ORDER
#undef MWSPT_NSEC

#ifdef USE_BUTTERWORTH_0_25HZ_1ST_ORDER
#define MWSPT_NSEC 3
#else
#define MWSPT_NSEC 3
#endif

class qFilterIIR_HP025 : public qAbstractFilter
{
public:
    qFilterIIR_HP025();
    virtual void InitLead(int lead);
    virtual int GetFrequencyIndex() { return DRF_025; }

protected:
    virtual void privInit();
    virtual int32_t privFilter(int32_t sample, int lead);

private:
    double x[AMP_IN_LEADS][MWSPT_NSEC][3];
    double y[AMP_IN_LEADS][MWSPT_NSEC][3];
};

#endif // QFILTERIIR_HP025_H
