#include "ECGFilter_AC.h"

#ifdef CARDIOFFICE_NEW_AC
#ifdef CARDIOFFICE_NEW_FIR_AC

#define Ntap 31

const double FIRCoef_500_60[Ntap] = {
    -0.00362979537523076040,
    0.00479684600063847580,
    0.01094079236357111400,
    0.01129866627560272500,
    0.00541848261682585480,
    -0.00371609314484288660,
    -0.01118926666712456900,
    -0.01279288604659050600,
    -0.00738802685474189340,
    0.00233279175299956010,
    0.01117368572119855100,
    0.01420662177926380000,
    0.00951110259344984010,
    -0.00063700488164796485,
    -0.01085089042704254400,
    0.96104994858734261000,
    -0.01085089042704254400,
    -0.00063700488164796485,
    0.00951110259344984010,
    0.01420662177926380000,
    0.01117368572119855100,
    0.00233279175299956010,
    -0.00738802685474189340,
    -0.01279288604659050600,
    -0.01118926666712456900,
    -0.00371609314484288660,
    0.00541848261682585480,
    0.01129866627560272500,
    0.01094079236357111400,
    0.00479684600063847580,
    -0.00362979537523076040
};

ECGFilter_AC::ECGFilter_AC(TACFilters frequency, int samplingFrequency)
    : qAbstractFilter(Ntap/2)
{
    mSamplingFrequency = samplingFrequency;
    mFrequency = frequency;
    for(int i=0; i<AMP_IN_LEADS; i++) {
        x[i] = nullptr;
    }
}

ECGFilter_AC::~ECGFilter_AC()
{
    for(int i=0; i<AMP_IN_LEADS; i++) {
        delete [] x[i];
    }
}

void ECGFilter_AC::InitLead(int lead)
{
    for(int i=0; i<Ntap; i++) {
        x[lead][i] = 0;
    }
}

void ECGFilter_AC::privInit()
{
    if(x[0] != nullptr) {
        for(int i=0; i<AMP_IN_LEADS; i++) {
            delete [] x[i];
        }
    }

    for(int i=0; i<AMP_IN_LEADS; i++) {
        x[i] = new double[Ntap];
        InitLead(i);
    }

    switch (mFrequency) {
    case ACF_50:
        switch (mSamplingFrequency) {
        case 250:
            FIRCoef = FIRCoef_500_60;
            break;
        case 500:
            FIRCoef = FIRCoef_500_60;
            break;
        default: // case 1000:
            FIRCoef = FIRCoef_500_60;
            break;
        }
        break;
    default:  // ACF_60:
        switch (mSamplingFrequency) {
        case 250:
            FIRCoef = FIRCoef_500_60;
            break;
        case 500:
            FIRCoef = FIRCoef_500_60;
            break;
        default: // case 1000:
            FIRCoef = FIRCoef_500_60;
            break;
        }
        break;
    }
}

int32_t ECGFilter_AC::privFilter(int32_t sample, int lead)
{
    int n;
    double output = 0;

    //shift the old samples
    for(n=Ntap-1; n>0; n--)
       x[lead][n] = x[lead][n-1];

    //Calculate the new output
    x[lead][0] = sample;
    for(n=0; n<Ntap; n++)
        output += FIRCoef[n] * x[lead][n];

    return static_cast<int32_t>(output);
}
#else
//#define USE_ORDER_2

#ifdef USE_ORDER_2
#warning This one has more ringing after pulses
#define NCoef 4
static const double ACoef_500_60[NCoef+1] = {
    0.92250197436706172000,
    -2.69074975980170010000,
    3.80709575749161640000,
    -2.69074975980170010000,
    0.92250197436706172000
};

static const double BCoef_500_60[NCoef+1] = {
    1.00000000000000000000,
    -2.86498044033993880000,
    3.98159640450767900000,
    -2.76490763422394490000,
    0.93138168206984417000
};

#else
// Filter type: Band Stop
// Filter model: Butterworth
// Filter order: 1
// Sampling Frequency: 500 Hz
// Fc1 and Fc2 Frequencies: 58.000000 Hz and 62.000000 Hz
// Coefficents Quantization: float

