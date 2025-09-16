#include "EMDDialog.h"
#include "ui_EMDDialog.h"
#include "EMD/emd.h"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QPainter>

// https://github.com/myzhang1029/libeemd or https://bitbucket.org/luukko/libeemd/src/master/    Depends on: https://www.gnu.org/software/gsl/

// Also check: https://github.com/zsteve/EMDNetworkSimplex.jl/blob/main/src/emd/EMD_wrapper.cpp

//https://github.com/sorkayi/Empirical-Mode-Decomposition/tree/master


EMDDialog::EMDDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EMDDialog)
{
    ui->setupUi(this);
}

EMDDialog::~EMDDialog()
{
    delete ui;
}

void EMDDialog::setEcgSignal(QVector<int32_t> ecgSignal)
{
    currentImf = 0;
    for(int i=0; i<ecgSignal.count(); i++) {
        orgSignal[i] = ecgSignal[i];
    }

    AddEmdPlot(orgSignal, QString("C%1").arg(QString::number(currentImf)));
    for(int i=1; i<7; i++) {
        AddEmdPlot(imfSignals[currentImf-1], QString("C%1").arg(QString::number(currentImf)));
    }
}

void EMDDialog::AddEmdPlot(double *data, QString caption)
{
    emd(data, SAMPLES_COUNT, imfSignals[currentImf]);
    chart = new QChart;
    chart->legend()->hide();
    chart->setTitle(caption);
    chart->setAcceptHoverEvents(true);

    chartView = new QChartView(this);
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout->addWidget(chartView);

    QLineSeries *seriesOrg = new QLineSeries();
    seriesOrg->setName("Original");
    for(int i=0;i<5000;i++) {
        *seriesOrg << QPointF(i, data[i]/*imfSignals[currentImf][i]*/);
    }
    chart->addSeries(seriesOrg);
    currentImf++;
}
