#ifndef QFILTERAC60_H
#define QFILTERAC60_H

#include "qAbstractFilter.h"

#define HKLEE_FILTER 1
#define GARRIDO_AC60_FILTER 2
#define IIR_RONNY_FILTER 3
#define RONNY_FIR_60HZ 4
#define RONNY_FIR_60HZ_ORD20 5

#define AC_60_TYPE  /*GARRIDO_AC60_FILTER*/RONNY_FIR_60HZ_ORD20

#if AC_60_TYPE == HKLEE_FILTER
#define AC60_BUF_SIZE 16 /*14*/ /* Original values is 16 */
#undef T8
#undef T16
#define T8  ((AC60_BUF_SIZE)/2)
#define T16 (AC60_BUF_SIZE)
#elif AC_60_TYPE == GARRIDO_AC60_FILTER
#define BUFSZ_AC60 140
#elif AC_60_TYPE == IIR_RONNY_FILTER
#define MWSPT_NSEC 7
#elif AC_60_TYPE == RONNY_FIR_60HZ
#define FIR_60HZ_ORDER 32
#elif AC_60_TYPE == RONNY_FIR_60HZ_ORD20
//#define USE_BANDSTOP_COEFF
#ifdef USE_BANDSTOP_COEFF
#define FIR_60HZ_ORDER 64
#else
#define FIR_60HZ_ORDER 20
#endif
#else
#error Invalid implementation!!
#endif


class qFilterAC60 : public qAbstractFilter
{
public:
    qFilterAC60();
    virtual void InitLead(int lead);
    virtual int GetFrequencyIndex() { return ACF_60; }

protected:
    virtual void privInit();
    virtual int32_t privFilter(int32_t sample, int lead);
#if (AC_60_TYPE == HKLEE_FILTER)
    int yy1[AMP_IN_LEADS], yy2[AMP_IN_LEADS], xx[AMP_IN_LEADS][AC60_BUF_SIZE*2+1];
    int nn2[AMP_IN_LEADS], yy12[AMP_IN_LEADS], yy22[AMP_IN_LEADS], xx2[AMP_IN_LEADS][AC60_BUF_SIZE*2+1];
    int sm0, sm1[AMP_IN_LEADS], sm2[AMP_IN_LEADS];
    int eadp1[AMP_IN_LEADS], eadp2[AMP_IN_LEADS], xadp1[AMP_IN_LEADS];
    int nnL[AMP_IN_LEADS], yy1L[AMP_IN_LEADS], yy2L[AMP_IN_LEADS];
#elif (AC_60_TYPE == IIR_RONNY_FILTER)
    double x[AMP_IN_LEADS][MWSPT_NSEC][3];
    double y[AMP_IN_LEADS][MWSPT_NSEC][3];
#elif (AC_60_TYPE == GARRIDO_AC60_FILTER)
    int32_t buf_A60[BUFSZ_AC60 +1][AMP_IN_LEADS];
    uint8_t offset_A60[AMP_IN_LEADS];
#elif (AC_60_TYPE == RONNY_FIR_60HZ) || (AC_60_TYPE == RONNY_FIR_60HZ_ORD20)
#ifdef USE_BANDSTOP_COEFF
    int32_t buf_A60[AMP_IN_LEADS][FIR_60HZ_ORDER+1];
#else
    int32_t buf_A60[AMP_IN_LEADS][FIR_60HZ_ORDER+1];
#endif
    uint8_t offset_A60[AMP_IN_LEADS];
#endif
};

#endif // QFILTERAC60_H
