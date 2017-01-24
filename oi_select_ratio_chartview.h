#ifndef OI_SELECT_RATIO_CHARTVIEW_H
#define OI_SELECT_RATIO_CHARTVIEW_H

#include <QObject>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtWidgets/QRubberBand>
#include <QDebug>
#include <QPointF>
QT_CHARTS_USE_NAMESPACE
class oi_select_ratio_chartview : public QChartView
{
public:
    oi_select_ratio_chartview(QChart *chart, QWidget *parent = 0);
signals :

protected :
    bool viewportEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    bool m_isTouching;
};

#endif // OI_SELECT_RATIO_CHARTVIEW_H
