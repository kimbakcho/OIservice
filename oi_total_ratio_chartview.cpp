#include "oi_total_ratio_chartview.h"

oi_total_ratio_chartview::oi_total_ratio_chartview(QChart *chart, QWidget *parent):
    QChartView(chart, parent),
    m_isTouching(false)
{
    setRubberBand(QChartView::RectangleRubberBand);
}

QPoint oi_total_ratio_chartview::getCurrent_point() const
{
    return current_point;
}

void oi_total_ratio_chartview::setCurrent_point(const QPoint &value)
{
    current_point = value;
}

bool oi_total_ratio_chartview::viewportEvent(QEvent *event)
{
    //    if (event->type() == QEvent::TouchBegin) {
    //        // By default touch events are converted to mouse events. So
    //        // after this event we will get a mouse event also but we want
    //        // to handle touch events as gestures only. So we need this safeguard
    //        // to block mouse events that are actually generated from touch.
    //        m_isTouching = true;

    //        // Turn off animations when handling gestures they
    //        // will only slow us down.
    //        chart()->setAnimationOptions(QChart::NoAnimation);
    //    }
    return QChartView::viewportEvent(event);
}

void oi_total_ratio_chartview::mousePressEvent(QMouseEvent *event)
{
    if (m_isTouching)
        return;
    QChartView::mousePressEvent(event);
}

void oi_total_ratio_chartview::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_isTouching)
        m_isTouching = false;

    // Because we disabled animations when touch event was detected
    // we must put them back on.
//    chart()->setAnimationOptions(QChart::SeriesAnimations);

    QChartView::mouseReleaseEvent(event);
}

void oi_total_ratio_chartview::mouseMoveEvent(QMouseEvent *event)
{
    current_point = event->globalPos();
    QChartView::mouseMoveEvent(event);
    if (m_isTouching)
        return;
}

void oi_total_ratio_chartview::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        chart()->zoomIn();
        break;
    case Qt::Key_Minus:
        chart()->zoomOut();
        break;
    case Qt::Key_Left:
        chart()->scroll(-10, 0);
        break;
    case Qt::Key_Right:
        chart()->scroll(10, 0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, 10);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, -10);
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}
