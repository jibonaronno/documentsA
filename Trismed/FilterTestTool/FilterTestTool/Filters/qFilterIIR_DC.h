#ifndef QFILTERIIR_DC_H
#define QFILTERIIR_DC_H

#include "qAbstractFilter.h"

class qFilterIIR_DC : public qAbstractFilter
{
public:
    qFilterIIR_DC();
    virtual void InitLead(int lead);
    virtual int GetFrequencyIndex() { return DRF_005; }

protected:
    virtual void privInit();
    virtual int32_t privFilter(int32_t sample, int lead);

private:
    double x[AMP_IN_LEADS][2];
    double y[AMP_IN_LEADS][2];
};

#endif // QFILTERIIR_DC_H
