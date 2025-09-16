#include "qFilterAC60.h"

#if (AC_60_TYPE == RONNY_FIR_60HZ) || (AC_60_TYPE == RONNY_FIR_60HZ_ORD20)

#if AC_60_TYPE == RONNY_FIR_60HZ
const int16_t B[33] = {
      116,    201,    249,    211,     54,   -219,   -553,   -843,   -958,
     -767,   -190,    771,   2016,   3360,   4565,   5400,   5699,   5400,
     4565,   3360,   2016,    771,   -190,   -767,   -958,   -843,   -553,
     -219,     54,    211,    249,    201,    116
};
#define DIVIDER_60HZ 34000

qFilterAC60::qFilterAC60()
    : qAbstractFilter(17)
{
    privInit();
}
#elif AC_60_TYPE == RONNY_FIR_60HZ_ORD20
#ifdef USE_BANDSTOP_COEFF
const int16_t B[FIR_60HZ_ORDER +1] = {
       17,    -39,    -89,   -116,    -71,     52,    193,    254,    171,
      -25,   -214,   -270,   -169,    -18,     32,    -65,   -176,    -78,
      325,    835,   1018,    507,   -640,  -1827,  -2215,  -1298,    649,
     2588,   3301,   2186,   -274,  -2724,  29026,  -2724,   -274,   2186,
     3301,   2588,    649,  -1298,  -2215,  -1827,   -640,    507,   1018,
      835,    325,    -78,   -176,    -65,     32,    -18,   -169,   -270,
     -214,    -25,    171,    254,    193,     52,    -71,   -116,    -89,
      -39,     17
};
#define AC60_DELAY   33
#else
#if 0
//with Wstop=100
const int16_t B[21] = {
     -152,   -152,    -20,    302,    840,   1576,   2441,   3323,   4088,
     4607,   4792,   4607,   4088,   3323,   2441,   1576,    840,    302,
      -20,   -152,   -152
};
#define DIVIDER_60HZ 38500
#else
const int16_t B[FIR_60HZ_ORDER+1] = {
     -261,   -330,   -255,     37,    587,   1380,   2339,   3333,   4204,
     4800,   5012,   4800,   4204,   3333,   2339,   1380,    587,     37,
     -255,   -330,   -261
};
#define AC60_DELAY 11
#define DIVIDER_60HZ 36500
#endif
#endif

qFilterAC60::qFilterAC60()
    : qAbstractFilter(AC60_DELAY)
{
    privInit();
}
#endif

void qFilterAC60::privInit()
{
#ifdef USE_BANDSTOP_COEFF
    memset(buf_A60, 0, sizeof(int32_t)*(FIR_60HZ_ORDER+1)*(AMP_IN_LEADS));
#else
    memset(buf_A60, 0, sizeof(int32_t)*(FIR_60HZ_ORDER+1)*(AMP_IN_LEADS));
#endif
    memset(offset_A60, 0, sizeof(uint8_t)*(AMP_IN_LEADS));
}

void qFilterAC60::InitLead(int lead)
{
    offset_A60[lead] = 0;
    for(int i=0; i<(FIR_60HZ_ORDER+1); i++) {
        buf_A60[i][lead] = 0;
    }
}

int32_t qFilterAC60::privFilter(int32_t sample, int lead)
{
    uint8_t i;
#ifdef USE_BANDSTOP_COEFF
    double zr = 0;
    const int16_t *coeffs;
#define AC60_FILTER_TYPE    int32_t
#else
    int32_t zr = 0;
    const int16_t *coeffs;
#define AC60_FILTER_TYPE    int32_t
#endif

    coeffs = B;
    buf_A60[lead][offset_A60[lead]] = sample;
    if(lead==0) {
        lead = 0;
    }

    for (i = 0; i < (FIR_60HZ_ORDER+1); i++) {
        zr += static_cast<AC60_FILTER_TYPE>
                (coeffs[i] * (buf_A60[lead][(offset_A60[lead] + i) % (FIR_60HZ_ORDER+1)]));
    }
    offset_A60[lead] = (offset_A60[lead] + 1) % (FIR_60HZ_ORDER+1);
#ifdef USE_BANDSTOP_COEFF
    return static_cast<int32_t>(zr)/32500;
#else
    return static_cast<int32_t>(zr/DIVIDER_60HZ);
#endif
}
#elif AC_60_TYPE == HKLEE_FILTER
qFilterAC60::qFilterAC60()
    : qAbstractFilter(7)
{
    privInit();
}

