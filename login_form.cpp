#include "login_form.h"
#include "ui_login_form.h"

login_form::login_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login_form)
{
    ui->setupUi(this);
    loginflag =false;
    connect(&menager,SIGNAL(finished(QNetworkReply*)),this,SLOT(read_finish(QNetworkReply*)));

}
login_form::login_form(QString event_name, QString machine_code, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login_form)
{
    ui->setupUi(this);
    loginflag =false;
    this->event_name= event_name;
    connect(&menager,SIGNAL(finished(QNetworkReply*)),this,SLOT(read_finish(QNetworkReply*)));
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
login_form::login_form(QString event_name, QString machine_code,QString machine_name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login_form)
{
    ui->setupUi(this);
    loginflag =false;
    this->event_name= event_name;
    connect(&menager,SIGNAL(finished(QNetworkReply*)),this,SLOT(read_finish(QNetworkReply*)));
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

QString login_form::getUser_name() const
{
    return user_name;
}

void login_form::setUser_name(const QString &value)
{
    user_name = value;
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

void login_form::read_finish(QNetworkReply *reply)
{
    QByteArray srcdata = reply->readAll();
    QString strdata(srcdata);
    QString fromurl = reply->url().toString();
    if(fromurl == "http://gw.wisol.co.kr/ekp/login.do"){
        QStringList temp_list = strdata.split(",");
        QString temp_name = temp_list.at(1);
        temp_list = temp_name.split(":");
        temp_name = temp_list.at(1);
        temp_name = temp_name.replace("\"","");

        user_name = temp_name;
        QString requsturl = QString("http://gw.wisol.co.kr/ekp/login.do?"
                                    "cmd=epLogin&pop3=N&saveid=N&securchk=N&"
                                    "id=%1&password=%2&lang=ko&mode=plain&"
                                    "cmpId=C100120723&slct_dept_id=&"
                                    "serverName=gw.wisol.co.kr/ekp&securityKey=").arg(ui->ID_LE->text()).arg(ui->PW_LE->text());
        QUrl longin_url(requsturl);
        QNetworkRequest requst(longin_url);
        menager.get(requst);
    }else if(fromurl.indexOf("cmd=epLogin&pop3=N&saveid=N&securchk=N")>=0){
        if(strdata.indexOf("LOGIN_SUCCESS")>=0){
            qDebug()<<"LOGIN_SUCCESS";
            _ns1__OIWebEquipmentStatusResponse response;
            soap_event.OIWebEquipmentStatus(&data,response);
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
            QSqlQuery query(my_mesdb);
            QString query_txt = QString("INSERT INTO `OI_system_history` "
                                        "(`event_datetime`, `name`, "
                                        "`machine_name`, `event_type`) "
                                        "VALUES ("
                                        "'%1', '%2', '%3', '%4');")
                                        .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                                        .arg(user_name).arg(machine_name).arg(event_name);
            query.exec(query_txt);

            QMessageBox msg;
            msg.setText(tr("ok"));
            msg.addButton(QMessageBox::Ok);
            msg.exec();
        }else {
            QMessageBox msg;
            msg.setText(tr("loginfail"));
            msg.addButton(QMessageBox::Ok);
            msg.exec();
        }
        reply->deleteLater();
        close();
    }else {
        reply->deleteLater();
        close();
    }
}

void login_form::on_login_btn_clicked()
{
    QUrl checkurl("http://gw.wisol.co.kr/ekp/login.do");
    QNetworkRequest requst(checkurl);
    requst.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QByteArray postData;
    postData.append("cmd=additionalCheck&");
    postData.append(QString("id=%1&").arg(ui->ID_LE->text()));
    postData.append("password=&");
    postData.append("mode=plain");
    menager.post(requst,postData);
}

void login_form::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Enter){
        on_login_btn_clicked();
    }
}

void login_form::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
}
