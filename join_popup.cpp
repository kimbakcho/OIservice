#include "join_popup.h"
#include "ui_join_popup.h"
#define DBID "EIS"
#define DBPW "wisolfab!"
join_popup::join_popup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::join_popup)
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
    crypt.setKey((Q_UINT64_C(0x20170123)));
}

join_popup::~join_popup()
{
    delete ui;
}

void join_popup::on_buttonBox_accepted()
{
    QSqlQuery query(my_mesdb);
    query.exec(QString("select * from OI_system_login_info where number = '%1'").arg(ui->LE_number->text()));
    if(query.next()){
        qDebug()<<"join fail because have number";
        QMessageBox msg;
        msg.setText(tr("have number"));
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        open();
    }else {
        query.exec(QString("insert into OI_system_login_info (number,name,password) values ('%1','%2','%3')")
                   .arg(ui->LE_number->text()).arg(ui->LE_name->text()).arg(crypt.encryptToString(ui->LE_password->text()))
                   );
        QMessageBox msg;
        msg.setText(tr("join completet"));
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        accept();
    }
}
