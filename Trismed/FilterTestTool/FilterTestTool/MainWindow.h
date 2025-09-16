#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollBar>
#include <QtCharts/QChartView>
#include <QHBoxLayout>
#include "Widgets/qFrequencyChart.h"
#include "Widgets/qFrequencyView.h"
#include "Widgets/qSignalChart.h"
#include "Filters/qFilterAC50.h"
#include "Filters/qFilterAC60.h"
#include "Filters/qFilterMUS35.h"
#include "Filters/qFilterMUS25.h"
#include "Filters/qFilterLP75.h"
#include "Filters/qFilterLP100.h"
#include "Filters/qFilterLP150.h"
#include "Filters/qFilterDrift.h"
#include "Filters/qFilterIIR_HP005.h"
#include "Filters/qFilterIIR_HP01.h"
#include "Filters/qFilterIIR_HP015.h"
#include "Filters/qFilterIIR_HP02.h"
#include "Filters/qFilterIIR_HP025.h"
#include "Filters/qFilterIIR_HP032.h"
#include "Filters/qFilterIIR_HP05.h"
#include "Filters/qFilterIIR_HP067.h"
#include "Filters/qFilterIIR_AC60.h"
#include "Filters/qFilterIIR_AC50.h"
#include "Filters/CardiOffice/ECGFilter_AC.h"
#include "Filters/CardiOffice/ECGFilter_MovingAverage.h"
#include "qFilterTestBench.h"
#ifdef WITH_EMD
#include "EMDDialog.h"
#endif

#define RAW_FILE 1
#define RT_FILE 2
#define ECG_FILE 3
#define CTS_FILE 4
#define FILE_TYPE   (CTS_FILE)

#if FILE_TYPE == CTS_FILE
#include "SignalFormats/CTSSignal_CYC.h"
#elif FILE_TYPE == ECG_FILE
#warning TODO:
#elif FILE_TYPE == RT_FILE
#include "qCardipiaECG_RT_File.h"
#include "qAdsToFile.h"
#elif FILE_TYPE == RAW_FILE
#include "qECG_RAW_File.h"
#else
#error Invalid FILE_TYPE definition!!!
#endif

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_process_clicked();
    void on_scrollValueChanged(int value);
    void on_YSpamChanged(int value);

private:
    Ui::MainWindow *ui;
    ECGFilter_AC cardiOffice_AC50;
    ECGFilter_AC cardiOffice_AC60;
    ECGFilter_MovingAverage lpMovingAvg;
    qFilterAC50 ac50;
    qFilterAC60 ac60;
    qFilterAC60 ac60_2;
    qFilterAC60 ac50_1, ac50_2;
    qFilterMUS35 mus35;
    qFilterMUS25 mus25;
    qFilterLP75 lp75;
    qFilterLP100 lp100;
    qFilterLP150 lp150;
    qFilterDrift drift;
    qFilterIIR_HP005 driftIIR005;
    qFilterIIR_HP01 driftIIR01;
    qFilterIIR_HP015 driftIIR015;
    qFilterIIR_HP02 driftIIR02;
    qFilterIIR_HP025 driftIIR025;
    qFilterIIR_HP032 driftIIR032;
    qFilterIIR_HP05 driftIIR05;
    qFilterIIR_HP067 driftIIR067;
    qFilterIIR_AC60 acIIR60;
    qFilterIIR_AC50 acIIR50;
    qFilterTestBench filterbench;
    QChartView *chartView;
    QChartView *chartViewPhase;
    QChartView *chartViewSignal;
    qFrequencyChart *chart;
    qFrequencyView *freqView;
    qSignalChart *chartSignal;
    QScrollBar *scrollBar_Signal;
    QScrollBar *scrollBar_YSpam;
    QHBoxLayout *bottomHLayout;
    int prevValue;
#if FILE_TYPE == CTS_FILE
    CTSSignal_CYC *ctsFile;
#elif FILE_TYPE == RAW_FILE
    qECG_RAW_File rawFile;
#elif FILE_TYPE == RT_FILE
    qCardipiaECG_RT_File rtFile;
    qAdsToFile adsFile;
#endif
    QList<qAbstractFilter*> filtersList;
    QString FiltersString;

    void setEnableControls(bool enable);
    void updateFilterList();

#ifdef WITH_EMD
    EMDDialog *emdDialog;
#endif

private slots:
    void on_ProcessDone();
    void on_pushButton_UpdateGraph_clicked();
    void on_pushButton_default_clicked();
    void on_pushButton_defaultHP_clicked();
    void on_pushButton_LoadAndFilter_clicked();
};

#endif // MAINWINDOW_H
