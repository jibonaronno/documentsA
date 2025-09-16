/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_Signal;
    QFormLayout *formLayout_2;
    QLabel *label_4;
    QLineEdit *lineEdit_ampliture;
    QLabel *label_5;
    QLineEdit *lineEdit_duration;
    QLineEdit *lineEdit_SamplingFreq;
    QLabel *label_samplingFreq;
    QGroupBox *groupBox_ACSweep;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit_minFreq;
    QLabel *label_2;
    QLineEdit *lineEdit_maxFreq;
    QLabel *label_3;
    QLineEdit *lineEdit_stepFreq;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_default;
    QPushButton *pushButton_defaultHP;
    QLabel *label_AmpMin;
    QLabel *label_AmpMax;
    QLineEdit *lineEdit_MinAmpdB;
    QLineEdit *lineEdit_MaxAmpdB;
    QGroupBox *groupBox_TimeDelay;
    QFormLayout *formLayout_3;
    QLabel *label_6;
    QLineEdit *lineEdit_FreqToShow;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *radioButton_StepResponse;
    QRadioButton *radioButton_Impulse;
    QRadioButton *radioButton_SineWave;
    QTabWidget *tabWidget;
    QWidget *tab_cdp400800;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_Filter;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_Drift;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboBox_driftFreq;
    QCheckBox *checkBox_LP100;
    QCheckBox *checkBox_AC50;
    QCheckBox *checkBox_LP75;
    QCheckBox *checkBox_AC60;
    QCheckBox *checkBox_LP150;
    QGroupBox *groupBox_Muscle;
    QGridLayout *gridLayout_2;
    QCheckBox *checkBox_MUS35;
    QCheckBox *checkBox_MUS25;
    QWidget *tab_iir;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *checkBox_IIR_HP005;
    QCheckBox *checkBox_IIR_HP01;
    QCheckBox *checkBox_IIR_HP015;
    QCheckBox *checkBox_IIR_HP02;
    QCheckBox *checkBox_IIR_HP025;
    QCheckBox *checkBox_IIR_HP032;
    QCheckBox *checkBox_IIR_HP05;
    QCheckBox *checkBox_IIR_HP067;
    QCheckBox *checkBox_IIR_AC60;
    QCheckBox *checkBox_IIR_AC50;
    QSpacerItem *verticalSpacer_2;
    QWidget *tabCardiOffice;
    QCheckBox *checkBox_CoAC60;
    QCheckBox *checkBox_CoAC50;
    QCheckBox *checkBox_CoLP;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *checkBox_FixFiltersDelay;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_process;
    QProgressBar *progressBar;
    QComboBox *comboBox_SignalFiles;
    QHBoxLayout *horizontalLayout_5;
    QComboBox *comboBox_Lead;
    QPushButton *pushButton_LoadAndFilter;
    QCheckBox *checkBox_signalCleanup;
    QGroupBox *groupBox_SignalChart;
    QFormLayout *formLayout_4;
    QLabel *label_7;
    QLineEdit *lineEdit_SamplesPerScreen;
    QPushButton *pushButton_UpdateGraph;
    QSpacerItem *verticalSpacer;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *FrameLayout;
    QButtonGroup *buttonGroupTimeGraph;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1067, 986);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        groupBox_Signal = new QGroupBox(centralWidget);
        groupBox_Signal->setObjectName("groupBox_Signal");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_Signal->sizePolicy().hasHeightForWidth());
        groupBox_Signal->setSizePolicy(sizePolicy);
        groupBox_Signal->setMinimumSize(QSize(200, 0));
        groupBox_Signal->setMaximumSize(QSize(16777215, 16777215));
        formLayout_2 = new QFormLayout(groupBox_Signal);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName("formLayout_2");
        label_4 = new QLabel(groupBox_Signal);
        label_4->setObjectName("label_4");

        formLayout_2->setWidget(1, QFormLayout::ItemRole::LabelRole, label_4);

        lineEdit_ampliture = new QLineEdit(groupBox_Signal);
        lineEdit_ampliture->setObjectName("lineEdit_ampliture");

        formLayout_2->setWidget(1, QFormLayout::ItemRole::FieldRole, lineEdit_ampliture);

        label_5 = new QLabel(groupBox_Signal);
        label_5->setObjectName("label_5");

        formLayout_2->setWidget(2, QFormLayout::ItemRole::LabelRole, label_5);

        lineEdit_duration = new QLineEdit(groupBox_Signal);
        lineEdit_duration->setObjectName("lineEdit_duration");

        formLayout_2->setWidget(2, QFormLayout::ItemRole::FieldRole, lineEdit_duration);

        lineEdit_SamplingFreq = new QLineEdit(groupBox_Signal);
        lineEdit_SamplingFreq->setObjectName("lineEdit_SamplingFreq");

        formLayout_2->setWidget(3, QFormLayout::ItemRole::FieldRole, lineEdit_SamplingFreq);

        label_samplingFreq = new QLabel(groupBox_Signal);
        label_samplingFreq->setObjectName("label_samplingFreq");

        formLayout_2->setWidget(3, QFormLayout::ItemRole::LabelRole, label_samplingFreq);


        verticalLayout->addWidget(groupBox_Signal);

        groupBox_ACSweep = new QGroupBox(centralWidget);
        groupBox_ACSweep->setObjectName("groupBox_ACSweep");
        sizePolicy.setHeightForWidth(groupBox_ACSweep->sizePolicy().hasHeightForWidth());
        groupBox_ACSweep->setSizePolicy(sizePolicy);
        groupBox_ACSweep->setMinimumSize(QSize(200, 0));
        groupBox_ACSweep->setMaximumSize(QSize(16777215, 16777215));
        formLayout = new QFormLayout(groupBox_ACSweep);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName("formLayout");
        label = new QLabel(groupBox_ACSweep);
        label->setObjectName("label");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label);

        lineEdit_minFreq = new QLineEdit(groupBox_ACSweep);
        lineEdit_minFreq->setObjectName("lineEdit_minFreq");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, lineEdit_minFreq);

        label_2 = new QLabel(groupBox_ACSweep);
        label_2->setObjectName("label_2");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_2);

        lineEdit_maxFreq = new QLineEdit(groupBox_ACSweep);
        lineEdit_maxFreq->setObjectName("lineEdit_maxFreq");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, lineEdit_maxFreq);

        label_3 = new QLabel(groupBox_ACSweep);
        label_3->setObjectName("label_3");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, label_3);

        lineEdit_stepFreq = new QLineEdit(groupBox_ACSweep);
        lineEdit_stepFreq->setObjectName("lineEdit_stepFreq");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, lineEdit_stepFreq);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout_3->setContentsMargins(0, 0, -1, -1);
        pushButton_default = new QPushButton(groupBox_ACSweep);
        pushButton_default->setObjectName("pushButton_default");

        horizontalLayout_3->addWidget(pushButton_default);

        pushButton_defaultHP = new QPushButton(groupBox_ACSweep);
        pushButton_defaultHP->setObjectName("pushButton_defaultHP");

        horizontalLayout_3->addWidget(pushButton_defaultHP);


        formLayout->setLayout(0, QFormLayout::ItemRole::SpanningRole, horizontalLayout_3);

        label_AmpMin = new QLabel(groupBox_ACSweep);
        label_AmpMin->setObjectName("label_AmpMin");

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, label_AmpMin);

        label_AmpMax = new QLabel(groupBox_ACSweep);
        label_AmpMax->setObjectName("label_AmpMax");

        formLayout->setWidget(6, QFormLayout::ItemRole::LabelRole, label_AmpMax);

        lineEdit_MinAmpdB = new QLineEdit(groupBox_ACSweep);
        lineEdit_MinAmpdB->setObjectName("lineEdit_MinAmpdB");

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, lineEdit_MinAmpdB);

        lineEdit_MaxAmpdB = new QLineEdit(groupBox_ACSweep);
        lineEdit_MaxAmpdB->setObjectName("lineEdit_MaxAmpdB");

        formLayout->setWidget(6, QFormLayout::ItemRole::FieldRole, lineEdit_MaxAmpdB);


        verticalLayout->addWidget(groupBox_ACSweep);

        groupBox_TimeDelay = new QGroupBox(centralWidget);
        groupBox_TimeDelay->setObjectName("groupBox_TimeDelay");
        sizePolicy.setHeightForWidth(groupBox_TimeDelay->sizePolicy().hasHeightForWidth());
        groupBox_TimeDelay->setSizePolicy(sizePolicy);
        formLayout_3 = new QFormLayout(groupBox_TimeDelay);
        formLayout_3->setSpacing(6);
        formLayout_3->setContentsMargins(11, 11, 11, 11);
        formLayout_3->setObjectName("formLayout_3");
        label_6 = new QLabel(groupBox_TimeDelay);
        label_6->setObjectName("label_6");

        formLayout_3->setWidget(0, QFormLayout::ItemRole::LabelRole, label_6);

        lineEdit_FreqToShow = new QLineEdit(groupBox_TimeDelay);
        lineEdit_FreqToShow->setObjectName("lineEdit_FreqToShow");

        formLayout_3->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEdit_FreqToShow);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, -1, -1);
        radioButton_StepResponse = new QRadioButton(groupBox_TimeDelay);
        buttonGroupTimeGraph = new QButtonGroup(MainWindow);
        buttonGroupTimeGraph->setObjectName("buttonGroupTimeGraph");
        buttonGroupTimeGraph->addButton(radioButton_StepResponse);
        radioButton_StepResponse->setObjectName("radioButton_StepResponse");

        horizontalLayout_6->addWidget(radioButton_StepResponse);

        radioButton_Impulse = new QRadioButton(groupBox_TimeDelay);
        buttonGroupTimeGraph->addButton(radioButton_Impulse);
        radioButton_Impulse->setObjectName("radioButton_Impulse");

        horizontalLayout_6->addWidget(radioButton_Impulse);

        radioButton_SineWave = new QRadioButton(groupBox_TimeDelay);
        buttonGroupTimeGraph->addButton(radioButton_SineWave);
        radioButton_SineWave->setObjectName("radioButton_SineWave");
        radioButton_SineWave->setChecked(true);

        horizontalLayout_6->addWidget(radioButton_SineWave);


        formLayout_3->setLayout(1, QFormLayout::ItemRole::SpanningRole, horizontalLayout_6);


        verticalLayout->addWidget(groupBox_TimeDelay);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tab_cdp400800 = new QWidget();
        tab_cdp400800->setObjectName("tab_cdp400800");
        gridLayout_3 = new QGridLayout(tab_cdp400800);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName("gridLayout_3");
        groupBox_Filter = new QGroupBox(tab_cdp400800);
        groupBox_Filter->setObjectName("groupBox_Filter");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_Filter->sizePolicy().hasHeightForWidth());
        groupBox_Filter->setSizePolicy(sizePolicy2);
        groupBox_Filter->setMinimumSize(QSize(200, 0));
        groupBox_Filter->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(groupBox_Filter);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        groupBox_Drift = new QGroupBox(groupBox_Filter);
        groupBox_Drift->setObjectName("groupBox_Drift");
        groupBox_Drift->setCheckable(true);
        groupBox_Drift->setChecked(false);
        verticalLayout_2 = new QVBoxLayout(groupBox_Drift);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        comboBox_driftFreq = new QComboBox(groupBox_Drift);
        comboBox_driftFreq->setObjectName("comboBox_driftFreq");

        verticalLayout_2->addWidget(comboBox_driftFreq);


        gridLayout->addWidget(groupBox_Drift, 5, 0, 1, 2);

        checkBox_LP100 = new QCheckBox(groupBox_Filter);
        checkBox_LP100->setObjectName("checkBox_LP100");

        gridLayout->addWidget(checkBox_LP100, 1, 1, 1, 1);

        checkBox_AC50 = new QCheckBox(groupBox_Filter);
        checkBox_AC50->setObjectName("checkBox_AC50");

        gridLayout->addWidget(checkBox_AC50, 0, 0, 1, 1);

        checkBox_LP75 = new QCheckBox(groupBox_Filter);
        checkBox_LP75->setObjectName("checkBox_LP75");

        gridLayout->addWidget(checkBox_LP75, 0, 1, 1, 1);

        checkBox_AC60 = new QCheckBox(groupBox_Filter);
        checkBox_AC60->setObjectName("checkBox_AC60");

        gridLayout->addWidget(checkBox_AC60, 1, 0, 1, 1);

        checkBox_LP150 = new QCheckBox(groupBox_Filter);
        checkBox_LP150->setObjectName("checkBox_LP150");

        gridLayout->addWidget(checkBox_LP150, 3, 1, 1, 1);

        groupBox_Muscle = new QGroupBox(groupBox_Filter);
        groupBox_Muscle->setObjectName("groupBox_Muscle");
        groupBox_Muscle->setCheckable(false);
        gridLayout_2 = new QGridLayout(groupBox_Muscle);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        checkBox_MUS35 = new QCheckBox(groupBox_Muscle);
        checkBox_MUS35->setObjectName("checkBox_MUS35");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(checkBox_MUS35->sizePolicy().hasHeightForWidth());
        checkBox_MUS35->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(checkBox_MUS35, 1, 0, 1, 1);

        checkBox_MUS25 = new QCheckBox(groupBox_Muscle);
        checkBox_MUS25->setObjectName("checkBox_MUS25");
        checkBox_MUS25->setChecked(false);

        gridLayout_2->addWidget(checkBox_MUS25, 1, 1, 1, 1);


        gridLayout->addWidget(groupBox_Muscle, 4, 0, 1, 2);


        gridLayout_3->addWidget(groupBox_Filter, 0, 0, 1, 1);

        tabWidget->addTab(tab_cdp400800, QString());
        tab_iir = new QWidget();
        tab_iir->setObjectName("tab_iir");
        verticalLayout_4 = new QVBoxLayout(tab_iir);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        checkBox_IIR_HP005 = new QCheckBox(tab_iir);
        checkBox_IIR_HP005->setObjectName("checkBox_IIR_HP005");

        verticalLayout_4->addWidget(checkBox_IIR_HP005);

        checkBox_IIR_HP01 = new QCheckBox(tab_iir);
        checkBox_IIR_HP01->setObjectName("checkBox_IIR_HP01");
        checkBox_IIR_HP01->setChecked(false);

        verticalLayout_4->addWidget(checkBox_IIR_HP01);

        checkBox_IIR_HP015 = new QCheckBox(tab_iir);
        checkBox_IIR_HP015->setObjectName("checkBox_IIR_HP015");

        verticalLayout_4->addWidget(checkBox_IIR_HP015);

        checkBox_IIR_HP02 = new QCheckBox(tab_iir);
        checkBox_IIR_HP02->setObjectName("checkBox_IIR_HP02");

        verticalLayout_4->addWidget(checkBox_IIR_HP02);

        checkBox_IIR_HP025 = new QCheckBox(tab_iir);
        checkBox_IIR_HP025->setObjectName("checkBox_IIR_HP025");

        verticalLayout_4->addWidget(checkBox_IIR_HP025);

        checkBox_IIR_HP032 = new QCheckBox(tab_iir);
        checkBox_IIR_HP032->setObjectName("checkBox_IIR_HP032");

        verticalLayout_4->addWidget(checkBox_IIR_HP032);

        checkBox_IIR_HP05 = new QCheckBox(tab_iir);
        checkBox_IIR_HP05->setObjectName("checkBox_IIR_HP05");

        verticalLayout_4->addWidget(checkBox_IIR_HP05);

        checkBox_IIR_HP067 = new QCheckBox(tab_iir);
        checkBox_IIR_HP067->setObjectName("checkBox_IIR_HP067");

        verticalLayout_4->addWidget(checkBox_IIR_HP067);

        checkBox_IIR_AC60 = new QCheckBox(tab_iir);
        checkBox_IIR_AC60->setObjectName("checkBox_IIR_AC60");

        verticalLayout_4->addWidget(checkBox_IIR_AC60);

        checkBox_IIR_AC50 = new QCheckBox(tab_iir);
        checkBox_IIR_AC50->setObjectName("checkBox_IIR_AC50");

        verticalLayout_4->addWidget(checkBox_IIR_AC50);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        tabWidget->addTab(tab_iir, QString());
        tabCardiOffice = new QWidget();
        tabCardiOffice->setObjectName("tabCardiOffice");
        checkBox_CoAC60 = new QCheckBox(tabCardiOffice);
        checkBox_CoAC60->setObjectName("checkBox_CoAC60");
        checkBox_CoAC60->setGeometry(QRect(20, 20, 70, 17));
        checkBox_CoAC50 = new QCheckBox(tabCardiOffice);
        checkBox_CoAC50->setObjectName("checkBox_CoAC50");
        checkBox_CoAC50->setGeometry(QRect(20, 50, 70, 17));
        checkBox_CoLP = new QCheckBox(tabCardiOffice);
        checkBox_CoLP->setObjectName("checkBox_CoLP");
        checkBox_CoLP->setGeometry(QRect(20, 80, 101, 17));
        tabWidget->addTab(tabCardiOffice, QString());

        verticalLayout->addWidget(tabWidget);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName("groupBox");
        groupBox->setMinimumSize(QSize(0, 0));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        checkBox_FixFiltersDelay = new QCheckBox(groupBox);
        checkBox_FixFiltersDelay->setObjectName("checkBox_FixFiltersDelay");
        checkBox_FixFiltersDelay->setChecked(true);

        verticalLayout_3->addWidget(checkBox_FixFiltersDelay);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        pushButton_process = new QPushButton(groupBox);
        pushButton_process->setObjectName("pushButton_process");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pushButton_process->sizePolicy().hasHeightForWidth());
        pushButton_process->setSizePolicy(sizePolicy4);

        horizontalLayout_4->addWidget(pushButton_process);

        progressBar = new QProgressBar(groupBox);
        progressBar->setObjectName("progressBar");
        sizePolicy3.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy3);
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        horizontalLayout_4->addWidget(progressBar);


        verticalLayout_3->addLayout(horizontalLayout_4);

        comboBox_SignalFiles = new QComboBox(groupBox);
        comboBox_SignalFiles->setObjectName("comboBox_SignalFiles");

        verticalLayout_3->addWidget(comboBox_SignalFiles);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(-1, 0, -1, -1);
        comboBox_Lead = new QComboBox(groupBox);
        comboBox_Lead->addItem(QString());
        comboBox_Lead->addItem(QString());
        comboBox_Lead->addItem(QString());
        comboBox_Lead->addItem(QString());
        comboBox_Lead->addItem(QString());
        comboBox_Lead->addItem(QString());
        comboBox_Lead->addItem(QString());
        comboBox_Lead->addItem(QString());
        comboBox_Lead->setObjectName("comboBox_Lead");
        comboBox_Lead->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_5->addWidget(comboBox_Lead);

        pushButton_LoadAndFilter = new QPushButton(groupBox);
        pushButton_LoadAndFilter->setObjectName("pushButton_LoadAndFilter");

        horizontalLayout_5->addWidget(pushButton_LoadAndFilter);


        verticalLayout_3->addLayout(horizontalLayout_5);

        checkBox_signalCleanup = new QCheckBox(groupBox);
        checkBox_signalCleanup->setObjectName("checkBox_signalCleanup");
        checkBox_signalCleanup->setChecked(true);

        verticalLayout_3->addWidget(checkBox_signalCleanup);


        verticalLayout->addWidget(groupBox);

        groupBox_SignalChart = new QGroupBox(centralWidget);
        groupBox_SignalChart->setObjectName("groupBox_SignalChart");
        sizePolicy.setHeightForWidth(groupBox_SignalChart->sizePolicy().hasHeightForWidth());
        groupBox_SignalChart->setSizePolicy(sizePolicy);
        formLayout_4 = new QFormLayout(groupBox_SignalChart);
        formLayout_4->setSpacing(6);
        formLayout_4->setContentsMargins(11, 11, 11, 11);
        formLayout_4->setObjectName("formLayout_4");
        label_7 = new QLabel(groupBox_SignalChart);
        label_7->setObjectName("label_7");

        formLayout_4->setWidget(0, QFormLayout::ItemRole::LabelRole, label_7);

        lineEdit_SamplesPerScreen = new QLineEdit(groupBox_SignalChart);
        lineEdit_SamplesPerScreen->setObjectName("lineEdit_SamplesPerScreen");

        formLayout_4->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEdit_SamplesPerScreen);

        pushButton_UpdateGraph = new QPushButton(groupBox_SignalChart);
        pushButton_UpdateGraph->setObjectName("pushButton_UpdateGraph");

        formLayout_4->setWidget(1, QFormLayout::ItemRole::FieldRole, pushButton_UpdateGraph);


        verticalLayout->addWidget(groupBox_SignalChart);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        FrameLayout = new QVBoxLayout();
        FrameLayout->setSpacing(0);
        FrameLayout->setObjectName("FrameLayout");
        FrameLayout->setSizeConstraint(QLayout::SetMinimumSize);

        horizontalLayout_2->addLayout(FrameLayout);


        horizontalLayout->addWidget(frame);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 8);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        comboBox_driftFreq->setCurrentIndex(-1);
        comboBox_Lead->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox_Signal->setTitle(QCoreApplication::translate("MainWindow", "Signal:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Amplitude [mV]", nullptr));
        lineEdit_ampliture->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Duration [s]", nullptr));
        lineEdit_duration->setText(QCoreApplication::translate("MainWindow", "30", nullptr));
        lineEdit_SamplingFreq->setText(QCoreApplication::translate("MainWindow", "500", nullptr));
        label_samplingFreq->setText(QCoreApplication::translate("MainWindow", "Sampling Frequency [Hz]", nullptr));
        groupBox_ACSweep->setTitle(QCoreApplication::translate("MainWindow", "AC sweep:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Lowest Frequency [Hz]", nullptr));
        lineEdit_minFreq->setInputMask(QString());
        lineEdit_minFreq->setText(QCoreApplication::translate("MainWindow", "0.1", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Highest Frequency [Hz]", nullptr));
        lineEdit_maxFreq->setInputMask(QString());
        lineEdit_maxFreq->setText(QCoreApplication::translate("MainWindow", "80", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Frequency Step [Hz]", nullptr));
        lineEdit_stepFreq->setText(QCoreApplication::translate("MainWindow", "0.2", nullptr));
        pushButton_default->setText(QCoreApplication::translate("MainWindow", "Default", nullptr));
        pushButton_defaultHP->setText(QCoreApplication::translate("MainWindow", "Default HP", nullptr));
        label_AmpMin->setText(QCoreApplication::translate("MainWindow", "Amp Min [dB]:", nullptr));
        label_AmpMax->setText(QCoreApplication::translate("MainWindow", "Amp Max [dB]:", nullptr));
        lineEdit_MinAmpdB->setText(QCoreApplication::translate("MainWindow", "-60", nullptr));
        lineEdit_MaxAmpdB->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        groupBox_TimeDelay->setTitle(QCoreApplication::translate("MainWindow", "Time Delay Graph", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Frequency to show [Hz]:", nullptr));
        lineEdit_FreqToShow->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        radioButton_StepResponse->setText(QCoreApplication::translate("MainWindow", "Step Response", nullptr));
        radioButton_Impulse->setText(QCoreApplication::translate("MainWindow", "Impulse Rerponse", nullptr));
        radioButton_SineWave->setText(QCoreApplication::translate("MainWindow", "Sine Wave", nullptr));
        groupBox_Filter->setTitle(QCoreApplication::translate("MainWindow", "Filters (Cardipia 440H / 800H):", nullptr));
        groupBox_Drift->setTitle(QCoreApplication::translate("MainWindow", "Drift", nullptr));
        checkBox_LP100->setText(QCoreApplication::translate("MainWindow", "LP100", nullptr));
        checkBox_AC50->setText(QCoreApplication::translate("MainWindow", "AC50", nullptr));
        checkBox_LP75->setText(QCoreApplication::translate("MainWindow", "LP75", nullptr));
        checkBox_AC60->setText(QCoreApplication::translate("MainWindow", "AC60", nullptr));
        checkBox_LP150->setText(QCoreApplication::translate("MainWindow", "LP150", nullptr));
        groupBox_Muscle->setTitle(QCoreApplication::translate("MainWindow", "Muscle", nullptr));
        checkBox_MUS35->setText(QCoreApplication::translate("MainWindow", "MUS35", nullptr));
        checkBox_MUS25->setText(QCoreApplication::translate("MainWindow", "MUS25", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_cdp400800), QCoreApplication::translate("MainWindow", "Cardipia 400H / 800H", nullptr));
        checkBox_IIR_HP005->setText(QCoreApplication::translate("MainWindow", "HP 0.05Hz", nullptr));
        checkBox_IIR_HP01->setText(QCoreApplication::translate("MainWindow", "HP 0.1Hz", nullptr));
        checkBox_IIR_HP015->setText(QCoreApplication::translate("MainWindow", "HP 0.15Hz", nullptr));
        checkBox_IIR_HP02->setText(QCoreApplication::translate("MainWindow", "HP 0.2Hz", nullptr));
        checkBox_IIR_HP025->setText(QCoreApplication::translate("MainWindow", "HP 0.25Hz", nullptr));
        checkBox_IIR_HP032->setText(QCoreApplication::translate("MainWindow", "HP 0.32Hz", nullptr));
        checkBox_IIR_HP05->setText(QCoreApplication::translate("MainWindow", "HP 0.5Hz", nullptr));
        checkBox_IIR_HP067->setText(QCoreApplication::translate("MainWindow", "HP 0.67Hz", nullptr));
        checkBox_IIR_AC60->setText(QCoreApplication::translate("MainWindow", "AC 60Hz", nullptr));
        checkBox_IIR_AC50->setText(QCoreApplication::translate("MainWindow", "AC 50Hz", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_iir), QCoreApplication::translate("MainWindow", "IIR", nullptr));
        checkBox_CoAC60->setText(QCoreApplication::translate("MainWindow", "AC 60Hz", nullptr));
        checkBox_CoAC50->setText(QCoreApplication::translate("MainWindow", "AC 50Hz", nullptr));
        checkBox_CoLP->setText(QCoreApplication::translate("MainWindow", "LowPass (MA)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabCardiOffice), QCoreApplication::translate("MainWindow", "CardiOffice", nullptr));
        groupBox->setTitle(QString());
        checkBox_FixFiltersDelay->setText(QCoreApplication::translate("MainWindow", "Fix Filter Delays", nullptr));
        pushButton_process->setText(QCoreApplication::translate("MainWindow", "Process", nullptr));
        comboBox_Lead->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        comboBox_Lead->setItemText(1, QCoreApplication::translate("MainWindow", "2", nullptr));
        comboBox_Lead->setItemText(2, QCoreApplication::translate("MainWindow", "3", nullptr));
        comboBox_Lead->setItemText(3, QCoreApplication::translate("MainWindow", "4", nullptr));
        comboBox_Lead->setItemText(4, QCoreApplication::translate("MainWindow", "5", nullptr));
        comboBox_Lead->setItemText(5, QCoreApplication::translate("MainWindow", "6", nullptr));
        comboBox_Lead->setItemText(6, QCoreApplication::translate("MainWindow", "7", nullptr));
        comboBox_Lead->setItemText(7, QCoreApplication::translate("MainWindow", "8", nullptr));

        pushButton_LoadAndFilter->setText(QCoreApplication::translate("MainWindow", "Load and Filter Signal", nullptr));
        checkBox_signalCleanup->setText(QCoreApplication::translate("MainWindow", "Signal cleanup using leadoff information", nullptr));
        groupBox_SignalChart->setTitle(QCoreApplication::translate("MainWindow", "Signal chart:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Samples per screen:", nullptr));
        lineEdit_SamplesPerScreen->setText(QCoreApplication::translate("MainWindow", "500", nullptr));
        pushButton_UpdateGraph->setText(QCoreApplication::translate("MainWindow", "Update >>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
