#include "qFilterLP100.h"

#ifdef TFILTER_LPF_100

#define SAMPLEFILTER_TAP_NUM 5
struct SampleFilter {
  int history[SAMPLEFILTER_TAP_NUM];
  unsigned int last_index;
};

static int filter_taps[SAMPLEFILTER_TAP_NUM] = {
    -2590,
    14977,
    12353,
    14977,
    -2590
};

qFilterLP100::qFilterLP100()
    : qAbstractFilter(SAMPLEFILTER_TAP_NUM/2)
{
    privInit();
}

qFilterLP100::~qFilterLP100()
{
    delete []fData;
}

void qFilterLP100::InitLead(int lead)
{
    int i;
    for(i = 0; i < SAMPLEFILTER_TAP_NUM; ++i) {
      fData[lead].history[i] = 0;
    }
    fData[lead].last_index = 0;
}

void qFilterLP100::privInit()
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

int32_t qFilterLP100::privFilter(int32_t sample, int lead)
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
    return acc/ 36500;
}
#else
#define T16 (LP100_BUF_SIZE-1)

#if LP100_BUF_SIZE == 3
#define LP100_DIVISOR    2
#define LP100_DELAY 0.5
#else
#pragma message("LP100_DIVISOR and LP100_DIVISOR must be adjusted if LP100_BUF_SIZE is changed")
#define LP100_DIVISOR    2
#define LP100_DELAY 0.5
#endif

qFilterLP100::qFilterLP100()
    : qAbstractFilter(LP100_DELAY)
{
    privInit();
}

void qFilterLP100::InitLead(int lead)
{
    yy2L[lead] = 0;
    nnL2[lead] = LP100_BUF_SIZE-1;
    memset(xxL[lead], 0, sizeof(int32_t)*2*LP100_BUF_SIZE);
}

void qFilterLP100::privInit()
{
    memset(yy2L, 0, sizeof(int32_t)*AMP_IN_LEADS);
    memset(xxL, 0, sizeof(int32_t)*2*LP100_BUF_SIZE*AMP_IN_LEADS);
    for(int i=0; i<AMP_IN_LEADS; i++)
        nnL2[i] = T16;
}

int32_t qFilterLP100::privFilter(int32_t sample, int lead)
{
    int yy0, ptr;
    ptr = nnL2[lead];
    xxL[lead][ptr] = xxL[lead][ptr + LP100_BUF_SIZE] = sample;
    yy0 = yy2L[lead] + xxL[lead][ptr] - xxL[lead][ptr + T16];
    yy2L[lead] = yy0;
    if (--nnL2[lead] < 0)
        nnL2[lead] = T16;
    sample = yy0 / LP100_DIVISOR;
    return sample;
}
#endif
