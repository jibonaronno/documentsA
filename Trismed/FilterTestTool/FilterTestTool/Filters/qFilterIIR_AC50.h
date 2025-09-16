#ifndef QFILTERIIR_AC50_H
#define QFILTERIIR_AC50_H

#include "qAbstractFilter.h"

#undef MWSPT_NSEC
#define MWSPT_NSEC 3

class qFilterIIR_AC50 : public qAbstractFilter
{
public:
    qFilterIIR_AC50();
    virtual void InitLead(int lead);
    virtual int GetFrequencyIndex() { return ACF_50; }

protected:
    virtual void privInit();
    virtual int32_t privFilter(int32_t sample, int lead);

private:
    double x[AMP_IN_LEADS][MWSPT_NSEC][3];
    double y[AMP_IN_LEADS][MWSPT_NSEC][3];
};

#endif // QFILTERIIR_AC50_H
