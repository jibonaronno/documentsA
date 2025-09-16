#include "qFilterAC50.h"
#if (AC_50_TYPE == RONNY_FIR_50HZ) || (AC_50_TYPE == RONNY_FIR_50HZ_ORD20)
#if AC_50_TYPE == RONNY_FIR_50HZ
const int16_t B[FIR_ORDER+1] = {
    -6,   -110,   -273,   -480,   -697,   -872,   -944,   -855,   -561,
    -44,    679,   1552,   2488,   3382,   4121,   4608,   4779,   4608,
    4121,   3382,   2488,   1552,    679,    -44,   -561,   -855,   -944,
    -872,   -697,   -480,   -273,   -110,     -6
};

qFilterAC50::qFilterAC50()
    : qAbstractFilter(17)
{
    privInit();
}
#elif AC_50_TYPE == RONNY_FIR_50HZ_ORD20
const int16_t B[21] = {
       31,    225,    535,    959,   1480,   2062,   2654,   3200,   3640,
     3926,   4026,   3926,   3640,   3200,   2654,   2062,   1480,    959,
      535,    225,     31
};

#define DIVIDER_50HZ 42000

qFilterAC50::qFilterAC50()
    : qAbstractFilter(11)
{
    memset(buf_A50, 0, sizeof(int32_t)*(FIR_ORDER+1)*(AMP_IN_LEADS));
    memset(offset_A50, 0, sizeof(uint8_t)*(AMP_IN_LEADS));
}
#endif

void qFilterAC50::privInit()
{
    memset(buf_A50, 0, sizeof(int32_t)*(FIR_ORDER+1)*(AMP_IN_LEADS));
    memset(offset_A50, 0, sizeof(uint8_t)*(AMP_IN_LEADS));
}

void qFilterAC50::InitLead(int lead)
{
    offset_A50[lead] = 0;
    for(int i=0; i<(FIR_ORDER+1); i++) {
        buf_A50[i][lead] = 0;
    }
}

int32_t qFilterAC50::privFilter(int32_t sample, int lead)
{
    int32_t zr = 0;
    uint8_t i;
    const int16_t *coeffs;
    coeffs = B;
    buf_A50[lead][offset_A50[lead]] = sample;

    for (i = 0; i < (FIR_ORDER+1); i++) {
        zr += static_cast<int32_t>
                (coeffs[i] * (buf_A50[lead][(offset_A50[lead] + i) % (FIR_ORDER+1)]));
    }
    offset_A50[lead] = (offset_A50[lead] + 1) % (FIR_ORDER+1);

    return static_cast<int32_t>(zr/DIVIDER_50HZ);
}

#elif AC_50_TYPE == COMB_FILTER
qFilterAC50::qFilterAC50()
#if AC50_BUF_SIZE == 14
    : qAbstractFilter(6)
    #elif AC50_BUF_SIZE == 16
    : qAbstractFilter(7)
    #elif AC50_BUF_SIZE == 18
    : qAbstractFilter(8)
    #elif AC50_BUF_SIZE == 20
    : qAbstractFilter(9)
    #else
    : qAbstractFilter(0)
    #error Unadjusted filter delay!!!
    #endif
{

}

void qFilterAC50::InitLead(int lead)
{
    Q_UNUSED(lead)
    privInit();
}

void qFilterAC50::privInit()
{
    int lpt, ftr;
    for (lpt = 0; lpt < AMP_IN_LEADS; lpt++) {
        sm0 = sm1[lpt] = sm2[lpt] = 0;
        eadp1[lpt] = eadp2[lpt] = xadp1[lpt] = 0;
        yy1[lpt] = yy2[lpt] = 0;
        nn2[lpt] = 0;
        yy22[lpt] = 0;
        yy12[lpt] = 0;
        for (ftr = 0; ftr <= AC50_BUF_SIZE*2; ftr++) {
            xx[lpt][ftr] = 0;
            xx2[lpt][ftr] = 0;
        }
    }
}

