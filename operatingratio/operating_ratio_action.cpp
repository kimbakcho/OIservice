#include "operating_ratio_action.h"
#include "ui_operating_ratio_action.h"

operating_ratio_action::operating_ratio_action(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::operating_ratio_action)
{
    ui->setupUi(this);
    QString mydb_name = QString("MY_MESDB_OI_%1").arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmm"));
    if(!my_mesdb.contains(mydb_name)){
        my_mesdb = QSqlDatabase::addDatabase("QMYSQL",mydb_name);
        my_mesdb.setHostName("fabsv.wisol.co.kr");
        my_mesdb.setPort(3306);
        my_mesdb.setUserName(DBID);
        my_mesdb.setPassword(DBPW);
        my_mesdb.setDatabaseName("FAB");
        if(!my_mesdb.open()){
            qDebug()<<"fasle";
            qDebug()<<my_mesdb.lastError().text();
        }else {
            qDebug()<<"open";
        }
    }else {
        my_mesdb = QSqlDatabase::database(mydb_name);
    }
}

operating_ratio_action::~operating_ratio_action()
{
    delete ui;
}


void operating_ratio_action::on_process_cb_currentIndexChanged(const QString &arg1)
{
    QString deposition = tr("deposition");
    QString light = tr("light");
    QString eatching = tr("eatching");
    QString all_probe = tr("ALL probe");
    QSqlQuery query(my_mesdb);
    ui->machinename_cb->clear();
    if(arg1 == deposition){
        query.exec(QString("select * from OI_system_machine_table where Main_process = '%1' order by number asc").arg(deposition));
        while(query.next()){
            ui->machinename_cb->addItem(query.value("machine_name").toString(),QVariant(query.value("machine_code").toString()));
        }
    }else if(arg1 == light){
        query.exec(QString("select * from OI_system_machine_table where Main_process = '%1' order by number asc").arg(light));
        while(query.next()){
            ui->machinename_cb->addItem(query.value("machine_name").toString(),QVariant(query.value("machine_code").toString()));
        }
    }else if(arg1 == eatching){
        query.exec(QString("select * from OI_system_machine_table where Main_process = '%1' order by number asc").arg(eatching));
        while(query.next()){
            ui->machinename_cb->addItem(query.value("machine_name").toString(),QVariant(query.value("machine_code").toString()));
        }
    }else if(arg1 ==all_probe){
        query.exec(QString("select * from OI_system_machine_table where Main_process = '%1' order by number asc").arg(all_probe));
        while(query.next()){
            ui->machinename_cb->addItem(query.value("machine_name").toString(),QVariant(query.value("machine_code").toString()));
        }
    }
}

void operating_ratio_action::on_machinename_cb_currentIndexChanged(const QString &arg1)
{
    ui->machinename_LA->setText(arg1);
}

void operating_ratio_action::on_RUN_btn_clicked()
{
      login_form *widget = new login_form("RUN", ui->machinename_cb->currentData().toString());
      widget->show();
}

void operating_ratio_action::on_ENGR1_btn_clicked()
{
    login_form *widget = new login_form("ENGR1", ui->machinename_cb->currentData().toString());
    widget->show();
}

void operating_ratio_action::on_SCHDOWN1_btn_clicked()
{
    login_form *widget = new login_form("SCHDOWN1", ui->machinename_cb->currentData().toString());
    widget->show();
}

void operating_ratio_action::on_USCHDOWN3_btn_clicked()
{
    login_form *widget = new login_form("USCHDOWN3", ui->machinename_cb->currentData().toString());
    widget->show();
}

void operating_ratio_action::on_WAIT_btn_clicked()
{
    login_form *widget = new login_form("WAIT", ui->machinename_cb->currentData().toString());
    widget->show();
}
