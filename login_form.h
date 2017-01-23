#ifndef LOGIN_FORM_H
#define LOGIN_FORM_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QKeyEvent>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <oistystemsoap/oisystemOIWebServiceSoapProxy.h>
#include <QMessageBox>
#include <QElapsedTimer>
#include <join_popup.h>
#include <simplecrypt/simplecrypt.h>
#define DBID "EIS"
#define DBPW "wisolfab!"

namespace Ui {
class login_form;
}

class login_form : public QWidget
{
    Q_OBJECT

public:
    explicit login_form(QWidget *parent = 0);
    login_form(QString event_name,QString machine_code,QWidget *parent = 0);
    login_form(QString event_name, QString machine_code, QString machine_name, QString process, QWidget *parent = 0);
    QNetworkAccessManager menager;
    QString loginname;
    QString event_name;
    QString machine_name;
    QString machine_code;
    QString process;
    bool loginflag;
    OIWebServiceSoapProxy soap_event;
    _ns1__OIWebEquipmentStatus data;
    std::string siteid;
    std::string equip;
    std::string eventid;
    std::string lang;
    std::string userid;
    std::string resultmessage;
    QSqlDatabase my_mesdb;
    QString user_name;
    SimpleCrypt crypt;
    ~login_form();

    QString getLoginname() const;
    void setLoginname(const QString &value);


    QString getMachine_name() const;
    void setMachine_name(const QString &value);

    QString getUser_name() const;
    void setUser_name(const QString &value);
    QString from_sec_to_timestr(int secs);

private slots:

    void on_login_btn_clicked();

    void on_join_btn_clicked();

private:
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);
    Ui::login_form *ui;
};

#endif // LOGIN_FORM_H
