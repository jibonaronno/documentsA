#ifndef QFILTERMUS25_H
#define QFILTERMUS25_H

#include "qAbstractFilter.h"

//#define TFILTER_LPF_25
/*

FIR filter designed with
 http://t-filter.appspot.com

sampling frequency: 500 Hz

fixed point precision: 16 bits

* 0 Hz - 17 Hz
  gain = 1
  desired ripple = 1 dB
  actual ripple = n/a

* 30 Hz - 250 Hz
  gain = 0
  desired attenuation = -3 dB
  actual attenuation = n/a

*/

#define MUSCLE25_BUF_SIZE   13
//#define MUSCLE25_BUF_SIZE   8

class qFilterMUS25 : public qAbstractFilter
{
public:
    qFilterMUS25();
    virtual void InitLead(int lead);
    virtual int GetFrequencyIndex() { return MUS_25; }

protected:
    virtual void privInit();
    virtual int32_t privFilter(int32_t sample, int lead);

#ifdef TFILTER_LPF_25
    SampleFilter *fData;
#else
    int nn2[AMP_IN_LEADS];
    int xx2[AMP_IN_LEADS][MUSCLE25_BUF_SIZE*2];
    int yy12[AMP_IN_LEADS];
    int yy22[AMP_IN_LEADS];
#endif
};

#endif // QFILTERMUS25_H
