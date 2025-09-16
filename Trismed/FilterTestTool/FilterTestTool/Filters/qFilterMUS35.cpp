#include "qFilterMUS35.h"
// sfrec=500Hz (2ms)

#ifdef TFILTER_LPF_35
#define SAMPLEFILTER_TAP_NUM 15

struct SampleFilter {
  int history[SAMPLEFILTER_TAP_NUM];
  unsigned int last_index;
};

static int filter_taps[SAMPLEFILTER_TAP_NUM] = {
  -8621,
  4291,
  3851,
  3729,
  3780,
  3886,
  3988,
  4016,
  3988,
  3886,
  3780,
  3729,
  3851,
  4291,
  -8621
};

qFilterMUS35::qFilterMUS35()
    : qAbstractFilter(SAMPLEFILTER_TAP_NUM/2)
{
    privInit();
}

qFilterMUS35::~qFilterMUS35()
{
    delete []fData;
}

void qFilterMUS35::InitLead(int lead)
{
    int i;
    for(i = 0; i < SAMPLEFILTER_TAP_NUM; ++i) {
      fData[lead].history[i] = 0;
    }
    fData[lead].last_index = 0;
}

void qFilterMUS35::privInit()
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

int32_t qFilterMUS35::privFilter(int32_t sample, int lead)
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
#define T8  ((MUSCLE35_BUF_SIZE-1)/2)
#define T16 (MUSCLE35_BUF_SIZE-1)

#if MUSCLE35_BUF_SIZE == 11
#pragma message("MUS35 cut at 32.5Hz")
#define MUSCLE35_DIVISOR 25
#define MUSCLE35_DELAY 4
#elif MUSCLE35_BUF_SIZE == 9
#pragma message("MUS35 cut at 40Hz")
#define MUSCLE35_DIVISOR 16
#define MUSCLE35_DELAY 3
#elif MUSCLE35_BUF_SIZE == 17
#define MUSCLE35_DIVISOR 58
#define MUSCLE35_DELAY 6
#else
#warning Untested MUSCLE35_BUF_SIZE. MUSCLE35_DIVISOR must be adjusted
#define MUSCLE35_DIVISOR 16
#define MUSCLE35_DELAY 3
#endif

qFilterMUS35::qFilterMUS35()
    : qAbstractFilter(MUSCLE35_DELAY)
{
    privInit();
}

qFilterMUS35::~qFilterMUS35()
{
}


void qFilterMUS35::InitLead(int lead)
{
    nn2[lead] = 0;
    yy12[lead] = 0;
    yy22[lead] = 0;
    memset(xx2[lead], 0, sizeof(int)*MUSCLE35_BUF_SIZE*2);
}

void qFilterMUS35::privInit()
{
    memset(nn2, 0, sizeof(int)*AMP_IN_LEADS);
    memset(xx2, 0, sizeof(int)*AMP_IN_LEADS*(MUSCLE35_BUF_SIZE*2));
    memset(yy12, 0, sizeof(int)*AMP_IN_LEADS);
    memset(yy22, 0, sizeof(int)*AMP_IN_LEADS);
}

int32_t qFilterMUS35::privFilter(int32_t sample, int lead)
{
    int yy0, ptr;
    /* H(z) = (1- Z^(-8)](1- Z^(-8)] / [1-Z^(-1)][1-Z^(-1)]
     y(nT) = 2*y(nT-T) +y(nT-2T) + x(nT) - 2*x(nT-8T)+x(nT-16T) */
    ptr = nn2[lead];
    xx2[lead][ptr] = xx2[lead][ptr + MUSCLE35_BUF_SIZE] = sample;
    yy0 = (yy12[lead] << 1) - yy22[lead] + xx2[lead][ptr] -
            (xx2[lead][ptr + T8] << 1) + xx2[lead][ptr + T16];
    yy22[lead] = yy12[lead];
    yy12[lead] = yy0;
#if MUSCLE35_BUF_SIZE == 17
    yy0 >>= 3;
    sample += yy0;
    sample = sample / 8;
#else
    sample = static_cast<int32_t>(yy0/MUSCLE35_DIVISOR);
#endif
    if (--nn2[lead] < 0)
        nn2[lead] = MUSCLE35_BUF_SIZE-1;
    return sample;
}
#endif /* TFILTER_LPF_35 */
