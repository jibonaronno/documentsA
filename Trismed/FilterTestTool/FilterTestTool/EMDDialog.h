#ifndef EMDDIALOG_H
#define EMDDIALOG_H

#include <QDialog>
#include <QtCharts/QChartGlobal>
#include <QtWidgets/QGraphicsItem>
#include <QtGui/QFont>

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
class QChartView;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

#define SAMPLES_COUNT 5000
#define MAX_IMF 10

namespace Ui {
class EMDDialog;
}

class EMDDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EMDDialog(QWidget *parent = nullptr);
    ~EMDDialog();

    void setEcgSignal(QVector<int32_t> ecgSignal);

private:
    Ui::EMDDialog *ui;
    QChartView *chartView;
    QChart *chart;

    void AddEmdPlot(double *data, QString caption);

    double orgSignal[SAMPLES_COUNT];
    double imfSignals[MAX_IMF][SAMPLES_COUNT];
    int currentImf;

};

#endif // EMDDIALOG_H
