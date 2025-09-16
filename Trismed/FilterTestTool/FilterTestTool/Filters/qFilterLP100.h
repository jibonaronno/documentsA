#ifndef QLP100_H
#define QLP100_H

#include "qAbstractFilter.h"

/*

FIR filter designed with
 http://t-filter.appspot.com

sampling frequency: 500 Hz

fixed point precision: 16 bits

* 0 Hz - 90 Hz
  gain = 1
  desired ripple = 3 dB
  actual ripple = n/a

* 110 Hz - 250 Hz
  gain = 0
  desired attenuation = -3 dB
  actual attenuation = n/a

*/

#define TFILTER_LPF_100

#define LP100_BUF_SIZE   3

class qFilterLP100 : public qAbstractFilter
{
public:
    qFilterLP100();
    ~qFilterLP100();
    virtual void InitLead(int lead);
    virtual int GetFrequencyIndex() { return LPF_100; }

protected:
    virtual void privInit();
    virtual int32_t privFilter(int32_t sample, int lead);
#ifdef TFILTER_LPF_100
    SampleFilter *fData;
#else
    int32_t nnL2[AMP_IN_LEADS];
    int32_t yy2L[AMP_IN_LEADS];
    int32_t xxL[AMP_IN_LEADS][LP100_BUF_SIZE*2];
#endif
};

#endif // QLP100_H
