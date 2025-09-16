#include "qFrequencyChart.h"
#include <QtCharts/QLogValueAxis>

qFrequencyChart::qFrequencyChart(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QChart(parent, wFlags)
{
    legend()->hide();
    setTitle("AC sweep");
}

qFrequencyChart::~qFrequencyChart()
{

}

void qFrequencyChart::SetDataPoints(const QVector<QPointF> &points, double min, double max)
{
    if(series) {
        series->detachAxis(axisX);
        series->detachAxis(axisY);
        removeAxis(axisX);
        removeAxis(axisY);
        removeSeries(series);
    }
    delete series;
    series = new QLineSeries();
    for(QPointF point : points) {
        *series << point;
    }
    addSeries(series);

    m_MaxFreq = max;
    m_MinFreq = min;
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
    axisY->setTitleText("Attenuation [dB]");
//    axisY->setRange(0, 1.1);
    axisY->setRange(-5, 1);
    axisY->setTickCount(11);
    axisY->setMinorTickCount(1);
    addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
}
