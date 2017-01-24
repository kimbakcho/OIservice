#include "oi_select_ratio_chartview.h"

oi_select_ratio_chartview::oi_select_ratio_chartview(QChart *chart, QWidget *parent ):
    QChartView(chart, parent),
    m_isTouching(false)
{
    setRubberBand(QChartView::RectangleRubberBand);
}

bool oi_select_ratio_chartview::viewportEvent(QEvent *event)
{
    return QChartView::viewportEvent(event);
}

void oi_select_ratio_chartview::mousePressEvent(QMouseEvent *event)
{

    QChartView::mousePressEvent(event);
}

void oi_select_ratio_chartview::mouseReleaseEvent(QMouseEvent *event)
{

    QChartView::mouseReleaseEvent(event);
}

void oi_select_ratio_chartview::mouseMoveEvent(QMouseEvent *event)
{
    QChartView::mouseMoveEvent(event);
}

void oi_select_ratio_chartview::keyPressEvent(QKeyEvent *event)
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
