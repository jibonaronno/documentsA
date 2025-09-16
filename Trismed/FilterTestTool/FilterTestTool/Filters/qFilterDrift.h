#ifndef QFILTERDRIFT_H
#define QFILTERDRIFT_H

#include "qAbstractFilter.h"
#include <QStringList>

class qFilterDrift : public qAbstractFilter
{
public:
    qFilterDrift();
    ~qFilterDrift();
    virtual void InitLead(int lead);
    void SetFrequency(TDriftFilters frequency);
    static QStringList getDriftFilters();
    virtual int GetFrequencyIndex() { return m_driftFreq; }

protected:
    virtual void privInit();
    virtual int32_t privFilter(int32_t sample, int lead);

private:
    TDriftFilters m_driftFreq;
    int m_bufferSize;

    int *xd[AMP_IN_LEADS];
    int nd[AMP_IN_LEADS];
    long int yd0[AMP_IN_LEADS];
    long int yd1[AMP_IN_LEADS];
};

#endif // QFILTERDRIFT_H
