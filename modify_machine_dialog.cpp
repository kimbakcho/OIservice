#include "modify_machine_dialog.h"
#include "ui_modify_machine_dialog.h"

modify_machine_dialog::modify_machine_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify_machine_dialog)
{
    ui->setupUi(this);
}

modify_machine_dialog::modify_machine_dialog(QString process, QString machine_name, QString machine_code, QWidget *parent):
    QDialog(parent),
    ui(new Ui::modify_machine_dialog)
{
    ui->setupUi(this);
    this->process = process;
    this->machine_name = machine_name;
    this->machine_code = machine_code;
    ui->CB_process->setCurrentText(process);
    ui->LE_machine_name->setText(machine_name);
    ui->LE_machine_code->setText(machine_code);

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
    QSqlQuery query(my_mesdb);
    QString query_txt = QString("select * from OI_system_machine_table where "
                                "Main_process = '%1' AND machine_name = '%2' "
                                "AND machine_code = '%3'").arg(process,machine_name,machine_code);
    query.exec(query_txt);
    if(query.next()){
        ui->spinBox->setValue(query.value("number").toInt());
    }


}

modify_machine_dialog::~modify_machine_dialog()
{
    delete ui;
}

void modify_machine_dialog::on_buttonBox_accepted()
{
    QSqlQuery query(my_mesdb);
    QString query_txt = QString("UPDATE `OI_system_machine_table` "
                                "SET `machine_name`='%1' "
                                ", `Main_process`='%2' "
                                ", `machine_code`='%3' "
                                ", `number`='%4' "
                                "WHERE `machine_name`='%5' "
                                "AND `machine_code`='%6' "
                                "AND `Main_process`='%7';")
                                .arg(ui->LE_machine_name->text())
                                .arg(ui->CB_process->currentText())
                                .arg(ui->LE_machine_code->text())
                                .arg(ui->spinBox->value())
                                .arg(machine_name)
                                .arg(machine_code)
                                .arg(process);
    query.exec(query_txt);
    return;
}
