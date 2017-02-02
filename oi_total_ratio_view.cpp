#include "oi_total_ratio_view.h"
#include "ui_oi_total_ratio_view.h"


oi_total_ratio_view::oi_total_ratio_view(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::oi_total_ratio_view)
{
    ui->setupUi(this);
    ratio_total_chart = new oi_total_ratio_chart();
    ratio_total_chart->setAnimationOptions(QChart::SeriesAnimations);
    ratio_total_chartview = new oi_total_ratio_chartview(ratio_total_chart);
    ratio_total_chartview->setRenderHint(QPainter::Antialiasing);
    ui->center_layout->addWidget(ratio_total_chartview);

}
oi_total_ratio_view::oi_total_ratio_view(QSqlDatabase db, QWidget *parent):
    QWidget(parent),
    ui(new Ui::oi_total_ratio_view)
{
    ui->setupUi(this);
}

QSqlDatabase oi_total_ratio_view::getDb() const
{
    return db;
}

void oi_total_ratio_view::setDb(const QSqlDatabase &value)
{
    db = value;
}



void oi_total_ratio_view::chart_update()
{
    ratio_total_chart->removeAllSeries();
    if(ratio_total_chart->axisX()!=NULL){
        ratio_total_chart->removeAxis(ratio_total_chart->axisX());
    }


    Nomal = new QBarSet(tr("run"));
    PT = new QBarSet(tr("PT"));
    PM = new QBarSet(tr("PM"));
    MT = new QBarSet(tr("MT"));
//    WAIT = new QBarSet(tr("WAIT"));
    USCHDOWN4 =new QBarSet(tr("USCHDOWN4"));
    USCHDOWN1 =new QBarSet(tr("USCHDOWN1"));
    SCHDOWN2 =new QBarSet(tr("SCHDOWN2"));
    USCHDOWN2 =new QBarSet(tr("USCHDOWN2"));
    NONSCHED =new QBarSet(tr("NONSCHED"));


    connect(Nomal,SIGNAL(hovered(bool,int)),this,SLOT(bar_hovered(bool,int)));
    connect(PT,SIGNAL(hovered(bool,int)),this,SLOT(bar_hovered(bool,int)));
    connect(PM,SIGNAL(hovered(bool,int)),this,SLOT(bar_hovered(bool,int)));
    connect(MT,SIGNAL(hovered(bool,int)),this,SLOT(bar_hovered(bool,int)));
//    connect(WAIT,SIGNAL(hovered(bool,int)),this,SLOT(bar_hovered(bool,int)));
    connect(USCHDOWN4,SIGNAL(hovered(bool,int)),this,SLOT(bar_hovered(bool,int)));
    connect(USCHDOWN1,SIGNAL(hovered(bool,int)),this,SLOT(bar_hovered(bool,int)));
    connect(SCHDOWN2,SIGNAL(hovered(bool,int)),this,SLOT(bar_hovered(bool,int)));
    connect(USCHDOWN2,SIGNAL(hovered(bool,int)),this,SLOT(bar_hovered(bool,int)));
    connect(NONSCHED,SIGNAL(hovered(bool,int)),this,SLOT(bar_hovered(bool,int)));



    QSqlQuery query5(db);
    query5.exec("select * from OI_system_time_2 where rate <> 100 order by rate asc LIMIT 10 ");
    QStringList categories;
    while(query5.next()){
        Nomal->append(ROUNDING(query5.value("rate").toDouble(),2));
        PT->append(ROUNDING(query5.value("PTrate").toDouble(),2));
        PM->append(ROUNDING(query5.value("PMrate").toDouble(),2));
        MT->append(ROUNDING(query5.value("MTrate").toDouble(),2));
//        WAIT->append(ROUNDING(query5.value("Waitrate").toDouble(),2));
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
//    series->append(WAIT);
    series->append(USCHDOWN4);
    series->append(USCHDOWN1);
    series->append(SCHDOWN2);
    series->append(USCHDOWN2);
    series->append(NONSCHED);
    series->setLabelsVisible(true);
    ratio_total_chart->addSeries(series);

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    ratio_total_chart->createDefaultAxes();
     ratio_total_chart->setAxisX(axis,series);
     ratio_total_chart->legend()->setVisible(true);
     ratio_total_chart->axisY()->setRange(0,110);

}

void oi_total_ratio_view::bar_hovered(bool status, int index)
{

    if(status){
        QString toolTip_text;
        QString Label_txt;
        if(Nomal->at(index) > 0 ){
            toolTip_text = toolTip_text.append(QString("%1 = %2 \n").arg(tr("run")).arg(Nomal->at(index)));
            Label_txt = Label_txt.append(QString("%1 = %2 ").arg(tr("run")).arg(Nomal->at(index)));
        }
        if(PT->at(index) >0 ){
            toolTip_text = toolTip_text.append(QString("%1 = %2 \n").arg(tr("PT")).arg(PT->at(index)));
            Label_txt = Label_txt.append(QString("%1 = %2 ").arg(tr("PT")).arg(PT->at(index)));
        }
        if(PM->at(index)>0){
            toolTip_text = toolTip_text.append(QString("%1 = %2 \n").arg(tr("PM")).arg(PM->at(index)));
            Label_txt = Label_txt.append(QString("%1 = %2 ").arg(tr("PM")).arg(PM->at(index)));
        }
        if(MT->at(index)>0){
            toolTip_text = toolTip_text.append(QString("%1 = %2 \n").arg(tr("MT")).arg(MT->at(index)));
            Label_txt = Label_txt.append(QString("%1 = %2 ").arg(tr("MT")).arg(MT->at(index)));
        }
//        if(WAIT->at(index)>0){
//            toolTip_text = toolTip_text.append(QString("%1 = %2 \n").arg(tr("WAIT")).arg(WAIT->at(index)));
//            Label_txt = Label_txt.append(QString("%1 = %2 ").arg(tr("WAIT")).arg(WAIT->at(index)));
//        }
        if(USCHDOWN4->at(index)>0){
            toolTip_text = toolTip_text.append(QString("%1 = %2 \n").arg(tr("USCHDOWN4")).arg(USCHDOWN4->at(index)));
            Label_txt = Label_txt.append(QString("%1 = %2 ").arg(tr("USCHDOWN4")).arg(USCHDOWN4->at(index)));
        }
        if(USCHDOWN1->at(index)>0){
            toolTip_text = toolTip_text.append(QString("%1 = %2 \n").arg(tr("USCHDOWN1")).arg(USCHDOWN1->at(index)));
            Label_txt = Label_txt.append(QString("%1 = %2 ").arg(tr("USCHDOWN1")).arg(USCHDOWN1->at(index)));
        }
        if(SCHDOWN2->at(index)>0){
            toolTip_text = toolTip_text.append(QString("%1 = %2 \n").arg(tr("SCHDOWN2")).arg(SCHDOWN2->at(index)));
            Label_txt = Label_txt.append(QString("%1 = %2 ").arg(tr("SCHDOWN2")).arg(SCHDOWN2->at(index)));
        }
        if(USCHDOWN2->at(index)>0){
            toolTip_text = toolTip_text.append(QString("%1 = %2 \n").arg(tr("USCHDOWN2")).arg(USCHDOWN2->at(index)));
            Label_txt = Label_txt.append(QString("%1 = %2 ").arg(tr("USCHDOWN2")).arg(USCHDOWN2->at(index)));
        }
        if(NONSCHED->at(index)>0){
            toolTip_text = toolTip_text.append(QString("%1 = %2 \n").arg(tr("NONSCHED")).arg(NONSCHED->at(index)));
            Label_txt = Label_txt.append(QString("%1 = %2 ").arg(tr("NONSCHED")).arg(NONSCHED->at(index)));
        }
        QToolTip::showText(ratio_total_chartview->getCurrent_point(),toolTip_text,ratio_total_chartview,QRect(0,0,120,120),70000);
        ui->explan_txt->setText(Label_txt);
    }else{

    }

}



oi_total_ratio_view::~oi_total_ratio_view()
{
    delete ui;
}

void oi_total_ratio_view::on_zoom_init_btn_clicked()
{
    ratio_total_chart->zoomReset();
}
