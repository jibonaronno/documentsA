#ifndef QFREQUENCYCHART_H
#define QFREQUENCYCHART_H

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

class qFrequencyChart : public QChart
{
    Q_OBJECT
public:
    explicit qFrequencyChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
    virtual ~qFrequencyChart();
    void SetDataPoints(const QVector<QPointF> &points, double min, double max);
private:
    QLineSeries *series = nullptr;
    QValueAxis *axisX = nullptr;
    QValueAxis *axisY = nullptr;
    double m_MaxFreq;
    double m_MinFreq;
};

#endif // QFREQUENCYCHART_H
