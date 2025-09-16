#include "qFilterMUS25.h"

#ifdef TFILTER_LPF_25

#define SAMPLEFILTER_TAP_NUM 23

struct SampleFilter {
  int history[SAMPLEFILTER_TAP_NUM];
  unsigned int last_index;
};

static int filter_taps[SAMPLEFILTER_TAP_NUM] = {
  -2947,
  -3502,
  3313,
  -52,
  2131,
  1469,
  2365,
  2429,
  2890,
  3046,
  3245,
  3266,
  3245,
  3046,
  2890,
  2429,
  2365,
  1469,
  2131,
  -52,
  3313,
  -3502,
  -2947
};

qFilterMUS25::qFilterMUS25()
    : qAbstractFilter(SAMPLEFILTER_TAP_NUM/2)
{
    privInit();
}

void qFilterMUS25::InitLead(int lead)
{
    int i;
    for(i = 0; i < SAMPLEFILTER_TAP_NUM; ++i) {
      fData[lead].history[i] = 0;
    }
    fData[lead].last_index = 0;
}

void qFilterMUS25::privInit()
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

int32_t qFilterMUS25::privFilter(int32_t sample, int lead)
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
    return acc/34000;
}
#else

#define T8  ((MUSCLE25_BUF_SIZE-1)/2)
#define T16 (MUSCLE25_BUF_SIZE-1)

#if MUSCLE25_BUF_SIZE == 13
#define MUSCLE25_DIVISOR    36
#define MUSCLE25_DELAY  5
#pragma message("MUS25 cut at 26Hz")
#elif MUSCLE25_BUF_SIZE == 8
#define MUSCLE25_DIVISOR    9
#define MUSCLE25_DELAY  2
#else
#pragma message("MUSCLE25_DIVISOR and MUSCLE25_DELAY must be adjusted")
#define MUSCLE25_DIVISOR    36
#define MUSCLE25_DELAY  5
#endif

qFilterMUS25::qFilterMUS25()
    : qAbstractFilter(MUSCLE25_DELAY)
{
    privInit();
}

void qFilterMUS25::InitLead(int lead)
{
    nn2[lead] = 0;
    yy12[lead] = 0;
    yy22[lead] = 0;
    memset(xx2[lead], 0, sizeof(int)*MUSCLE25_BUF_SIZE*2);
}

void qFilterMUS25::privInit()
{
    memset(nn2, 0, sizeof(int)*AMP_IN_LEADS);
    memset(xx2, 0, sizeof(int)*AMP_IN_LEADS*(MUSCLE25_BUF_SIZE*2));
    memset(yy12, 0, sizeof(int)*AMP_IN_LEADS);
    memset(yy22, 0, sizeof(int)*AMP_IN_LEADS);
}

int32_t qFilterMUS25::privFilter(int32_t sample, int lead)
{
    int yy0, ptr;
    /* H(z) = (1- Z^(-8)](1- Z^(-8)] / [1-Z^(-1)][1-Z^(-1)]
     y(nT) = 2*y(nT-T) +y(nT-2T) + x(nT) - 2*x(nT-8T)+x(nT-16T) */
    ptr = nn2[lead];
    xx2[lead][ptr] = xx2[lead][ptr + MUSCLE25_BUF_SIZE] = sample;
    yy0 = (yy12[lead] << 1) - yy22[lead] + xx2[lead][ptr] -
            (xx2[lead][ptr + T8] << 1) + xx2[lead][ptr + T16];
    yy22[lead] = yy12[lead];
    yy12[lead] = yy0;
    sample = yy0 / MUSCLE25_DIVISOR;

    if (--nn2[lead] < 0)
        nn2[lead] = MUSCLE25_BUF_SIZE-1;
    return sample;
}

#endif /* TFILTER_LPF_25 */
