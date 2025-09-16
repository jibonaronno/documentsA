#ifndef ECGFILTER_MOVINGAVERAGE_H
#define ECGFILTER_MOVINGAVERAGE_H

#include "..\qAbstractFilter.h"

class ECGFilter_MovingAverage : public qAbstractFilter
{
public:
    enum MovingAverageFilterCut { LowPass, HighPass, BandPass };

    ECGFilter_MovingAverage(MovingAverageFilterCut filterCutType = LowPass, int samplingFrequency = 500);
    ~ECGFilter_MovingAverage();
    virtual void InitLead(int lead);
    virtual int GetFrequencyIndex(); //TODO: check this later

protected:
    virtual void privInit();
    virtual int32_t privFilter(int32_t sample, int lead);

private:
    MovingAverageFilterCut FilterCut;
    int mSamplingFrequency;

    void SetBuffersSize(ushort k, ushort l);
    void SetBuffersSize(int samplingrate);

    short k;
    short l;
    int kk;
    int ll;
    uint FilteredSamples;

    long** bvaL;
    long** bspL;
    long* spL;
    long* stL;

    long** bvaH;
    long** bspH;
    long* spH;
    long* stH;
    void FreeUpMemory();
};

#endif // ECGFILTER_MOVINGAVERAGE_H
