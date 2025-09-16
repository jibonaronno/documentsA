#ifndef CTSSIGNAL_CYC_H
#define CTSSIGNAL_CYC_H

#include "BaseSignal.h"
#include <QString>
#include <QStringList>

class CTSSignal_CYC : public BaseSignal
{
    Q_OBJECT
public:
#ifdef MEASUREMENTS_TESTER
    explicit CTSSignal_CYC(unsigned int index, QObject *parent = nullptr);
#else
    explicit CTSSignal_CYC(QString filename, QObject *parent = nullptr);
    static QStringList GetFileLists();
#endif
    SignalType_t  GetSignalType() {return CTS;}
    QString GetResults();

signals:

protected:
    void LoadFile();
#ifndef MEASUEMENTS_TESTER
    void LoadDataVector();
#endif
};

#endif // CTSSIGNAL_CYC_H
