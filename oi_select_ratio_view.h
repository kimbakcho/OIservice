#ifndef OI_SELECT_RATIO_VIEW_H
#define OI_SELECT_RATIO_VIEW_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <oi_select_ratio_chart.h>
#include <oi_select_ratio_chartview.h>
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
class oi_select_ratio_view;
}

class oi_select_ratio_view : public QWidget
{
    Q_OBJECT

public:
    explicit oi_select_ratio_view(QWidget *parent = 0);
    explicit oi_select_ratio_view(QSqlDatabase db,QWidget *parent = 0);
    QSqlDatabase db;
    oi_select_ratio_chart *ratio_select_chart;
    oi_select_ratio_chartview *ratio_select_chartview;

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

    ~oi_select_ratio_view();

    QSqlDatabase getDb() const;
    void setDb(const QSqlDatabase &value);

    void chart_update(QStringList itemlist);
public slots:
    void bar_hovered(bool status,int index);
private slots:
    void on_zoom_init_btn_clicked();

private:
    Ui::oi_select_ratio_view *ui;
};

#endif // OI_SELECT_RATIO_VIEW_H
