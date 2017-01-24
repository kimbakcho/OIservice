#include "login_form.h"
#include "ui_login_form.h"
#include <mainwindow.h>
extern MainWindow *m_window;
login_form::login_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login_form)
{
    ui->setupUi(this);
    loginflag =false;

    crypt.setKey((Q_UINT64_C(0x20170123)));

}
login_form::login_form(QString event_name, QString machine_code, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login_form)
{
    ui->setupUi(this);
    loginflag =false;
    this->event_name= event_name;
    data.equipmentId = &equip;
    data.siteId = &siteid;
    data.eventId = &eventid;
    data.userId = &userid;
    data.languageId = &lang;
    data.resultMessage = &resultmessage;
    siteid= "WOSF";
    lang= "en-US";
    userid= "PROBE";
    resultmessage= "";
    equip= machine_code.toStdString();
    eventid = event_name.toStdString();

//    QString mydb_name = QString("MY_MESDB_OI_%1").arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"));
//    if(!my_mesdb.contains(mydb_name)){
//        my_mesdb = QSqlDatabase::addDatabase("QMYSQL",mydb_name);
//        my_mesdb.setHostName("fabsv.wisol.co.kr");
//        my_mesdb.setPort(3306);
//        my_mesdb.setUserName(DBID);
//        my_mesdb.setPassword(DBPW);
//        my_mesdb.setDatabaseName("FAB");
//        if(!my_mesdb.open()){
//            qDebug()<<"fasle";
//            qDebug()<<my_mesdb.lastError().text();
//        }else {
//            qDebug()<<"open";
//        }
//    }else {
//        my_mesdb = QSqlDatabase::database(mydb_name);
//    }

}
login_form::login_form(QString event_name, QString machine_code,QString machine_name,QString process, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login_form)
{
    ui->setupUi(this);
    loginflag =false;
    this->event_name= event_name;

    data.equipmentId = &equip;
    data.siteId = &siteid;
    data.eventId = &eventid;
    data.userId = &userid;
    data.languageId = &lang;
    data.resultMessage = &resultmessage;
    siteid= "WOSF";
    lang= "en-US";
    userid= "PROBE";
    resultmessage= "";
    equip= machine_code.toStdString();
    eventid = event_name.toStdString();
    this->machine_name = machine_name;
    this->process = process;
    this->machine_code = machine_code;

//    QString mydb_name = QString("MY_MESDB_OI_%1").arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"));
//    if(!my_mesdb.contains(mydb_name)){
//        my_mesdb = QSqlDatabase::addDatabase("QMYSQL",mydb_name);
//        my_mesdb.setHostName("fabsv.wisol.co.kr");
//        my_mesdb.setPort(3306);
//        my_mesdb.setUserName(DBID);
//        my_mesdb.setPassword(DBPW);
//        my_mesdb.setDatabaseName("FAB");
//        if(!my_mesdb.open()){
//            qDebug()<<"fasle";
//            qDebug()<<my_mesdb.lastError().text();
//        }else {
//            qDebug()<<"open";
//        }
//    }else {
//        my_mesdb = QSqlDatabase::database(mydb_name);
//    }

}

QString login_form::getUser_name() const
{
    return user_name;
}

void login_form::setUser_name(const QString &value)
{
    user_name = value;
}

QString login_form::from_sec_to_timestr(int secs)
{
    int hour = secs/3600;
    int min = (secs%3600)/60;
    int sec = (secs%3600)%60;
    QString reslut = QString("%1:%2:%3").arg(hour).arg(min).arg(sec);
    return reslut;
}

QString login_form::getMachine_name() const
{
    return machine_name;
}

void login_form::setMachine_name(const QString &value)
{
    machine_name = value;
}


QString login_form::getLoginname() const
{
    return loginname;
}

void login_form::setLoginname(const QString &value)
{
    loginname = value;
}

login_form::~login_form()
{
    delete ui;
}

