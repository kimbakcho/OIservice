#include "rest_time_widget.h"
#include "ui_rest_time_widget.h"

rest_time_widget::rest_time_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rest_time_widget)
{
    ui->setupUi(this);
    QString mydb_name = QString("MY_MESDB_OI_%1").arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"));

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
    rest_time_model = new QSqlTableModel(this,my_mesdb);
    rest_time_model->setTable("OI_system_rest_time_repeat_table");
     ui->daily_rest_time_table->setModel(rest_time_model);
     rest_time_model->select();
}

rest_time_widget::~rest_time_widget()
{
    delete ui;
}

void rest_time_widget::closeEvent(QCloseEvent *event)
{
    rest_time_model->deleteLater();
    this->deleteLater();
}

void rest_time_widget::on_add_btn_clicked()
{
    rest_time_model->insertRow(rest_time_model->rowCount());
}

void rest_time_widget::on_del_btn_clicked()
{
    rest_time_model->removeRow(ui->daily_rest_time_table->selectionModel()->currentIndex().row());
}
