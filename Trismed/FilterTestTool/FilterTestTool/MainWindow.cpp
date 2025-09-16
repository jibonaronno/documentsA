#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QValueAxis>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
#include <QDoubleValidator>
#include <QMessageBox>
#include "qSignalCleaner.h"

#define USE_Q_FREQUENCY_VIEW
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_minFreq->setValidator(new QDoubleValidator(this));
    ui->lineEdit_maxFreq->setValidator(new QDoubleValidator(this));
    ui->lineEdit_stepFreq->setValidator(new QDoubleValidator(this));
    ui->lineEdit_ampliture->setValidator(new QDoubleValidator(this));
    ui->lineEdit_duration->setValidator(new QDoubleValidator(this));
    ui->lineEdit_SamplingFreq->setValidator(new QIntValidator(this));
    ui->lineEdit_FreqToShow->setValidator(new QDoubleValidator(this));
    ui->lineEdit_SamplesPerScreen->setValidator(new QIntValidator(this));

    ui->comboBox_driftFreq->addItems(qFilterDrift::getDriftFilters());
    connect(&filterbench, SIGNAL(sProgress(int)), ui->progressBar, SLOT(setValue(int)));

#ifdef USE_Q_FREQUENCY_VIEW
    freqView = new qFrequencyView(this);
    freqView->setRenderHint(QPainter::Antialiasing);
    ui->FrameLayout->addWidget(freqView);
#else
    chart = new qFrequencyChart();
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->FrameLayout->addWidget(chartView);
#endif

    chartSignal = nullptr;
    chartViewSignal = nullptr;
    chartViewPhase = nullptr;

    bottomHLayout = new QHBoxLayout();
    ui->FrameLayout->addLayout(bottomHLayout);

    scrollBar_YSpam = new QScrollBar(this);
    scrollBar_YSpam->setVisible(false);
    scrollBar_YSpam->setOrientation(Qt::Vertical);
    bottomHLayout->addWidget(scrollBar_YSpam);
    connect(scrollBar_YSpam, SIGNAL(valueChanged(int)), this, SLOT(on_YSpamChanged(int)));

    chartSignal = new qSignalChart();
    chartViewSignal = new QChartView(chartSignal);
    chartViewSignal->setRenderHint(QPainter::Antialiasing);
    bottomHLayout->addWidget(chartViewSignal);

    scrollBar_Signal = new QScrollBar(this);
    scrollBar_Signal->setVisible(false);
    scrollBar_Signal->setOrientation(Qt::Horizontal);
    prevValue = 0;
    scrollBar_Signal->setValue(0);
    ui->FrameLayout->addWidget(scrollBar_Signal);
    connect(scrollBar_Signal, SIGNAL(valueChanged(int)), this, SLOT(on_scrollValueChanged(int)));

    on_pushButton_default_clicked();
#if FILE_TYPE == CTS_FILE
    ctsFile = nullptr;
    QStringList fileList = CTSSignal_CYC::GetFileLists();
#else
    QDir searchFolder(QCoreApplication::applicationDirPath());
    searchFolder.setNameFilters(QStringList() << "*.ecgrt" << "*.AdsRaw");
    QStringList fileList = searchFolder.entryList(QDir::NoFilter, QDir::NoSort);
#endif
    ui->comboBox_SignalFiles->addItems(fileList);
#ifdef WITH_EMD
    emdDialog = nullptr;
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_process_clicked()
{
    updateFilterList();
    filterbench.SetFiltersList(filtersList);
    double startFreq = ui->lineEdit_minFreq->text().toDouble();
    double endFreq = ui->lineEdit_maxFreq->text().toDouble();
    double stepFreq = ui->lineEdit_stepFreq->text().toDouble();
    filterbench.SetSignalProperties(ui->lineEdit_ampliture->text().toDouble(),
                                    ui->lineEdit_duration->text().toInt(),
                                    ui->lineEdit_SamplingFreq->text().toInt());
    filterbench.SetFrequencySweep(startFreq,
                                  endFreq,
                                  stepFreq);
    filterbench.SetFixFilterDelay(ui->checkBox_FixFiltersDelay->isChecked());

    double outputSignalFreq = ui->lineEdit_FreqToShow->text().toDouble();

    filterbench.SetupOutputParameters(outputSignalFreq, ui->lineEdit_duration->text().toInt());

    QFutureWatcher<void> *processFutureWatcher = new QFutureWatcher<void>();
    connect(processFutureWatcher, SIGNAL(finished()), this, SLOT(on_ProcessDone()));
    processFutureWatcher->setFuture(QtConcurrent::run(&filterbench, &qFilterTestBench::Process));
    setEnableControls(false);
}

