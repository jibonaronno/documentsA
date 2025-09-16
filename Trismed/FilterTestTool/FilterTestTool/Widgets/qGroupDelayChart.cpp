#include "qGroupDelayChart.h"

qGroupDelayChart::qGroupDelayChart(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QChart(parent, wFlags)
{
    legend()->hide();
    setTitle("Group Delay");
}

qGroupDelayChart::~qGroupDelayChart()
{

}

void qGroupDelayChart::SetDataPoints(const QVector<QPointF> &points, double min, double max)
{
    m_MaxFreq = max;
    m_MinFreq = min;
    if(series) {
        series->detachAxis(axisX);
        series->detachAxis(axisY);
        removeAxis(axisX);
        removeAxis(axisY);
        removeSeries(series);
    }
    delete series;
    series = new QLineSeries();
    double maxY = INT32_MIN;
    double minY = INT32_MAX;

    for(QPointF point : points) {
        *series << point;
        if(point.y() > max) maxY = point.y();
        if(point.y() < min) minY = point.y();
    }
    addSeries(series);

    delete axisX;
    axisX = new QValueAxis();
    axisX->setRange(m_MinFreq, m_MaxFreq);
    int ticks = static_cast<int>(1+m_MaxFreq/10);
    axisX->setTickCount(ticks);
    axisX->setMinorTickCount(1);
    axisX->setTitleText("Frequency [Hz]");
    if(m_MaxFreq > 10)
        axisX->setLabelFormat("%d");
    else
        axisX->setLabelFormat("%.3f");
    addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    delete axisY;
    axisY = new QValueAxis();
    axisY->setTitleText("Delay [samples]");
    axisY->setRange(minY, maxY);
    axisY->setTickCount(5);
    axisY->setMinorTickCount(1);
    addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
}