// Tests notes: Order 2 or higher increase the ringing after pulses.
//              Also using Chevichev increases the ringing
//              Separating Fc1 and Fc2 decreases attenuetion (bad) and ringing (good)
//              Bringing closer Fc1 and Fc2 increases attenuation (good) and ringing (bad)

#define NCoef 2
static const double ACoef_500_60[NCoef+1] = {
    0.94655074441985865000,
    -1.38044755402032140000,
    0.94655074441985865000
};
static const double BCoef_500_60[NCoef+1] = {
    1.00000000000000000000,
    -1.42263557070365000000,
    0.95095678145114293000
};

// Filter type: Band Stop
// Filter model: Butterworth
// Filter order: 1
// Sampling Frequency: 500 Hz
// Fc1 and Fc2 Frequencies: 48.000000 Hz and 52.000000 Hz
// Coefficents Quantization: float

static const double ACoef_500_50[NCoef+1] = {
    1.00478012187330120000,
    -1.62628198569072050000,
    1.00478012187330120000
};

static const double BCoef_500_50[NCoef+1] = {
    1.00000000000000000000,
    -1.57885581108267030000,
    0.95095678145431706000
};

#endif


ECGFilter_AC::ECGFilter_AC(TACFilters frequency, int samplingFrequency)
    : qAbstractFilter(2)
{
    mSamplingFrequency = samplingFrequency;
    mFrequency = frequency;

    for(int i=0; i<AMP_IN_LEADS; i++) {
        y[i] = nullptr;
        x[i] = nullptr;
    }
}

ECGFilter_AC::~ECGFilter_AC()
{
    for(int i=0; i<AMP_IN_LEADS; i++) {
        delete [] y[i];
        delete [] x[i];
    }
}

void ECGFilter_AC::InitLead(int lead)
{
    for(int i=0; i<NCoef+1; i++) {
        x[lead][i] = 0;
        x[lead][i] = 0;
        x[lead][i] = 0;
        y[lead][i] = 0;
        y[lead][i] = 0;
        y[lead][i] = 0;
    }
}

void ECGFilter_AC::privInit()
{
    if(x[0] != nullptr) {
        for(int i=0; i<AMP_IN_LEADS; i++) {
            delete [] y[i];
            delete [] x[i];
        }
    }

    for(int i=0; i<AMP_IN_LEADS; i++) {
        x[i] = new float[NCoef+1];
        y[i] = new float[NCoef+1];
        InitLead(i);
    }

    switch (mFrequency) {
    case ACF_50:
        switch (mSamplingFrequency) {
        case 250:
            ACoef = ACoef_500_60;
            BCoef = BCoef_500_60;
            break;
        case 500:
            ACoef = ACoef_500_50;
            BCoef = BCoef_500_50;
            break;
        default: // case 1000:
            ACoef = ACoef_500_60;
            BCoef = BCoef_500_60;
            break;
        }
        break;
    default:  // ACF_60:
        switch (mSamplingFrequency) {
        case 250:
            ACoef = ACoef_500_60;
            BCoef = BCoef_500_60;
            //filtersamplevalue = new FilterSampleValueDelegateF(FilterSampleValue_60_250);
            break;
        case 500:
            ACoef = ACoef_500_60;
            BCoef = BCoef_500_60;
            //filtersamplevalue = new FilterSampleValueDelegateF(FilterSampleValue_60_500);
            break;
        default: // case 1000:
            ACoef = ACoef_500_60;
            BCoef = BCoef_500_60;
            //filtersamplevalue = new FilterSampleValueDelegateF(FilterSampleValue_60_1000);
            break;
        }
        break;
    }
}

int32_t ECGFilter_AC::privFilter(int32_t sample, int lead)
{
    int n;

    //shift the old samples
    for(n=NCoef; n>0; n--) {
        x[lead][n] = x[lead][n-1];
        y[lead][n] = y[lead][n-1];
    }

    //Calculate the new output
    x[lead][0] = sample;
    y[lead][0] = ACoef[0] * x[lead][0];
    for(n=1; n<=NCoef; n++)
        y[lead][0] += ACoef[n] * x[lead][n] - BCoef[n] * y[lead][n];
    return y[lead][0];
}
#endif /* CARDIOFFICE_NEW_FIR_AC */

