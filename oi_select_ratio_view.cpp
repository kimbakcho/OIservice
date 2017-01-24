#include "oi_select_ratio_view.h"
#include "ui_oi_select_ratio_view.h"

#include "mainwindow.h"

extern MainWindow *m_window;

oi_select_ratio_view::oi_select_ratio_view(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::oi_select_ratio_view)
{
    ui->setupUi(this);
    ratio_select_chart = new oi_select_ratio_chart();
    ratio_select_chart->setAnimationOptions(QChart::SeriesAnimations);
    ratio_select_chartview = new oi_select_ratio_chartview(ratio_select_chart);
    ratio_select_chartview->setRenderHint(QPainter::Antialiasing);
    ui->center_layout->addWidget(ratio_select_chartview);
}

oi_select_ratio_view::oi_select_ratio_view(QSqlDatabase db, QWidget *parent):
    QWidget(parent),
    ui(new Ui::oi_select_ratio_view)
{
    ui->setupUi(this);
    ratio_select_chart = new oi_select_ratio_chart();
    ratio_select_chart->setAnimationOptions(QChart::SeriesAnimations);
    ratio_select_chartview = new oi_select_ratio_chartview(ratio_select_chart);
    ratio_select_chartview->setRenderHint(QPainter::Antialiasing);
    ui->center_layout->addWidget(ratio_select_chartview);
}

QSqlDatabase oi_select_ratio_view::getDb() const
{
    return db;
}

void oi_select_ratio_view::setDb(const QSqlDatabase &value)
{
    db = value;
}

void oi_select_ratio_view::chart_update(QStringList itemlist)
{
    ratio_select_chart->removeAllSeries();
    if(ratio_select_chart->axisX()!=NULL){
        ratio_select_chart->removeAxis(ratio_select_chart->axisX());
    }


    Nomal = new QBarSet(tr("run"));
    PT = new QBarSet(tr("PT"));
    PM = new QBarSet(tr("PM"));
    MT = new QBarSet(tr("MT"));
    WAIT = new QBarSet(tr("WAIT"));
    USCHDOWN4 =new QBarSet(tr("USCHDOWN4"));
    USCHDOWN1 =new QBarSet(tr("USCHDOWN1"));
    SCHDOWN2 =new QBarSet(tr("SCHDOWN2"));
    USCHDOWN2 =new QBarSet(tr("USCHDOWN2"));
    NONSCHED =new QBarSet(tr("NONSCHED"));

    connect(Nomal,SIGNAL(hovered(bool,int)),this,SLOT(bar_hovered(bool,int)));
    connect(PT,SIGNAL(hovered(bool,int)),this,SLOT(bar_hovered(bool,int)));
    connect(PM,SIGNAL(hovered(bool,int)),this,SLOT(bar_hovered(bool,int)));
    connect(MT,SIGNAL(hovered(bool,int)),this,SLOT(bar_hovered(bool,int)));
    connect(WAIT,SIGNAL(hovered(bool,int)),this,SLOT(bar_hovered(bool,int)));
    connect(USCHDOWN4,SIGNAL(hovered(bool,int)),this,SLOT(bar_hovered(bool,int)));
    connect(USCHDOWN1,SIGNAL(hovered(bool,int)),this,SLOT(bar_hovered(bool,int)));
    connect(SCHDOWN2,SIGNAL(hovered(bool,int)),this,SLOT(bar_hovered(bool,int)));
    connect(USCHDOWN2,SIGNAL(hovered(bool,int)),this,SLOT(bar_hovered(bool,int)));
    connect(NONSCHED,SIGNAL(hovered(bool,int)),this,SLOT(bar_hovered(bool,int)));

    QSqlQuery query5(db);
    QString where_search;
    for(int i=0;i<itemlist.size();i++){
        if(i == itemlist.size()-1){
            where_search.append(QString("machine_name = '%1'").arg(itemlist.at(i)));
        }else {
            where_search.append(QString("machine_name = '%1' OR ").arg(itemlist.at(i)));
        }
    }
    query5.exec(QString("select * from OI_system_time_2 where %1").arg(where_search));
    QStringList categories;
    while(query5.next()){
        Nomal->append(ROUNDING(query5.value("rate").toDouble(),2));
        PT->append(ROUNDING(query5.value("PTrate").toDouble(),2));
        PM->append(ROUNDING(query5.value("PMrate").toDouble(),2));
        MT->append(ROUNDING(query5.value("MTrate").toDouble(),2));
        WAIT->append(ROUNDING(query5.value("Waitrate").toDouble(),2));
        USCHDOWN4->append(ROUNDING(query5.value("USCHDOWN4").toDouble(),2));
        USCHDOWN1->append(ROUNDING(query5.value("USCHDOWN1").toDouble(),2));
        SCHDOWN2->append(ROUNDING(query5.value("SCHDOWN2").toDouble(),2));
        USCHDOWN2->append(ROUNDING(query5.value("USCHDOWN2").toDouble(),2));
        NONSCHED->append(ROUNDING(query5.value("NONSCHED").toDouble(),2));
        categories.append(query5.value("machine_name").toString());
    }
    QStackedBarSeries *series = new QStackedBarSeries();
    series->append(Nomal);
    series->append(PT);
    series->append(PM);
    series->append(MT);
    series->append(WAIT);
    series->append(USCHDOWN4);
    series->append(USCHDOWN1);
    series->append(SCHDOWN2);
    series->append(USCHDOWN2);
    series->append(NONSCHED);
    series->setLabelsVisible(true);
    ratio_select_chart->addSeries(series);


    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    ratio_select_chart->createDefaultAxes();
     ratio_select_chart->setAxisX(axis,series);
     ratio_select_chart->legend()->setVisible(true);

}

