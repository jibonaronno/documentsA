#ifndef QSIGNALCHART_H
#define QSIGNALCHART_H

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

class qSignalChart : public QChart
{
    Q_OBJECT
public:
    explicit qSignalChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
    ~qSignalChart();
    void SetDataPoints(const QVector<QPointF> &orgPoints, const QVector<QPointF> &filteredPoints);
    void setSamplesPerScreen(int samples);
    void SetTotalDelay(double samples, double ms);
    double getYMax();
    void setYSpam(double spamm);
    void setPlotTitle(QString title);

protected:
    virtual void mousePressEvent(QMouseEvent* event);

private slots:
    void seriesClicked(const QPointF &point);
    void OrgSeriesHovered(const QPointF &point, bool state);
    void FilteredSeriesHovered(const QPointF &point, bool state);

private:
    QLineSeries *seriesOrg = nullptr;
    QLineSeries *seriesFiltered = nullptr;
    QValueAxis *axisX = nullptr;
    QValueAxis *axisY = nullptr;
    QPointF startPoint;
    QPointF endPoint;
    int m_samplesPerScreen;
    double absYMax;
    bool withControl;

    double findAbsMax(const QVector<QPointF> &points);
};

#endif // QSIGNALCHART_H
