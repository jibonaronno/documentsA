#include "qSignalChart.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include <math.h>
#include <cfloat>

qSignalChart::qSignalChart(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QChart(parent, wFlags)
{
    withControl = false;
    startPoint = QPointF(-1,-1);
    endPoint = QPointF(-1,-1);
    m_samplesPerScreen = 100;
    setTitle("Signals");
}

void qSignalChart::setPlotTitle(QString title) {
    setTitle(title);
}

void qSignalChart::mousePressEvent(QMouseEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        withControl = true;
        // Ctrl key is pressed
/*        if (event->button() == Qt::LeftButton) {
            // Left button is clicked
            // Check if a series was clicked
            QPointF clickPos = event->pos();
            for (QAbstractSeries* series : series()) {
                // Convert click position to series' coordinate system
                QPointF seriesPos = mapFromScene(clickPos);
                if (series->isVisible() && series->isSmooth()) {
                    // Check if the clicked position is within the series' bounds
                    if (series->boundsOnData(seriesPos).contains(seriesPos)) {
                        // Series is clicked while Ctrl key is pressed
                        // Add your custom logic here
                        break;
                    }
                }
            }
        }
*/
    } else {
        withControl = false;
    }
}

qSignalChart::~qSignalChart()
{

}

void qSignalChart::SetDataPoints(const QVector<QPointF> &orgPoints, const QVector<QPointF> &filteredPoints)
{
    setCursor(QCursor(Qt::CrossCursor));
    if(seriesOrg) {
        seriesOrg->detachAxis(axisX);
        seriesOrg->detachAxis(axisY);
        seriesFiltered->detachAxis(axisX);
        seriesFiltered->detachAxis(axisY);
        removeAxis(axisX);
        removeAxis(axisY);
        removeSeries(seriesOrg);
        removeSeries(seriesFiltered);
    }
    delete seriesOrg;
    seriesOrg = new QLineSeries();
    seriesOrg->setName("Original");
    for(QPointF point : orgPoints) {
        *seriesOrg << point;
    }

    delete seriesFiltered;
    seriesFiltered = new QLineSeries();
    seriesFiltered->setName("Filtered");
    for(QPointF point : filteredPoints) {
        *seriesFiltered << point;
    }
    addSeries(seriesOrg);
    addSeries(seriesFiltered);

    connect(seriesOrg, &QLineSeries::clicked, this, &qSignalChart::seriesClicked);
    connect(seriesFiltered, &QLineSeries::clicked, this, &qSignalChart::seriesClicked);
    connect(seriesOrg, &QLineSeries::hovered, this, &qSignalChart::OrgSeriesHovered);
    connect(seriesFiltered, &QLineSeries::hovered, this, &qSignalChart::FilteredSeriesHovered);

    delete axisX;
    axisX = new QValueAxis();
    axisX->setRange(0, m_samplesPerScreen);
    axisX->setTitleText("Time [samples]");
    addAxis(axisX, Qt::AlignBottom);
    seriesOrg->attachAxis(axisX);
    seriesFiltered->attachAxis(axisX);

    delete axisY;
    axisY = new QValueAxis();
    addAxis(axisY, Qt::AlignLeft);
    seriesFiltered->attachAxis(axisY);
    seriesOrg->attachAxis(axisY);
    absYMax = std::max(findAbsMax(orgPoints),findAbsMax(filteredPoints));
    axisY->setMax(absYMax);
    axisY->setMin(-absYMax);
}

void qSignalChart::setSamplesPerScreen(int samples)
{
    m_samplesPerScreen = samples;
    if(axisX)
        axisX->setRange(0,samples);
}

void qSignalChart::SetTotalDelay(double samples, double ms)
{
    if(axisX) axisX->setTitleText(QString("Time [samples] :        Delay: %1 samples / %2 ms").arg(samples).arg(ms));
}

double qSignalChart::getYMax()
{
    return absYMax;
}

void qSignalChart::setYSpam(double spamm)
{
    if(axisY) {
        axisY->setMax(spamm);
        axisY->setMin(-spamm);
    }
}

void qSignalChart::seriesClicked(const QPointF &point)
{
    if(startPoint.x() < 0) {
        startPoint = point;
    } else {
        endPoint = point;
        if(!withControl) {
            QString text = "The delay is: " + QString::number(fabs(endPoint.x()-startPoint.x())) + " samples";
            QMessageBox::information(nullptr, "Information", text);
            startPoint = QPointF(-1,-1);
            endPoint = QPointF(-1,-1);
        } else {
            // Convert click position to series' coordinate system
            QPointF seriesStartPos = mapFromScene(startPoint);
            QPointF seriesEndPos = mapFromScene(endPoint);
            startPoint = QPointF(-1,-1);
            if (seriesOrg->isVisible()) {
                // Check if the clicked position is within the series' bounds
                qDebug() << seriesOrg->at(seriesStartPos.x()).y()-seriesFiltered->at(seriesEndPos.x()).y();
                //qDebug() << seriesFiltered->at(seriesStartPos.x()).y()-seriesFiltered->at(seriesEndPos.x()).y();

            }
        }
    }
}

void qSignalChart::OrgSeriesHovered(const QPointF &point, bool state)
{
    Q_UNUSED(point);
    QPen pen = seriesOrg->pen();
    if(state) {
        pen.setWidth(3);
    } else
        pen.setWidth(2);
    seriesOrg->setPen(pen);
}

void qSignalChart::FilteredSeriesHovered(const QPointF &point, bool state)
{
    Q_UNUSED(point);
    QPen pen = seriesFiltered->pen();
    if(state) {
        pen.setWidth(3);
    } else
        pen.setWidth(2);
    seriesFiltered->setPen(pen);
}

double qSignalChart::findAbsMax(const QVector<QPointF> &points)
{
    double max = DBL_MIN;
    foreach(QPointF point, points) {
        double val = fabs(point.y());
        if(val > max) max = val;
    }
    return max;
}
