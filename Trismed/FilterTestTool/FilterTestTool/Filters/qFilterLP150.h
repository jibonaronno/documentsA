#ifndef QLP150_H
#define QLP150_H

#include "qAbstractFilter.h"

//#define TFILTER_LPF_150
/*

FIR filter designed with
 http://t-filter.appspot.com

sampling frequency: 500 Hz

fixed point precision: 16 bits

* 0 Hz - 140 Hz
  gain = 1
  desired ripple = 1.5 dB
  actual ripple = n/a

* 150 Hz - 250 Hz
  gain = 0
  desired attenuation = -3 dB
  actual attenuation = n/a

*/

#define LP150_BUF_SIZE   3

class qFilterLP150 : public qAbstractFilter
{
public:
    qFilterLP150();
    ~qFilterLP150();
    virtual void InitLead(int lead);
    virtual int GetFrequencyIndex() { return LPF_150; }

protected:
    void privInit();
    virtual int32_t privFilter(int32_t sample, int lead);
#ifdef TFILTER_LPF_150
    SampleFilter *fData;
#else
    int32_t nnL3[AMP_IN_LEADS];
    int32_t yy3L[AMP_IN_LEADS];
    int32_t xxL[AMP_IN_LEADS][2*LP150_BUF_SIZE];
#endif
};

#endif // QLP150_H
