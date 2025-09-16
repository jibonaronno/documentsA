#-------------------------------------------------
#
# Project created by QtCreator 2018-11-30T14:10:48
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FilterTestTool
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

#DEFINES += WITH_EMD

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    Filters/CardiOffice/ECGFilter_AC.cpp \
    Filters/CardiOffice/ECGFilter_MovingAverage.cpp \
    Filters/qAbstractFilter.cpp \
    Filters/qFilterAC60.cpp \
    Filters/qFilterMUS25.cpp \
    Filters/qFilterMUS35.cpp\
    Filters/qFilterAC50.cpp \
    Filters/qFilterLP100.cpp \
    Filters/qFilterLP150.cpp \
    Filters/qFilterLP75.cpp \
    Filters/qFilterDrift.cpp \
    Filters/qFilterIIR_HP005.cpp \
    Filters/qFilterIIR_HP01.cpp \
    Filters/qFilterIIR_HP015.cpp \
    Filters/qFilterIIR_HP02.cpp \
    Filters/qFilterIIR_HP025.cpp \
    Filters/qFilterIIR_HP032.cpp \
    Filters/qFilterIIR_HP05.cpp \
    Filters/qFilterIIR_HP067.cpp \
    Filters/qFilterIIR_AC60.cpp \
    Filters/qFilterIIR_AC50.cpp \
    qFilterTestBench.cpp \
    Widgets/qFrequencyChart.cpp \
    Widgets/qSignalChart.cpp \
    Widgets/Callout.cpp \
    Widgets/qFrequencyView.cpp \
    qSignalCleaner.cpp \
    qImpulseSignal.cpp \
    qPulsesignal.cpp \
    qSineGen.cpp \
    qSpikeGen.cpp \
    qStepSignal.cpp \
    qAdsToFile.cpp \
    qCardipiaECG_RT_File.cpp \
    qECG_RAW_File.cpp \
    SignalFormats/BaseSignal.cpp \
    SignalFormats/CTSSignal_CYC.cpp

HEADERS += \
    MainWindow.h \
    Filters/CardiOffice/ECGFilter_AC.h \
    Filters/CardiOffice/ECGFilter_MovingAverage.h \
    Filters/qAbstractFilter.h \
    Filters/qFilterAC60.h \
    Filters/qFilterMUS25.h \
    Filters/qFilterMUS35.h \
    Filters/qFilterAC50.h \
    Filters/qFilterLP100.h \
    Filters/qFilterLP150.h \
    Filters/qFilterLP75.h \
    Filters/qFilterDrift.h \
    Filters/qFilterIIR_HP005.h \
    Filters/qFilterIIR_HP01.h \
    Filters/qFilterIIR_HP015.h \
    Filters/qFilterIIR_HP02.h \
    Filters/qFilterIIR_HP025.h \
    Filters/qFilterIIR_HP032.h \
    Filters/qFilterIIR_HP05.h \
    Filters/qFilterIIR_HP067.h \
    Filters/qFilterIIR_AC60.h \
    Filters/qFilterIIR_AC50.h \
    qFilterTestBench.h \
    Widgets/qFrequencyChart.h \
    Widgets/qSignalChart.h \
    Widgets/Callout.h \
    Widgets/qFrequencyView.h \
    qImpulseSignal.h \
    qPulsesignal.h \
    qSineGen.h \
    qSignalCleaner.h \
    qSpikeGen.h \
    qStepSignal.h \
    qAdsToFile.h \
    qCardipiaECG_RT_File.h \
    qECG_RAW_File.h \
    SignalFormats/BaseSignal.h \
    SignalFormats/CTSSignal_CYC.h

FORMS += \
        MainWindow.ui

contains(DEFINES, "WITH_EMD") {
SOURCES +=  EMDDialog.cpp \
            EMD/cubic.cpp \
            EMD/emd.cpp

HEADERS +=  EMDDialog.h \
            EMD/cubic.h \
            EMD/emd.h

FORMS += \
        EMDDialog.ui
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
