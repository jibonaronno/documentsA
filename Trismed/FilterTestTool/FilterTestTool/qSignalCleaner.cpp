#include "qSignalCleaner.h"
#include <QDebug>

typedef enum  {
    L_RA=0x0100,
    L_LA=0x0200,
    L_LL=0x0080,
    L_C1=0x0400,
    L_C2=0x0800,
    L_C3=0x1000,
    L_C4=0x2000,
    L_C5=0x4000,
    L_C6=0x8000
} electrode_type;

qSignalCleaner::qSignalCleaner(QObject *parent) : QObject(parent)
{

}

QVector<int32_t> qSignalCleaner::CleanSignal(QVector<int32_t> &original, int lead, QVector<leadoffChange> &leadoffChanges)
{
    m_filterResetIndexes.clear();
    QVector<range_type> cleanRanges = GetCleanupRanges(leadoffChanges, lead);
    m_filterResetIndexes.append(0);
    foreach(range_type range, cleanRanges) {
        m_filterResetIndexes.append(range.start + (range.length==-1?original.count()-1:range.length));
    }
    qDebug() << "ResetIndexes:" << m_filterResetIndexes;

    int currentRageIndex = 0;
    range_type currentRange;
    if(cleanRanges.count()) {
        currentRange = cleanRanges.at(currentRageIndex);
        for(int i=0; i < original.count(); i++) {
            if(i >= currentRange.start) {
                if(i < currentRange.start+currentRange.length) {
                    original[i] = 0;
                } else {
                   currentRageIndex++;
                   if(currentRageIndex < cleanRanges.count())
                       currentRange = cleanRanges.at(currentRageIndex);
                   else
                       break;
                }
            }
        }
    }
    return original;
}

QVector<int> qSignalCleaner::GetFilterResetIndexes() const
{
    return m_filterResetIndexes;
}

QVector<range_type> qSignalCleaner::GetCleanupRanges(QVector<leadoffChange> &leadoffChanges, int lead)
{
    QVector<range_type> ranges;
    uint16_t electrodesToCheck = 0;
    switch(lead) {
    default:    // case 0:
        electrodesToCheck = L_RA + L_LA;
        break;
    case 1:
        electrodesToCheck = L_RA + L_LL;
        break;
    case 2:
        electrodesToCheck = L_RA + L_LA + L_LL + L_C1;
        break;
    case 3:
        electrodesToCheck = L_RA + L_LA + L_LL + L_C2;
        break;
    case 4:
        electrodesToCheck = L_RA + L_LA + L_LL + L_C3;
        break;
    case 5:
        electrodesToCheck = L_RA + L_LA + L_LL + L_C4;
        break;
    case 6:
        electrodesToCheck = L_RA + L_LA + L_LL + L_C5;
        break;
    case 7:
        electrodesToCheck = L_RA + L_LA + L_LL + L_C6;
        break;
    }
    leadoffChange prevStatus;
    prevStatus.extra = electrodesToCheck;
    int index=-1;
    int rangeEnd;
    int rangeStart = 0;
    foreach(leadoffChange currentStatus, leadoffChanges) {
        index++;
        if((currentStatus.extra & electrodesToCheck) != electrodesToCheck) { // electrode fault detected
            if((prevStatus.extra & electrodesToCheck) == electrodesToCheck) { // the electrode was OK before
                rangeStart = currentStatus.index;
                prevStatus = currentStatus;
                rangeEnd = -1;
            }
        } else { // The electrodes are ok
            if((prevStatus.extra & electrodesToCheck) != electrodesToCheck) { // the electrode was previously off
                    rangeEnd = 1250 +  currentStatus.index - rangeStart;
                qDebug() << "------" << rangeStart << " : " << rangeEnd;
                ranges << range_type(rangeStart, rangeEnd);
                rangeEnd = -1;
                prevStatus = currentStatus;
            }
        }
    }

    return ranges;
}