int32_t qFilterAC50::privFilter(int32_t sample, int Lead)
{
    int yy0, ptr;
    /* H(z) = [1- Z^(-8)][1- Z^(-8)] / [1-Z^(-1)][1-Z^(-1)]
     y(nT) = 2*y(nT-T) +y(nT-2T) + x(nT) - 2*x(nT-8T)+x(nT-16T)  */
    ptr = nn2[Lead];
    xx2[Lead][ptr] = xx2[Lead][ptr + T16+1] = sample;
    yy0 = (yy12[Lead] << 1) - yy22[Lead] + xx2[Lead][ptr] - (xx2[Lead][ptr + T8] << 1) + xx2[Lead][ptr + T16];
    yy22[Lead] = yy12[Lead];
    yy12[Lead] = yy0;
    if (--nn2[Lead] < 0)
        nn2[Lead] = T16;
#if AC50_BUF_SIZE == 16
    int yyc;
    yy0 >>= 3;
    yyc = yy0 >> 6;
    yy0 += yyc;
    return yy0 / 8;
#elif AC50_BUF_SIZE == 14
    return yy0 / 49;
#elif AC50_BUF_SIZE == 18
    return yy0 / 81;
#elif AC50_BUF_SIZE == 20
    return yy0 / 100;
#else
#error Unadjusted gain!!!
#endif
}
#elif AC_50_TYPE == GARRIDO_AC50_FILTER

#define FLTORDA50 129
static const int32_t coeffs_A50[ FLTORDA50 / 2 + 1 ] = {
    556,   -161,   -215,   -270,   -287,   -238,   -127,     18,    146,
    210,    181,     63,    -98,   -243,   -308,   -259,   -106,     99,
    278,    358,    301,    119,   -123,   -333,   -424,   -354,   -140,
    141,    382,    486,    403,    158,   -161,   -431,   -545,   -451,
    -176,    178,    476,    599,    493,    192,   -194,   -516,   -647,
    -531,   -206,    207,    549,    686,    560,    216,   -217,   -574,
    -715,   -582,   -224,    225,    591,    733,    594,    228,   -228,
    -597,  32029
};

#define AC50_PACEMAKE_DELAY (FLTORDA50 / 2)

qFilterAC50::qFilterAC50()
    : qAbstractFilter(/*14*/64)
{
    privInit();
}

void qFilterAC50::InitLead(int lead)
{
    offset_A50[lead] = 0;
    for(int i=0; i<BUFSZ_AC50; i++) {
        buf_A50[i][lead] = 0;
    }
}

void qFilterAC50::privInit()
{
    memset(buf_A50, 0, sizeof(int32_t)*BUFSZ_AC50*(AMP_IN_LEADS));
    memset(offset_A50, 0, sizeof(uint8_t)*(AMP_IN_LEADS));
}

int32_t qFilterAC50::privFilter(int32_t sample, int lead)
{
    int32_t zr;
    uint8_t i;
    const int32_t *coeffs;

    coeffs = coeffs_A50;
    buf_A50[offset_A50[lead]][lead] = sample >> 1;

    zr = static_cast<int32_t>(coeffs[FLTORDA50 / 2] * buf_A50[(offset_A50[lead] + BUFSZ_AC50 - (FLTORDA50 / 2)) % (BUFSZ_AC50)][lead]);
    for (i = 0; i < (FLTORDA50 / 2); i++)
        zr += static_cast<int32_t>
                (coeffs[i] * (buf_A50[(offset_A50[lead] + BUFSZ_AC50 - i) % (BUFSZ_AC50)][lead] +
                 buf_A50[(offset_A50[lead] + BUFSZ_AC50 - FLTORDA50 + 1 + i) % (BUFSZ_AC50)][lead]));
    offset_A50[lead] = (offset_A50[lead] + 1) % (BUFSZ_AC50);

    return static_cast<int32_t>(zr/16384);
}

#endif