void oi_select_ratio_view::bar_hovered(bool status, int index)
{
    if(status){
        QString Label_txt;
        if(Nomal->at(index) > 0 ){
            Label_txt = Label_txt.append(QString("%1 = %2 ").arg(tr("run")).arg(Nomal->at(index)));
        }
        if(PT->at(index) >0 ){
            Label_txt = Label_txt.append(QString("%1 = %2 ").arg(tr("PT")).arg(PT->at(index)));
        }
        if(PM->at(index)>0){
            Label_txt = Label_txt.append(QString("%1 = %2 ").arg(tr("PM")).arg(PM->at(index)));
        }
        if(MT->at(index)>0){
            Label_txt = Label_txt.append(QString("%1 = %2 ").arg(tr("MT")).arg(MT->at(index)));
        }
        if(WAIT->at(index)>0){
            Label_txt = Label_txt.append(QString("%1 = %2 ").arg(tr("WAIT")).arg(WAIT->at(index)));
        }
        if(USCHDOWN4->at(index)>0){
            Label_txt = Label_txt.append(QString("%1 = %2 ").arg(tr("USCHDOWN4")).arg(USCHDOWN4->at(index)));
        }
        if(USCHDOWN1->at(index)>0){
            Label_txt = Label_txt.append(QString("%1 = %2 ").arg(tr("USCHDOWN1")).arg(USCHDOWN1->at(index)));
        }
        if(SCHDOWN2->at(index)>0){
            Label_txt = Label_txt.append(QString("%1 = %2 ").arg(tr("SCHDOWN2")).arg(SCHDOWN2->at(index)));
        }
        if(USCHDOWN2->at(index)>0){
            Label_txt = Label_txt.append(QString("%1 = %2 ").arg(tr("USCHDOWN2")).arg(USCHDOWN2->at(index)));
        }
        if(NONSCHED->at(index)>0){
            Label_txt = Label_txt.append(QString("%1 = %2 ").arg(tr("NONSCHED")).arg(NONSCHED->at(index)));
        }
        ui->explan_txt->setText(Label_txt);
    }else{

    }
}

oi_select_ratio_view::~oi_select_ratio_view()
{
    delete ui;
}

void oi_select_ratio_view::on_zoom_init_btn_clicked()
{
    ratio_select_chart->zoomReset();
}
