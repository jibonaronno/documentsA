#ifndef QADSTOFILE_H
#define QADSTOFILE_H
#include <QObject>
#include "queues/fastqueue.h"
#include "qAcq_Ads1298.h"
#include "qSignalCleaner.h"

class qAdsToFile : public QObject
{
    Q_OBJECT

public:
    qAdsToFile(QObject* parent = nullptr);
    ~qAdsToFile();
    FastQueue<Raw_Tx_t> * getQueue() { return samplesQueue; }

    bool Load(QString fileName);
    QVector<int32_t> GetLead(int lead);
    double GetResolution();
    int SamplesCount();
    leadoffChange GetNextElectrodeChangeIndex(int currentIndex);

private:
    FastQueue<Raw_Tx_t> *samplesQueue;
    QFile *m_file;
    double m_resolution;
    int64_t m_numSamples;

    QList<Raw_Tx_t> samples;

private slots:
    void onNewSamples();
};

#endif // QADSTOFILE_H
