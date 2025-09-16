#ifndef QFILTERAC50_H
#define QFILTERAC50_H

#include "qAbstractFilter.h"

#define GARRIDO_AC50_FILTER 1
#define COMB_FILTER 2
#define RONNY_FIR_50HZ 3
#define RONNY_FIR_50HZ_ORD20 4

#define AC_50_TYPE  RONNY_FIR_50HZ_ORD20

#if AC_50_TYPE == GARRIDO_AC50_FILTER
#define BUFSZ_AC50 140
#elif AC_50_TYPE == COMB_FILTER
#define AC50_BUF_SIZE 20 /*18*/ /*16*/ /*14*/ /* Original values is 16 */
#define T8  ((AC50_BUF_SIZE)/2)
#define T16 (AC50_BUF_SIZE)
#elif AC_50_TYPE == RONNY_FIR_50HZ
#define FIR_ORDER 32
#elif AC_50_TYPE == RONNY_FIR_50HZ_ORD20
#define FIR_ORDER 20
#else
#error Invalid implementation!!!
#endif

class qFilterAC50 : public qAbstractFilter
{
public:
    qFilterAC50();
    void InitLead(int lead) override;
    virtual int GetFrequencyIndex() override { return ACF_50; }

protected:
    void privInit() override;
    virtual int32_t privFilter(int32_t sample, int lead) override;
#if AC_50_TYPE == GARRIDO_AC50_FILTER
    int32_t buf_A50[BUFSZ_AC50][AMP_IN_LEADS];
    uint8_t offset_A50[AMP_IN_LEADS];
#elif AC_50_TYPE == COMB_FILTER
    int yy1[AMP_IN_LEADS], yy2[AMP_IN_LEADS], xx[AMP_IN_LEADS][AC50_BUF_SIZE*2+1];
    int nn2[AMP_IN_LEADS], yy12[AMP_IN_LEADS], yy22[AMP_IN_LEADS], xx2[AMP_IN_LEADS][AC50_BUF_SIZE*2+1];
    int sm0, sm1[AMP_IN_LEADS], sm2[AMP_IN_LEADS];
    int eadp1[AMP_IN_LEADS], eadp2[AMP_IN_LEADS], xadp1[AMP_IN_LEADS];
    int nnL[AMP_IN_LEADS], yy1L[AMP_IN_LEADS], yy2L[AMP_IN_LEADS];
#elif (AC_50_TYPE == RONNY_FIR_50HZ) || (AC_50_TYPE == RONNY_FIR_50HZ_ORD20)
    int32_t buf_A50[AMP_IN_LEADS][FIR_ORDER+1];
    uint8_t offset_A50[AMP_IN_LEADS];
#endif
};

#endif // QFILTERAC50_H
