#ifndef QFREQUENCYVIEW_H
#define QFREQUENCYVIEW_H

#include <QtWidgets/QGraphicsView>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QMutex>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QMouseEvent;
class QResizeEvent;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

class Callout;

QT_CHARTS_USE_NAMESPACE

class qFrequencyView: public QGraphicsView
{
    Q_OBJECT

public:
    qFrequencyView(QWidget *parent = nullptr);
    void SetMaxMinAmplitud_dB(int max, int min);
    void SetDataPoints(const QVector<QPointF> &points, double min, double max);

protected:
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    void keepCallout();
    void tooltip(QPointF point, bool state);

private:
    QGraphicsSimpleTextItem *m_coordX;
    QGraphicsSimpleTextItem *m_coordY;
    QChart *m_chart;
    Callout *m_tooltip;
    QList<Callout *> m_callouts;

    QLineSeries *series = nullptr;
    QValueAxis *axisX = nullptr;
    QValueAxis *axisY = nullptr;
    double m_MaxFreq;
    double m_MinFreq;
    QMutex mutex;
    int m_MaxdB;
    int m_MindB;
};

#endif // QFREQUENCYVIEW_H
