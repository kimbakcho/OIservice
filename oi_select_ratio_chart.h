#ifndef OI_SELECT_RATIO_CHART_H
#define OI_SELECT_RATIO_CHART_H

#include <QObject>
#include <QWidget>
#include <QtCharts/QChart>
#include <QLineSeries>

QT_CHARTS_USE_NAMESPACE

class oi_select_ratio_chart : public QChart
{
public:
    oi_select_ratio_chart();
};

#endif // OI_SELECT_RATIO_CHART_H
