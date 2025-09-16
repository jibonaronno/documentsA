#ifndef QFILTERIIR_HP01_H
#define QFILTERIIR_HP01_H

#include "qAbstractFilter.h"

//#define USE_CUSTOM
#define USE_BUTTERWORTH_0_1HZ_1ST_ORDER

#undef MWSPT_NSEC

#ifdef USE_CUSTOM
#define DELAY   1000
#else
#ifdef USE_BUTTERWORTH_0_1HZ_1ST_ORDER
#define MWSPT_NSEC 3
#else
#define MWSPT_NSEC 3
#endif
#endif

class qFilterIIR_HP01 : public qAbstractFilter
{
public:
    qFilterIIR_HP01();
    virtual void InitLead(int lead);
    virtual int GetFrequencyIndex() { return DRF_01; }

protected:
    virtual void privInit();
    virtual int32_t privFilter(int32_t sample, int lead);

private:
#ifdef USE_CUSTOM
    int32_t buff[AMP_IN_LEADS][DELAY];
    int32_t cummul[AMP_IN_LEADS];
    int32_t avg[AMP_IN_LEADS];
    int inPos;
    int outPos;
#else
    double x[AMP_IN_LEADS][MWSPT_NSEC][3];
    double y[AMP_IN_LEADS][MWSPT_NSEC][3];
#endif
};

#endif // QFILTERIIR_HP01_H
