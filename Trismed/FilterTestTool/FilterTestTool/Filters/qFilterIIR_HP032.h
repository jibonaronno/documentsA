#ifndef QFILTERIIR_HP032_H
#define QFILTERIIR_HP032_H

#include "qAbstractFilter.h"

#define USE_BUTTERWORTH_0_32HZ_1ST_ORDER
#undef MWSPT_NSEC

#ifdef USE_BUTTERWORTH_0_32HZ_1ST_ORDER
#define MWSPT_NSEC 3
#else
#define MWSPT_NSEC 3
#endif

class qFilterIIR_HP032 : public qAbstractFilter
{
public:
    qFilterIIR_HP032();
    virtual void InitLead(int lead);
    virtual int GetFrequencyIndex() { return DRF_032; }

protected:
    virtual void privInit();
    virtual int32_t privFilter(int32_t sample, int lead);

private:
    double x[AMP_IN_LEADS][MWSPT_NSEC][3];
    double y[AMP_IN_LEADS][MWSPT_NSEC][3];
};

#endif // QFILTERIIR_HP032_H