void qFilterAC60::InitLead(int lead)
{
    Q_UNUSED(lead)
    privInit();
}

void qFilterAC60::privInit()
{
    int lpt, ftr;
    for (lpt = 0; lpt < AMP_IN_LEADS; lpt++) {
        sm0 = sm1[lpt] = sm2[lpt] = 0;
        eadp1[lpt] = eadp2[lpt] = xadp1[lpt] = 0;
        yy1[lpt] = yy2[lpt] = 0;
        nn2[lpt] = 0;
        yy22[lpt] = 0;
        yy12[lpt] = 0;
        for (ftr = 0; ftr <= AC60_BUF_SIZE*2; ftr++) {
            xx[lpt][ftr] = 0;
            xx2[lpt][ftr] = 0;
        }
    }
}

int32_t qFilterAC60::privFilter(int32_t sample, int Lead)
{
    int yy0, ptr;
    /* H(z) = (1- Z^(-8)](1- Z^(-8)] / [1-Z^(-1)][1-Z^(-1)]
     y(nT) = 2*y(nT-T) +y(nT-2T) + x(nT) - 2*x(nT-8T)+x(nT-16T)  */
    ptr = nn2[Lead];
    xx2[Lead][ptr] = xx2[Lead][ptr + T16+1] = sample;
    yy0 = (yy12[Lead] << 1) - yy22[Lead] + xx2[Lead][ptr] - (xx2[Lead][ptr + T8] << 1) + xx2[Lead][ptr + T16];
    yy22[Lead] = yy12[Lead];
    yy12[Lead] = yy0;
    if (--nn2[Lead] < 0)
        nn2[Lead] = T16;
#if AC60_BUF_SIZE == 16
    int yyc;
    yy0 >>= 3;
    yyc = yy0 >> 6;
    yy0 += yyc;
    return yy0 / 8;
#elif AC60_BUF_SIZE == 14
    return yy0 / 49;
#endif
}

#elif AC_60_TYPE == IIR_RONNY_FILTER
static const int NL[MWSPT_NSEC] = { 1,3,1,3,1,3,1 };
static const double NUM[MWSPT_NSEC][3] = {
    {
       0.9993714846137,                 0,                 0
    },
    {
                     1,   -1.457938405985,                 1
    },
    {
       0.9993714846137,                 0,                 0
    },
    {
                     1,   -1.457938405985,                 1
    },
    {
       0.9987449394335,                 0,                 0
    },
    {
                     1,   -1.457938405985,                 1
    },
    {
                     1,                 0,                 0
    }
};
static const int DL[MWSPT_NSEC] = { 1,3,1,3,1,3,1 };
static const double DEN[MWSPT_NSEC][3] = {
    {
                     1,                 0,                 0
    },
    {
                     1,   -1.455531125313,   0.9987426983483
    },
    {
                     1,                 0,                 0
    },
    {
                     1,   -1.458511289754,   0.9987456073277
    },
    {
                     1,                 0,                 0
    },
    {
                     1,   -1.456108604983,   0.9974898788671
    },
    {
                     1,                 0,                 0
    }
};

qFilterAC60::qFilterAC60()
    : qAbstractFilter(0)
{
    privInit();
}

void qFilterAC60::InitLead(int lead)
{
    for(int i=0; i<MWSPT_NSEC; i++) {
        x[lead][i][0] = 0;
        x[lead][i][1] = 0;
        x[lead][i][2] = 0;
        y[lead][i][0] = 0;
        y[lead][i][1] = 0;
        y[lead][i][2] = 0;
    }
}

void qFilterAC60::privInit()
{
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
}

