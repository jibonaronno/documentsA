#ifndef ECGFILTER_AC_H
#define ECGFILTER_AC_H

#include "..\qAbstractFilter.h"

#define CARDIOFFICE_NEW_AC
//#define CARDIOFFICE_NEW_FIR_AC

class ECGFilter_AC : public qAbstractFilter
{
public:
    ECGFilter_AC(TACFilters frequency = ACF_60, int samplingFrequency = 500);
    void SetAcFilterType(TACFilters frequency);
    ~ECGFilter_AC();
    virtual void InitLead(int lead);
    virtual int GetFrequencyIndex() { return mFrequency; }

protected:
    virtual void privInit();
    virtual int32_t privFilter(int32_t sample, int lead);

    TACFilters mFrequency;
    int mSamplingFrequency;

private:
#ifdef CARDIOFFICE_NEW_AC
#ifdef CARDIOFFICE_NEW_FIR_AC
    double* x[AMP_IN_LEADS]; //input samples
    const double *FIRCoef;
#else
    float* y[AMP_IN_LEADS]; //output samples
    float* x[AMP_IN_LEADS]; //input samples

    const double *ACoef;
    const double *BCoef;

#endif /* CARDIOFFICE_NEW_FIR_AC */
#else
    int* xn1;
    int* xn2;
    float* yn1;
    float* yn2;
    float coeff_commonx;
    float coeff_xn1;
    float coeff_yn1;
    float coeff_yn2;
#endif
};

#endif // ECGFILTER_AC_H
