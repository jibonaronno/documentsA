#include "ECGFilter_MovingAverage.h"

static const ushort BUFFSIZE_LOWPASS_250 = 3;
static const ushort BUFFSIZE_LOWPASS_500 = 4;
static const ushort BUFFSIZE_LOWPASS_1000 = 8;
static const ushort BUFFSIZE_HIGHPASS_250 = 200;
static const ushort BUFFSIZE_HIGHPASS_500 = 410;
static const ushort BUFFSIZE_HIGHPASS_1000 = 820;

ECGFilter_MovingAverage::ECGFilter_MovingAverage(MovingAverageFilterCut filterCutType, int samplingFrequency) : qAbstractFilter(0)
{
    FilterCut = filterCutType;
    mSamplingFrequency = samplingFrequency;

    k = 0;
    l = 0;
    kk = 0;
    ll = 0;

    bvaL = nullptr;
    bspL = nullptr;
    spL = nullptr;
    stL = nullptr;

    bvaH = nullptr;
    bspH = nullptr;
    spH = nullptr;
    stH = nullptr;
    m_filterDelay = l+k;
}

void ECGFilter_MovingAverage::FreeUpMemory()
{
    if(FilterCut == BandPass || FilterCut == LowPass) {
        for(int i=0; i<AMP_IN_LEADS; i++) {
            if(bvaL) {
                delete [] bvaL[i];
            }
            if(bspL) {
                delete [] bspL[i];
            }
        }
        delete [] bvaL;
        delete [] bspL;
        delete [] spL;
        delete [] stL;
    }

    if(FilterCut == BandPass || FilterCut == HighPass) {
        for(int i=0; i<AMP_IN_LEADS; i++) {
            delete [] bvaH[i];
            delete [] bspH[i];
        }
        delete [] bvaH;
        delete [] bspH;
        delete [] spH;
        delete [] stH;
    }

    bvaL = nullptr;
    bspL = nullptr;
    spL = nullptr;
    stL = nullptr;

    bvaH = nullptr;
    bspH = nullptr;
    spH = nullptr;
    stH = nullptr;
}

ECGFilter_MovingAverage::~ECGFilter_MovingAverage()
{
    FreeUpMemory();
}

void ECGFilter_MovingAverage::SetBuffersSize(ushort k, ushort l)
{
    if ((FilterCut == BandPass) || (FilterCut == LowPass)) { // low pass filter
        this->k = k;
        this->kk = (uint)(k * k);
    } else {
        this->k = 0;
        this->kk = 0;
    }

    if ((FilterCut == BandPass) || (FilterCut == HighPass)) { // high pass filter
        this->l = l;
        this->ll = (uint)(l * l);
    } else {
        this->l = 0;
        this->ll = 0;
    }

    m_filterDelay = this->l + this->k;
}

void ECGFilter_MovingAverage::SetBuffersSize(int samplingrate)
{
    switch (samplingrate)
    {
        case 250:
            SetBuffersSize(BUFFSIZE_LOWPASS_250, BUFFSIZE_HIGHPASS_250);
            break;
        case 1000:
            SetBuffersSize(BUFFSIZE_LOWPASS_1000, BUFFSIZE_HIGHPASS_1000);
            break;
        default: // case 500:
            SetBuffersSize(BUFFSIZE_LOWPASS_500, BUFFSIZE_HIGHPASS_500);
            break;
    }
}

void ECGFilter_MovingAverage::InitLead(int lead)
{
    if(FilterCut == BandPass || FilterCut == LowPass) {
        spL[lead] = 0;
        stL[lead] = 0;
        for(int i=0; i<k; i++) {
            bvaL[lead][i] = 0;
            bspL[lead][i] = 0;
        }
    }

    if(FilterCut == BandPass || FilterCut == HighPass) {
        spH[lead] = 0;
        stH[lead] = 0;
        for(int i=0; i<l; i++) {
            bvaH[lead][i] = 0;
            bspH[lead][i] = 0;
        }
    }
}

int ECGFilter_MovingAverage::GetFrequencyIndex() { return 0; }

void ECGFilter_MovingAverage::privInit()
{
    FilteredSamples = 0;
    if(bvaL != nullptr || bvaH != nullptr ) {
        FreeUpMemory();
    }

    SetBuffersSize(mSamplingFrequency);
    if(FilterCut == BandPass || FilterCut == LowPass) {
        bvaL = new long*[AMP_IN_LEADS];
        bspL = new long*[AMP_IN_LEADS];
        spL = new long[AMP_IN_LEADS];
        stL = new long[AMP_IN_LEADS];
        for(int i=0; i<AMP_IN_LEADS; i++) {
            bvaL[i] = new long[k];
            bspL[i] = new long[k];
            spL[i] = 0;
            stL[i] = 0;
        }
    }

    if(FilterCut == BandPass || FilterCut == HighPass) {
        bvaH = new long*[AMP_IN_LEADS];
        bspH = new long*[AMP_IN_LEADS];
        spH = new long[AMP_IN_LEADS];
        stH = new long[AMP_IN_LEADS];
        for(int i=0; i<AMP_IN_LEADS; i++) {
            bvaH[i] = new long[l];
            bspH[i] = new long[l];
            spH [i] = 0;
            stH [i] = 0;
        }
    }

    for(int i=0; i<AMP_IN_LEADS; i++) {
        InitLead(i);
    }
}

int32_t ECGFilter_MovingAverage::privFilter(int32_t sample, int lead)
{
    long result = sample;

    if ((FilterCut == BandPass) || (FilterCut == LowPass)) // low pass filter
    {
        int pbL = FilteredSamples % k;
        spL[lead] = spL[lead] + result - bvaL[lead][pbL];
        stL[lead] = stL[lead] + spL[lead] - bspL[lead][pbL];
        bvaL[lead][pbL] = result;
        bspL[lead][pbL] = spL[lead];
        result = stL[lead] / kk;
    }

    if ((FilterCut == BandPass) || (FilterCut == HighPass)) // high pass filter
    {
        int pbH = FilteredSamples % l;
        spH[lead] = spH[lead] + result - bvaH[lead][pbH];
        stH[lead] = stH[lead] + spH[lead] - bspH[lead][pbH];
        long partialresult = bvaH[lead][pbH];
        bvaH[lead][pbH] = result;
        bspH[lead][pbH] = spH[lead];
        result = partialresult - stH[lead] / ll;
    }

    if(lead == AMP_IN_LEADS-1) {
        FilteredSamples++;
    }

    return result;
}
