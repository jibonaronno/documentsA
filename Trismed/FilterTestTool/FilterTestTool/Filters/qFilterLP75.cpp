#include "qFilterLP75.h"

#define T16 (LP75_BUF_SIZE-3)

#if LP75_BUF_SIZE == 6
#define LP75_DIVISOR    3
#define LP75_DELAY  1
#else
#pragma message("LP75_DIVISOR and LP75_DELAY must be adjusted if LP75_BUF_SIZE is changed")
#define LP75_DIVISOR    3
#define LP75_DELAY  1
#endif

qFilterLP75::qFilterLP75()
    : qAbstractFilter(LP75_DELAY)
{
    privInit();
}

void qFilterLP75::InitLead(int lead)
{
   yy1L[lead] = 0;
   nnL1[lead] = LP75_BUF_SIZE-1;
   memset(xxL[lead], 0, sizeof(int32_t)*2*LP75_BUF_SIZE);
}

void qFilterLP75::privInit()
{
    memset(yy1L, 0, sizeof(int32_t)*AMP_IN_LEADS);
    memset(xxL, 0, sizeof(int32_t)*2*LP75_BUF_SIZE*AMP_IN_LEADS);
    for(int i = 0; i < AMP_IN_LEADS; i++)
        nnL1[i] = LP75_BUF_SIZE-1; // the original value here was 8, but according to the implementation of LPF1_Filter it should be 6.
}

int32_t qFilterLP75::privFilter(int32_t sample, int lead)
{
    int yy0, ptr;
    ptr = nnL1[lead];
    xxL[lead][ptr] = xxL[lead][ptr + LP75_BUF_SIZE] = sample;
    yy0 = yy1L[lead] + (xxL[lead][ptr] - xxL[lead][ptr + T16]);
    yy1L[lead] = yy0;
    if (--nnL1[lead] < 0)
        nnL1[lead] = LP75_BUF_SIZE-1;
    sample = yy0 / LP75_DIVISOR;
    return sample;
}
