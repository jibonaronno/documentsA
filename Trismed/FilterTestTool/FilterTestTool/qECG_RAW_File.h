#ifndef QECG_RAW_FILE_H
#define QECG_RAW_FILE_H

#include <QObject>
#include <QVector>

class qECG_RAW_File : public QObject
{
    Q_OBJECT
public:
    explicit qECG_RAW_File(QObject *parent = nullptr);
    void Load(QString filename);
    QVector<int32_t> GetChannel(int lead);

private:
    QVector< QVector<int32_t> > m_leads;
    int32_t m_channelCount;
};

#endif // QECG_RAW_FILE_H