void MainWindow::on_scrollValueChanged(int value)
{
    chartSignal->scroll(value-prevValue, 0);
    prevValue = value;
}

void MainWindow::on_YSpamChanged(int value)
{
    chartSignal->setYSpam(value/1000.0);
}

void MainWindow::setEnableControls(bool enable)
{
    ui->groupBox_Signal->setEnabled(enable);
    ui->groupBox_ACSweep->setEnabled(enable);
    ui->groupBox_Filter->setEnabled(enable);
    ui->groupBox_TimeDelay->setEnabled(enable);
    ui->groupBox->setEnabled(enable);
    ui->groupBox_SignalChart->setEnabled(enable);
}

void MainWindow::updateFilterList()
{
    FiltersString.clear();
    filtersList.clear();
    if(ui->checkBox_MUS35->isChecked()) {
        filtersList.append(&mus35);
        FiltersString += "MUS35Hz ";
    }
    if(ui->checkBox_MUS25->isChecked()) {
        filtersList.append(&mus25);
        FiltersString += "MUS25Hz ";
    }
    if(ui->checkBox_LP75->isChecked()) {
        filtersList.append(&lp75);
        FiltersString += "75Hz ";
    }
    if(ui->checkBox_LP100->isChecked()) {
        filtersList.append(&lp100);
        FiltersString += "100Hz ";
    }
    if(ui->checkBox_LP150->isChecked()) {
        filtersList.append(&lp150);
        FiltersString += "150Hz ";
    }
    if(ui->groupBox_Drift->isChecked()) {
        drift.SetFrequency(static_cast<TDriftFilters>(ui->comboBox_driftFreq->currentIndex()));
        FiltersString += ui->comboBox_driftFreq->currentText() + " ";
        filtersList.append(&drift);
    }
    if(ui->checkBox_IIR_HP005->isChecked()) {
        filtersList.append(&driftIIR005);
        FiltersString += "0.05Hz ";
    }
    if(ui->checkBox_IIR_HP01->isChecked()) {
        filtersList.append(&driftIIR01);
        FiltersString += "0.1Hz ";
    }
    if(ui->checkBox_IIR_HP015->isChecked()) {
        filtersList.append(&driftIIR015);
        FiltersString += "0.15Hz ";
    }
    if(ui->checkBox_IIR_HP02->isChecked()) {
        filtersList.append(&driftIIR02);
        FiltersString += "0.2Hz ";
    }
    if(ui->checkBox_IIR_HP025->isChecked()) {
        filtersList.append(&driftIIR025);
        FiltersString += "0.25Hz ";
    }
    if(ui->checkBox_IIR_HP032->isChecked()) {
        filtersList.append(&driftIIR032);
        FiltersString += "0.32Hz ";
    }
    if(ui->checkBox_IIR_HP067->isChecked()) {
        filtersList.append(&driftIIR067);
        FiltersString += "0.67Hz ";
    }
    if(ui->checkBox_IIR_HP05->isChecked()) {
        filtersList.append(&driftIIR05);
        FiltersString += "0.5Hz ";
    }
    if(ui->checkBox_IIR_AC60->isChecked()) {
        filtersList.append(&acIIR60);
        FiltersString += "60Hz ";
    }
    if(ui->checkBox_IIR_AC50->isChecked()) {
        filtersList.append(&acIIR50);
        FiltersString += "50Hz ";
    }
    if(ui->checkBox_AC60->isChecked()) {
        filtersList.append(&ac60);
        FiltersString += "60Hz ";
        //filtersList.append(&ac60_2);
    }
    if(ui->checkBox_AC50->isChecked()) {
//        filtersList.append(&ac50_1);
//        filtersList.append(&ac50_2);
        filtersList.append(&ac50);
        FiltersString += "50Hz ";
    }
    if(ui->checkBox_CoAC60->isChecked()) {
        cardiOffice_AC60.SetAcFilterType(ACF_60);
        filtersList.append(&cardiOffice_AC60);
        FiltersString += "60Hz ";
    }
    if(ui->checkBox_CoAC50->isChecked()) {
        cardiOffice_AC50.SetAcFilterType(ACF_50);
        filtersList.append(&cardiOffice_AC50);
        FiltersString += "50Hz ";
    }
    if(ui->checkBox_CoLP->isChecked()) {
        filtersList.append(&lpMovingAvg);
        FiltersString += "LP ";
    }
}

