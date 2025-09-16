#ifndef QFILTERMUS35_H
#define QFILTERMUS35_H

#include "qAbstractFilter.h"

//#define TFILTER_LPF_35
/*

FIR filter designed with
 http://t-filter.engineerjs.com/

sampling frequency: 500 Hz

fixed point precision: 16 bits

* 0 Hz - 27 Hz
  gain = 1
  desired ripple = 1.5 dB
  actual ripple = n/a

* 35 Hz - 250 Hz
  gain = 0
  desired attenuation = -3 dB
  actual attenuation = n/a

*/

#define MUSCLE35_BUF_SIZE   11//17/*11*//*9*/

class qFilterMUS35 : public qAbstractFilter
{
public:
    qFilterMUS35();
    ~qFilterMUS35();
    virtual void InitLead(int lead);
    virtual int GetFrequencyIndex() { return MUS_35; }

protected:
    virtual void privInit();
    virtual int32_t privFilter(int32_t sample, int lead);

#ifdef TFILTER_LPF_35
    SampleFilter *fData;
#else
    int nn2[AMP_IN_LEADS];
    int xx2[AMP_IN_LEADS][MUSCLE35_BUF_SIZE*2];
    int yy12[AMP_IN_LEADS];
    int yy22[AMP_IN_LEADS];
#endif
};

#endif // QFILTERMUS35_H