int32_t qFilterAC60::privFilter(int32_t sample, int lead)
{
#if 0
    uint16_t i;
    x[lead][0][0] = sample;
    for(i=0; i<MWSPT_NSEC; i++) {
        y[lead][i][0] =
                x[lead][i][0] * NUM[i][0] +
                x[lead][i][1] * NUM[i][1] +
                x[lead][i][2] * NUM[i][2] -
                y[lead][i][1] * DEN[i][1] -
                y[lead][i][2] * DEN[i][2];

        y[lead][i][0] /= DEN[i][0];

        y[lead][i][2]=y[lead][i][1]; y[lead][i][1]=y[lead][i][0];
        x[lead][i][2]=x[lead][i][1]; x[lead][i][1]=x[lead][i][0];

        x[lead][i+1][0] = y[lead][i][0];
    }
    if( x[lead][MWSPT_NSEC][0] > 32767)  x[lead][MWSPT_NSEC][0] = 32767;
    if( x[lead][MWSPT_NSEC][0] < -32768) x[lead][MWSPT_NSEC][0] = -32768;
    return  static_cast<int32_t>(x[lead][MWSPT_NSEC][0]);
#else
    double w = sample;
    for(int i=0; i < MWSPT_NSEC; i++) {
        x[lead][i][2] = x[lead][i][1];
        x[lead][i][1] = x[lead][i][0];
        x[lead][i][0] = w;
        w=0;
        y[lead][i][2] = y[lead][i][1];
        y[lead][i][1] = y[lead][i][0];
        for ( int j=0; j<NL[i]; j++ )
            w += NUM[i][j] * x[lead][i][j];
        for ( int j=1; j<DL[i]; j++ )
            w -= DEN[i][j] * y[lead][i][j];
        w /= DEN[i][0];
        y[lead][i][0] = w;
    }
    return static_cast<int32_t>(w);
#endif
}
#elif AC_60_TYPE == GARRIDO_AC60_FILTER
#define FLTORDA60 129

const int32_t coeffs_A60[FLTORDA60 / 2 +1] = {
    -141,    664,    255,     95,    -53,   -171,   -200,   -117,     43,
    194,    249,    168,    -17,   -209,   -299,   -227,    -20,    214,
    345,    292,     70,   -207,   -386,   -360,   -131,    186,    417,
    429,    202,   -150,   -436,   -494,   -280,    100,    441,    552,
    362,    -36,   -430,   -600,   -444,    -39,    401,    633,    524,
    123,   -356,   -651,   -595,   -212,    295,    650,    656,    302,
    -221,   -631,   -701,   -390,    137,    593,    730,    470,    -46,
    -539,  32029
};

#define AC60_PACEMAKE_DELAY (FLTORDA60 / 2)

qFilterAC60::qFilterAC60()
    : qAbstractFilter(/*14*/64)
{
    privInit();
}

void qFilterAC60::InitLead(int lead)
{
    offset_A60[lead] = 0;
    for(int i=0; i<BUFSZ_AC60; i++) {
        buf_A60[i][lead] = 0;
    }
}

void qFilterAC60::privInit()
{
    memset(buf_A60, 0, sizeof(int32_t)*BUFSZ_AC60*(AMP_IN_LEADS));
    memset(offset_A60, 0, sizeof(uint8_t)*(AMP_IN_LEADS));
}

int32_t qFilterAC60::privFilter(int32_t sample, int lead)
{
    int32_t zr;
    uint8_t i;
    const int32_t *coeffs;

    coeffs = coeffs_A60;
    buf_A60[offset_A60[lead]][lead] = sample >> 1;

    zr = static_cast<int32_t>(coeffs[FLTORDA60 / 2] * buf_A60[(offset_A60[lead] + BUFSZ_AC60 -(FLTORDA60 / 2)) % (BUFSZ_AC60)][lead]);
    for (i = 0; i < (FLTORDA60 / 2); i++)
        zr += static_cast<int32_t>(coeffs[i] * (buf_A60[(offset_A60[lead] + BUFSZ_AC60 - i) % (BUFSZ_AC60)][lead] +
                                   buf_A60[(offset_A60[lead] + BUFSZ_AC60 - FLTORDA60 + 1 + i) % (BUFSZ_AC60)][lead]));
    offset_A60[lead] = (offset_A60[lead] + 1) % (BUFSZ_AC60);
    return zr/16384;
}
#endif
