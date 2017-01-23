#ifndef OI_TOTAL_RATIO_CHART_H
#define OI_TOTAL_RATIO_CHART_H

#include <QObject>
#include <QWidget>
#include <QtCharts/QChart>
#include <QLineSeries>

QT_CHARTS_USE_NAMESPACE

class oi_total_ratio_chart : public QChart
{
    Q_OBJECT
public:
    oi_total_ratio_chart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
};

#endif // OI_TOTAL_RATIO_CHART_H
