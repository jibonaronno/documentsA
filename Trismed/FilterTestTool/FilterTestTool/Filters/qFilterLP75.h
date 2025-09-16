#ifndef QLP75_H
#define QLP75_H

#include "qAbstractFilter.h"

#define LP75_BUF_SIZE   6

class qFilterLP75 : public qAbstractFilter
{
public:
    qFilterLP75();
    virtual void InitLead(int lead);
    virtual int GetFrequencyIndex() { return LPF_75; }

protected:
    void privInit();
    virtual int32_t privFilter(int32_t sample, int lead);

    int32_t nnL1[AMP_IN_LEADS];
    int32_t yy1L[AMP_IN_LEADS];
    int32_t xxL[AMP_IN_LEADS][LP75_BUF_SIZE*2];
};

#endif // QLP75_H
