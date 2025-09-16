#ifndef QGROUPDELAYCHART_H
#define QGROUPDELAYCHART_H

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

class qGroupDelayChart : public QChart
{
    Q_OBJECT
public:
    qGroupDelayChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
    virtual ~qGroupDelayChart();
    void SetDataPoints(const QVector<QPointF> &points, double min, double max);

private:
    QLineSeries *series = nullptr;
    QValueAxis *axisX = nullptr;
    QValueAxis *axisY = nullptr;
    double m_MaxFreq;
    double m_MinFreq;
};

#endif // QGROUPDELAYCHART_H
