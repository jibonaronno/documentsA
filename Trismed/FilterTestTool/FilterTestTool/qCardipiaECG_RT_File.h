#ifndef QCARDIPIAECG_RT_FILE_H
#define QCARDIPIAECG_RT_FILE_H

#include <QObject>
#include <QVector>
#include <QList>
#include <QFile>
#include <QDebug>
#include "qSignalCleaner.h"

#ifdef CARDIPIA
#include "services/ampservice.h"
#else
#pragma pack (push, 2)
struct ampsample {
    int leads[12];                            /**< Leads sample values */
    unsigned short extra;                     /**< Additional information (leadoff and pacemaker) */
};
#pragma pack(pop)
#endif

QDebug operator<< (QDebug d, const leadoffChange &loff);

class qCardipiaECG_RT_File : public QObject
{
    Q_OBJECT
public:
    explicit qCardipiaECG_RT_File(QObject *parent = 0);
    void Save(QString fileName = "");
    bool Load(QString fileName);
    void AddSample(ampsample sample);
    QVector<int32_t> GetLead(int lead);
    leadoffChange GetNextElectrodeChangeIndex(int currentIndex);
    double GetResolution();
    int SamplesCount();

private:

    double m_resolution;
    QList<ampsample> samples;
};

#endif // QCARDIPIAECG_RT_FILE_H