void MainWindow::on_ProcessDone()
{
    delete QObject::sender();
    QVector<QPointF> result = filterbench.GetResult();
    scrollBar_Signal->setValue(0);
    prevValue = 0;
#ifdef USE_Q_FREQUENCY_VIEW
    freqView->SetMaxMinAmplitud_dB(
                ui->lineEdit_MaxAmpdB->text().toInt(),
                ui->lineEdit_MinAmpdB->text().toInt());
    freqView->SetDataPoints(result, ui->lineEdit_minFreq->text().toDouble(), ui->lineEdit_maxFreq->text().toDouble());
#else
    chart->SetDataPoints(result, ui->lineEdit_minFreq->text().toDouble(), ui->lineEdit_maxFreq->text().toDouble());
#endif

    if(ui->radioButton_SineWave->isChecked()) {
    chartSignal->SetDataPoints(filterbench.GetOriginalSignal(), filterbench.GetFilteredSignal());
    scrollBar_Signal->setMaximum(
                static_cast<int>(
                    (filterbench.GetOriginalSignal().count()/100.0)*
                    (chartSignal->rect().width()-(chartSignal->margins().left()+chartSignal->margins().right())))
                );
    chartSignal->SetTotalDelay(filterbench.GetTotalFilterDelay(),
                               1000 * filterbench.GetTotalFilterDelay() / ui->lineEdit_SamplingFreq->text().toInt());
    } else if(ui->radioButton_StepResponse->isChecked()) {
        chartSignal->SetDataPoints(filterbench.GetStepSignal(), filterbench.GetFilteredStepSignal());
        scrollBar_Signal->setMaximum(
                    static_cast<int>(
                        (filterbench.GetStepSignal().count()/100.0)*
                        (chartSignal->rect().width()-(chartSignal->margins().left()+chartSignal->margins().right())))
                    );
        chartSignal->SetTotalDelay(filterbench.GetTotalFilterDelay(),
                                   1000 * filterbench.GetTotalFilterDelay() / ui->lineEdit_SamplingFreq->text().toInt());
    } else {
        chartSignal->SetDataPoints(filterbench.GetImpulseSignal(), filterbench.GetFilteredImpulseSignal());
        scrollBar_Signal->setMaximum(
                    static_cast<int>(
                        (filterbench.GetImpulseSignal().count()/100.0)*
                        (chartSignal->rect().width()-(chartSignal->margins().left()+chartSignal->margins().right())))
                    );
        chartSignal->SetTotalDelay(filterbench.GetTotalFilterDelay(),
                                   1000 * filterbench.GetTotalFilterDelay() / ui->lineEdit_SamplingFreq->text().toInt());
    }
    scrollBar_Signal->setValue(0);
    scrollBar_Signal->setVisible(true);
    setEnableControls(true);
    on_pushButton_UpdateGraph_clicked();
}

void MainWindow::on_pushButton_UpdateGraph_clicked()
{
    chartSignal->setSamplesPerScreen(ui->lineEdit_SamplesPerScreen->text().toInt());
    double pixPerScreen = chartSignal->rect().width()-(chartSignal->margins().left()+chartSignal->margins().right());
    double samplesPerScreen = ui->lineEdit_SamplesPerScreen->text().toInt();
    int max;
    if(ui->radioButton_SineWave->isChecked()) {
        max = static_cast<int>(((filterbench.GetOriginalSignal().count()/samplesPerScreen))*pixPerScreen);
    } else if(ui->radioButton_StepResponse->isChecked()) {
        max = static_cast<int>(((filterbench.GetStepSignal().count()/samplesPerScreen))*pixPerScreen);
    } else {
        max = static_cast<int>(((filterbench.GetImpulseSignal().count()/samplesPerScreen))*pixPerScreen);
    }
    scrollBar_Signal->setMaximum(max);
    chartSignal->scroll(0, 0);
    prevValue = 0;
    scrollBar_Signal->setValue(0);
}

void MainWindow::on_pushButton_default_clicked()
{
    ui->lineEdit_minFreq->setText(QString::number(0.1));
    ui->lineEdit_maxFreq->setText(QString::number(80));
    ui->lineEdit_stepFreq->setText(QString::number(0.2));
    ui->lineEdit_duration->setText(QString::number(30));
}

void MainWindow::on_pushButton_defaultHP_clicked()
{
    ui->lineEdit_minFreq->setText(QString::number(0.01));
    ui->lineEdit_maxFreq->setText(QString::number(1));
    ui->lineEdit_stepFreq->setText(QString::number(0.01));
    ui->lineEdit_duration->setText(QString::number(120));
}

