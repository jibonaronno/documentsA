#ifndef QABSTRACTFILTER_H
#define QABSTRACTFILTER_H

#include <stdint.h>
#include <QVector>
#include <list>
#ifdef CARDIPIA
#include "devices/qampdevice.h"
#include "TECGUtils.h"
#else
#define AMP_IN_LEADS 1
#endif

using namespace std;

//#define FORCE_DELAY_0

#ifndef TECGUTILS_H
enum TDriftFilters {DRF_005 = 0, DRF_05, DRF_01, DRF_02, DRF_015, DRF_025, DRF_032, DRF_067, DRF_QUANTITY};
enum TLPFFilters {LPF_200 = 0, LPF_150, LPF_100, LPF_75, LPF_QUANTITY};
enum TMusFilters {MUS_OFF = 0, MUS_25, MUS_35, MUS_40, MUS_45,  MUS_QUANTITY};
enum TACFilters {ACF_OFF = 0, ACF_50, ACF_60, ACF_QUANTITY};
#endif

struct SampleFilter; /* used for filters designed with: http://t-filter.engineerjs.com/ */

class qAbstractFilter
{
public:
    qAbstractFilter(double filterDelay);
    virtual ~qAbstractFilter();
    void Init();
    virtual void InitLead(int lead) = 0;
    int32_t Filter(int32_t sample);
    QVector<int32_t> Filter(const QVector<int32_t>& inSignal);
    QVector<int32_t> Filter(const QVector<int32_t>& inSignal, int startIndex, int endIndex);
#ifdef CARDIPIA
    virtual void Filter(ampsample *sample);
#endif
    double GetDelay();
    virtual int GetFrequencyIndex() = 0;

protected:
    QVector<int32_t> output;
    double m_filterDelay;

    virtual void privInit() = 0;
    virtual int32_t privFilter(int32_t sample, int lead) = 0;

#ifdef CARDIPIA
    void initDelay();
private:
    virtual void delayExtraData(ampsample &sample);
    list<unsigned short> listExtra;
#endif
};

#endif // QABSTRACTFILTER_H
