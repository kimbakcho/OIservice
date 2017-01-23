#ifndef OI_TOTAL_RATIO_CHARTVIEW_H
#define OI_TOTAL_RATIO_CHARTVIEW_H

#include <QObject>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtWidgets/QRubberBand>
#include <QDebug>
#include <QPointF>
QT_CHARTS_USE_NAMESPACE

class oi_total_ratio_chartview : public QChartView
{
     Q_OBJECT
public:
    oi_total_ratio_chartview(QChart *chart, QWidget *parent = 0);
    QPoint current_point;
    QPoint getCurrent_point() const;
    void setCurrent_point(const QPoint &value);

signals :
    void move_value(QPointF value);
protected :
    bool viewportEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    bool m_isTouching;
};

#endif // OI_TOTAL_RATIO_CHARTVIEW_H