void MainWindow::on_pushButton_LoadAndFilter_clicked()
{
    scrollBar_Signal->setValue(0);
    prevValue = 0;
    updateFilterList();
    filterbench.SetFixFilterDelay(ui->checkBox_FixFiltersDelay->isChecked());
    filterbench.SetFiltersList(filtersList);
#if FILE_TYPE == CTS_FILE
    delete ctsFile;
    ctsFile = new CTSSignal_CYC(ui->comboBox_SignalFiles->currentText());
    filterbench.FilterSignal(ctsFile);
    filterbench.SetResolution(ctsFile->resolution);
    QString title = QString("%1 Filters: %2")
            .arg(ui->comboBox_SignalFiles->currentText().split('.').at(1), FiltersString);
    chartSignal->setPlotTitle(title);

#ifdef WITH_EMD
    if(emdDialog != nullptr) {
        emdDialog->close();
        delete emdDialog;
    }
    emdDialog = new EMDDialog(this);
    emdDialog->setEcgSignal(ctsFile->GetChannel(0));
    emdDialog->show();
#endif
#elif FILE_TYPE == RT_FILE
    QVector<int32_t> orgSignal;
    qSignalCleaner cleaner;
    QString fileName = QCoreApplication::applicationDirPath() + "\\" + ui->comboBox_SignalFiles->currentText();
    if(ui->comboBox_SignalFiles->currentText().contains(".AdsRaw")) {
        if(!adsFile.Load(fileName))
            return;
        orgSignal = adsFile.GetLead(ui->comboBox_Lead->currentIndex());
        filterbench.SetResolution(adsFile.GetResolution());
        QVector<leadoffChange> electrodeChanges;
        if(ui->checkBox_signalCleanup->isChecked()) {
            leadoffChange currentChange;
            currentChange.index = -1;
            do {
                currentChange = adsFile.GetNextElectrodeChangeIndex(currentChange.index);
                if(currentChange.index != -1) {
                    electrodeChanges.push_back(currentChange);
                }
            } while(currentChange.index != -1);

            orgSignal = cleaner.CleanSignal(orgSignal, ui->comboBox_Lead->currentIndex(), electrodeChanges);
        }
    } else {
        if(!rtFile.Load(fileName))
            return;
        orgSignal = rtFile.GetLead(ui->comboBox_Lead->currentIndex());
        filterbench.SetResolution(rtFile.GetResolution());
        QVector<leadoffChange> electrodeChanges;
        if(ui->checkBox_signalCleanup->isChecked()) {
            leadoffChange currentChange;
            currentChange.index = -1;
            do {
                currentChange = rtFile.GetNextElectrodeChangeIndex(currentChange.index);
                if(currentChange.index != -1) {
                    electrodeChanges.push_back(currentChange);
                }
            } while(currentChange.index != -1);

            orgSignal = cleaner.CleanSignal(orgSignal, ui->comboBox_Lead->currentIndex(), electrodeChanges);
        }
    }
    filterbench.FilterSignal(orgSignal, cleaner.GetFilterResetIndexes());
#elif FILE_TYPE == RAW_FILE
    rawFile.Load("D:\\Work\\Tools\\FilterTestTool\\build-FilterTestTool-Desktop_Qt_5_11_2_MinGW_32bit-Debug\\debug\\APAC.RAW");
    filterbench.FilterSignal(rawFile);
#endif
    chartSignal->SetDataPoints(filterbench.GetOriginalSignal(), filterbench.GetFilteredSignal());
    scrollBar_Signal->setMaximum(
                static_cast<int>(
                    (filterbench.GetOriginalSignal().count()/100.0)*
                    (chartSignal->rect().width()-(chartSignal->margins().left()+chartSignal->margins().right())))
                );
    chartSignal->SetTotalDelay(filterbench.GetTotalFilterDelay(),
                               1000 * filterbench.GetTotalFilterDelay() / ui->lineEdit_SamplingFreq->text().toInt());
    scrollBar_Signal->setValue(0);
    scrollBar_Signal->setVisible(true);
    scrollBar_YSpam->setMaximum(chartSignal->getYMax()*1000);
    scrollBar_YSpam->setValue(chartSignal->getYMax()*1000);
    scrollBar_YSpam->setVisible(true);
    setEnableControls(true);
    on_pushButton_UpdateGraph_clicked();
}
