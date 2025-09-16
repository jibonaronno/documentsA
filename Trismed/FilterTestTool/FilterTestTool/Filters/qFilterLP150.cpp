#include "qFilterLP150.h"
#ifdef TFILTER_LPF_150

#define SAMPLEFILTER_TAP_NUM 13

struct SampleFilter {
  int history[SAMPLEFILTER_TAP_NUM];
  unsigned int last_index;
};

static int filter_taps[SAMPLEFILTER_TAP_NUM] = {
  584,
  -4408,
  6029,
  -4130,
  -2633,
  10532,
  18717,
  10532,
  -2633,
  -4130,
  6029,
  -4408,
  584
};

qFilterLP150::qFilterLP150()
    : qAbstractFilter(SAMPLEFILTER_TAP_NUM/2)
{
    privInit();
}

qFilterLP150::~qFilterLP150()
{
    delete []fData;
}

void qFilterLP150::InitLead(int lead)
{
    int i;
    for(i = 0; i < SAMPLEFILTER_TAP_NUM; ++i) {
      fData[lead].history[i] = 0;
    }
    fData[lead].last_index = 0;
}

void qFilterLP150::privInit()
{
    fData = new struct SampleFilter[SAMPLEFILTER_TAP_NUM];
    int i;
    for(int lead=0; lead<AMP_IN_LEADS; lead++) {
        for(i = 0; i < SAMPLEFILTER_TAP_NUM; ++i) {
            fData[lead].history[i] = 0;
        }
        fData[lead].last_index = 0;
    }
}

int32_t qFilterLP150::privFilter(int32_t sample, int lead)
{
    fData[lead].history[fData[lead].last_index++] = sample;
    if(fData[lead].last_index == SAMPLEFILTER_TAP_NUM)
      fData[lead].last_index = 0;
    long long acc = 0;
    int index = fData[lead].last_index, i;
    for(i = 0; i < SAMPLEFILTER_TAP_NUM; ++i) {
      index = index != 0 ? index-1 : SAMPLEFILTER_TAP_NUM-1;
      acc += (long long)fData[lead].history[index] * filter_taps[i];
    };
    return acc/ 32768; //>> 15;
}
#else
#define T16 (LP150_BUF_SIZE-1)
#define T8  ((LP150_BUF_SIZE-1)/2)

#if LP150_BUF_SIZE == 3
#define LP150_DIVISOR    3
#define LP150_DELAY 0.66
#else
#pragma message("LP150_DIVISOR and LP150_DELAY must be adjusted if LP150_BUF_SIZE is changed")
#define LP150_DIVISOR    3
#define LP150_DELAY 0.66
#endif

qFilterLP150::qFilterLP150()
    : qAbstractFilter(LP150_DELAY)
{
    privInit();
}

qFilterLP150::~qFilterLP150() {

}

void qFilterLP150::InitLead(int lead)
{
    yy3L[lead] = 0;
    nnL3[lead] = LP150_BUF_SIZE-1;
    memset(xxL[lead], 0, sizeof(int32_t)*2*LP150_BUF_SIZE);
}

void qFilterLP150::privInit()
{
    memset(yy3L, 0, sizeof(int32_t)*AMP_IN_LEADS);
    memset(xxL, 0, sizeof(int32_t)*2*LP150_BUF_SIZE*AMP_IN_LEADS);
    for(int i = 0; i < AMP_IN_LEADS; i++)
        nnL3[i] = T16;
}

int32_t qFilterLP150::privFilter(int32_t sample, int lead)
{
    int yy0, ptr;
    ptr = nnL3[lead];
    xxL[lead][ptr] = xxL[lead][ptr + LP150_BUF_SIZE] = sample;
    yy0 = yy3L[lead] + xxL[lead][ptr] - (xxL[lead][ptr + T16] << 1) + (xxL[lead][ptr + T8]);
    yy3L[lead] = yy0;
    if (--nnL3[lead] < 0)
        nnL3[lead] = T16;
    sample = yy0 / LP150_DIVISOR;
    return sample;
}
#endif /*TFILTER_LPF_150*/