void login_form::on_login_btn_clicked()
{
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
            QMessageBox msg;
            msg.setText(tr("db join false again try"));
            msg.addButton(QMessageBox::Ok);
            msg.exec();
            return ;
        }else {
            qDebug()<<"open";
        }
    }else {
        my_mesdb = QSqlDatabase::database(mydb_name);
    }

          QSqlQuery query(my_mesdb);
          user_name = ui->ID_LE->text();

          if(event_name=="RUN"){
              event_name = event_name.replace("RUN",tr("RUN"));
          }else if(event_name=="ENGR1"){
              event_name = event_name.replace("ENGR1",tr("ENGR1"));
          }else if(event_name=="SCHDOWN1"){
              event_name = event_name.replace("SCHDOWN1",tr("SCHDOWN1"));
          }else if(event_name=="USCHDOWN3"){
              event_name = event_name.replace("USCHDOWN3",tr("USCHDOWN3"));
          }else if(event_name=="WAIT"){
              event_name = event_name.replace("WAIT",tr("WAIT"));
          }else {

          }
          QDateTime current_datetime = QDateTime::currentDateTime();
          QString currenttime_str =current_datetime.toString("yyyy-MM-dd hh:mm:ss");
          QSqlQuery query1(my_mesdb);
          QString query_txt = QString("INSERT INTO `OI_system_history` "
                                      "(`event_datetime`, `name`, "
                                      "`machine_name`, `event_type`,`process`) "
                                      "VALUES ("
                                      "'%1', '%2', '%3', '%4' , '%5');")
                                      .arg(currenttime_str)
                                      .arg(user_name).arg(machine_name).arg(event_name).arg(process);
          query1.exec(query_txt);
          if(event_name == tr("RUN")){
              query_txt = QString("select * from OI_system_time where run_time is NULL "
                                  "AND machine_code = '%1' "
                                  "AND machine_name = '%2' order by stop_time desc LIMIT 1").arg(machine_code).arg(machine_name);
              query1.exec(query_txt);
              if(query1.next()){
                  QDateTime stop_time = query1.value("stop_time").toDateTime();
                  qint64 secs = stop_time.secsTo(current_datetime);
                  QString time_str = from_sec_to_timestr(secs);
                  query_txt = QString("Update `OI_system_time` SET "
                                      "run_time = '%1',run_name='%2',stop_time_calc='%3' "
                                      "Where stop_time = '%5' AND machine_code ='%6'")
                                      .arg(currenttime_str).arg(user_name).arg(time_str)
                                      .arg(query1.value("stop_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                                      .arg(query1.value("machine_code").toString());
                  query1.exec(query_txt);
                  qDebug()<<query1.lastQuery();
              }else {

              }
          }else {
              query_txt = QString("select * from OI_system_time where run_time is NULL "
                                  "AND machine_code = '%1' "
                                  "AND machine_name = '%2' order by run_time desc LIMIT 1")
                      .arg(machine_code).arg(machine_name);
              query1.exec(query_txt);
              if(!query1.next()){
                  query_txt = QString("INSERT INTO `OI_system_time` "
                                      "(`process`,`machine_name`, `machine_code`, `stop_time`, `stop_name` , `stop_data`) "
                                      "VALUES ('%1', '%2', '%3', '%4','%5','%6');")
                                      .arg(process).arg(machine_name).arg(machine_code).arg(currenttime_str).arg(user_name).arg(event_name);
                  query1.exec(query_txt);
              }else {
                  QDateTime stop_time = query1.value("stop_time").toDateTime();
                  qint64 secs = stop_time.secsTo(current_datetime);
                  QString time_str = from_sec_to_timestr(secs);
                  query_txt = QString("Update `OI_system_time` SET "
                                      "run_time = '%1',run_name='%2',stop_time_calc='%3' "
                                      "Where stop_time = '%5' AND machine_code ='%6'")
                                      .arg(currenttime_str).arg(user_name).arg(time_str)
                                      .arg(query1.value("stop_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                                      .arg(query1.value("machine_code").toString());
                  query1.exec(query_txt);
                  query_txt = QString("INSERT INTO `OI_system_time` "
                                      "(`process`,`machine_name`, `machine_code`, `stop_time`, `stop_name` , `stop_data`) "
                                      "VALUES ('%1', '%2', '%3', '%4','%5','%6');")
                                      .arg(process).arg(machine_name).arg(machine_code).arg(currenttime_str).arg(user_name).arg(event_name);
                  query1.exec(query_txt);

              }
          }
          _ns1__OIWebEquipmentStatusResponse response;
          soap_event.OIWebEquipmentStatus(&data,response);
          QMessageBox msg;
          msg.setText(tr("ok"));
          msg.addButton(QMessageBox::Ok);
          msg.exec();
          close();
          m_window->on_search_btn_clicked_connection();
}

void login_form::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Enter){
        on_login_btn_clicked();
        ui->login_btn->setEnabled(false);
    }
}

void login_form::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
}
