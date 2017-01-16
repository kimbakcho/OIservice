#include "add_machine_dialog.h"
#include "ui_add_machine_dialog.h"

add_machine_dialog::add_machine_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_machine_dialog)
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
}

add_machine_dialog::~add_machine_dialog()
{
    delete ui;
}

void add_machine_dialog::on_buttonBox_accepted()
{
    QSqlQuery query(my_mesdb);
    QString query_txt = QString("INSERT INTO `OI_system_machine_table` "
                                "(`number`, `machine_name`, `machine_code`, `Main_process`) "
                                "VALUES ('%1', '%2', '%3', '%4');")
                                .arg(ui->spinBox->value()).arg(ui->LE_machine_name->text())
                                .arg(ui->LE_machine_code->text()).arg(ui->CB_process->currentText());

    query.exec(query_txt);
    qDebug()<<query.lastQuery();
    return ;
}
