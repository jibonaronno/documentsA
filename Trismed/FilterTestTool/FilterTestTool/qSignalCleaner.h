#ifndef QSIGNALCLEANER_H
#define QSIGNALCLEANER_H

#include <QObject>
#include <QVector>

struct leadoffChange {
    int index;
    uint16_t extra;
};

struct range_type {
    range_type() { start = 0; length = 0; }
    range_type(int _start, int _length) { start = _start; length = _length; }
    int start;
    int length;
};

class qSignalCleaner : public QObject
{
    Q_OBJECT
public:
    explicit qSignalCleaner(QObject *parent = nullptr);
    QVector<int32_t> CleanSignal(QVector<int32_t> &original, int lead, QVector<leadoffChange>& leadoffChanges);
    QVector<int> GetFilterResetIndexes() const;

private:
    QVector<int> m_filterResetIndexes;
    QVector<range_type> GetCleanupRanges(QVector<leadoffChange>& leadoffChanges, int lead);
};

#endif // QSIGNALCLEANER_H