void ECGFilter_AC::SetAcFilterType(TACFilters frequency)
{
    mFrequency = frequency;
    privInit();
}
#else
ECGFilter_AC::ECGFilter_AC(TACFilters frequency, int samplingFrequency)
    : qAbstractFilter(2)
{
    mSamplingFrequency = samplingFrequency;
    mFrequency = frequency;
    xn1 = nullptr;
    xn2 = nullptr;
    yn1 = nullptr;
    yn2 = nullptr;
}

void ECGFilter_AC::SetAcFilterType(TACFilters frequency)
{
    mFrequency = frequency;
    privInit();
}

ECGFilter_AC::~ECGFilter_AC()
{
    delete [] xn1;
    delete [] xn2;
    delete [] yn1;
    delete [] yn2;
}

void ECGFilter_AC::InitLead(int lead)
{
    Q_UNUSED(lead)
}

void ECGFilter_AC::privInit()
{
    if(xn1 != nullptr) {
        delete [] xn1;
        delete [] xn2;
        delete [] yn1;
        delete [] yn2;
    }
    xn1 = new int[AMP_IN_LEADS];
    xn2 = new int[AMP_IN_LEADS];
    yn1 = new float[AMP_IN_LEADS];
    yn2 = new float[AMP_IN_LEADS];
    memset(xn1, 0, sizeof(int)*AMP_IN_LEADS);
    memset(xn2, 0, sizeof(int)*AMP_IN_LEADS);
    memset(yn1, 0, sizeof(float)*AMP_IN_LEADS);
    memset(yn2, 0, sizeof(float)*AMP_IN_LEADS);

    switch (mFrequency) {
    case ACF_50:
        switch (mSamplingFrequency) {
        case 250:
            coeff_commonx = 0.9873701369842f;
            coeff_xn1 = 0.61803398874992f;
            coeff_yn1 = 0.6102283041329f;
            coeff_yn2 = 0.9747402739684f;
            break;
        case 500:
            coeff_commonx = 0.9936459339824f;
            coeff_xn1 = 1.61803398875024f;
            coeff_yn1 = 1.607752893967f;
            coeff_yn2 = 0.9872918679647f;
            break;
        default: // case 1000:
            coeff_commonx = 0.996812966709f;
            coeff_xn1 = 1.90211303259011f;
            coeff_yn1 = 1.896050935032f;
            coeff_yn2 = 0.993625933418f;
            break;
        }
        break;
    default:  // ACF_60:
        switch (mSamplingFrequency) {
        case 250:
            coeff_commonx = 0.9936459339824f;
            coeff_xn1 = 0.1255810390586374f;
            coeff_yn1 = 0.1247830888459f;
            coeff_yn2 = 0.9872918679647f;
            //filtersamplevalue = new FilterSampleValueDelegateF(FilterSampleValue_60_250);
            break;
        case 500:
            coeff_commonx = 0.996812966709f;
            coeff_xn1 = 1.457937254842372f;
            coeff_yn1 = 1.453290760275f;
            coeff_yn2 = 0.993625933418f;
            //filtersamplevalue = new FilterSampleValueDelegateF(FilterSampleValue_60_500);
            break;
        default: // case 1000:
            coeff_commonx = 0.996812966709f;
            coeff_xn1 = 1.859552971776429f;
            coeff_yn1 = 1.853626514549f;
            coeff_yn2 = 0.993625933418f;
            //filtersamplevalue = new FilterSampleValueDelegateF(FilterSampleValue_60_1000);
            break;
        }
        break;
    }
}

int32_t ECGFilter_AC::privFilter(int32_t sample, int lead)
{
    xn2[lead] = xn1[lead];
    xn1[lead] = sample;
    yn2[lead] = yn1[lead];
    yn1[lead] = coeff_commonx * (sample - coeff_xn1 * xn1[lead] + xn2[lead]) + coeff_yn1 * yn1[lead] - coeff_yn2 * yn2[lead];

    return (int32_t)yn1[lead];
}
#endif
