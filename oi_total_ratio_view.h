#ifndef OI_TOTAL_RATIO_VIEW_H
#define OI_TOTAL_RATIO_VIEW_H

#include <QWidget>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <oi_total_ratio_chart.h>
#include <oi_total_ratio_chartview.h>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QMouseEvent>
#include <QToolTip>
#define Onedaymin 1180
#define DBID "EIS"
#define DBPW "wisolfab!"
#define ROUNDING(x, dig)	( floor((x) * pow(float(10), dig) + 0.5f) / pow(float(10), dig) )
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class oi_total_ratio_view;
}

class oi_total_ratio_view : public QWidget
{
    Q_OBJECT

public:
    explicit oi_total_ratio_view(QWidget *parent = 0);
    explicit oi_total_ratio_view(QSqlDatabase db,QWidget *parent = 0);
    QSqlDatabase db;
    oi_total_ratio_chart *ratio_total_chart;
    oi_total_ratio_chartview *ratio_total_chartview;
    QPoint currentmouse_point;

    QBarSet *Nomal;
    QBarSet *PT ;
    QBarSet *PM ;
    QBarSet *MT;
    QBarSet *WAIT;
    QBarSet *USCHDOWN4 ;
    QBarSet *USCHDOWN1 ;
    QBarSet *SCHDOWN2;
    QBarSet *USCHDOWN2;
    QBarSet *NONSCHED;

    ~oi_total_ratio_view();

    QSqlDatabase getDb() const;
    void setDb(const QSqlDatabase &value);


    void chart_update();
public slots:
    void bar_hovered(bool status,int index);

private:
    Ui::oi_total_ratio_view *ui;
};

#endif // OI_TOTAL_RATIO_VIEW_H
