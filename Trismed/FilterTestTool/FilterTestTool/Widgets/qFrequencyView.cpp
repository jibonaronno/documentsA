#include "qFrequencyView.h"

#include <QtGui/QResizeEvent>
#include <QtWidgets/QGraphicsScene>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtWidgets/QGraphicsTextItem>
#include <QValueAxis>
#include "Callout.h"
#include <QtGui/QMouseEvent>
#include <QDebug>

qFrequencyView::qFrequencyView(QWidget *parent)
    : QGraphicsView(new QGraphicsScene, parent),
      m_coordX(nullptr),
      m_coordY(nullptr),
      m_chart(nullptr),
      m_tooltip(nullptr),
      m_MaxdB(1),
      m_MindB(-60)
{
    setDragMode(QGraphicsView::NoDrag);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // chart
    m_chart = new QChart;
    m_chart->legend()->hide();
    m_chart->setTitle("AC sweep");
    m_chart->setAcceptHoverEvents(true);

    setRenderHint(QPainter::Antialiasing);
    scene()->addItem(m_chart);

    setMouseTracking(true);
}

void qFrequencyView::SetMaxMinAmplitud_dB(int max, int min)
{
    m_MindB = min;
    m_MaxdB = max;
}

void qFrequencyView::SetDataPoints(const QVector<QPointF> &points, double min, double max)
{
    mutex.lock();
    setMouseTracking(false);
    scene()->removeItem(m_chart);
    if(series) {
        disconnect(series, &QLineSeries::clicked, this, &qFrequencyView::keepCallout);
        disconnect(series, &QLineSeries::hovered, this, &qFrequencyView::tooltip);
        series->detachAxis(axisX);
        series->detachAxis(axisY);
        m_chart->removeAxis(axisX);
        m_chart->removeAxis(axisY);
        m_chart->removeSeries(series);
        for(auto serie : m_chart->series()) {
            m_chart->removeSeries(serie);
        }

    }
    const auto callouts = m_callouts;
    for (Callout *callout : callouts) {
        delete callout;
    }

    m_callouts.clear();
    delete m_tooltip;
    m_tooltip = nullptr;
    delete series;
    series = new QLineSeries();
    for(QPointF point : points) {
        *series << point;
    }
    m_chart->addSeries(series);

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
    m_chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    delete axisY;
    axisY = new QValueAxis();
    axisY->setTitleText("Attenuation [dB]");
//    axisY->setRange(0, 1.1);
    axisY->setRange(m_MindB, m_MaxdB);
    axisY->setTickCount(11);
    axisY->setMinorTickCount(1);
    m_chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    scene()->addItem(m_chart);
    setMouseTracking(true);

    connect(series, &QLineSeries::clicked, this, &qFrequencyView::keepCallout);
    connect(series, &QLineSeries::hovered, this, &qFrequencyView::tooltip);
    mutex.unlock();
}

void qFrequencyView::resizeEvent(QResizeEvent *event)
{
    if (scene()) {
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
        m_chart->resize(event->size());
//        m_coordX->setPos(m_chart->size().width()/2 - 50, m_chart->size().height() - 20);
//        m_coordY->setPos(m_chart->size().width()/2 + 50, m_chart->size().height() - 20);
        mutex.lock();
        const auto callouts = m_callouts;
        for (Callout *callout : callouts)
            callout->updateGeometry();
        mutex.unlock();
    }
    QGraphicsView::resizeEvent(event);
}

void qFrequencyView::mouseMoveEvent(QMouseEvent *event)
{
//    m_coordX->setText(QString("X: %1").arg(m_chart->mapToValue(event->pos()).x()));
//    m_coordY->setText(QString("Y: %1").arg(m_chart->mapToValue(event->pos()).y()));
    QGraphicsView::mouseMoveEvent(event);
}

void qFrequencyView::keepCallout()
{
    QAbstractSeries *series = qobject_cast<QAbstractSeries *>(sender());
    m_callouts.append(m_tooltip);

    m_tooltip = new Callout(m_chart, series);
    m_tooltip->hide();
}

void qFrequencyView::tooltip(QPointF point, bool state)
{
    QAbstractSeries *series = qobject_cast<QAbstractSeries *>(sender());
    if (m_tooltip == nullptr){
        m_tooltip = new Callout(m_chart, series);
    }
    if (state) {
        m_tooltip->setSeries(series);
        m_tooltip->setText(QString("X: %1 \nY: %2 ").arg(point.x()).arg(point.y()));
        m_tooltip->setAnchor(point);
        m_tooltip->setZValue(11);
        m_tooltip->updateGeometry();
        m_tooltip->show();
    } else {
        m_tooltip->hide();
    }
}
