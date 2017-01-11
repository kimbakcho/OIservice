#ifndef OPERATING_RATIO_ACTION_H
#define OPERATING_RATIO_ACTION_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSettings>
#include <QDateTime>
#include <oistystemsoap/oisystemOIWebServiceSoapProxy.h>
#include <QMessageBox>
#include <login_form.h>

#define DBID "EIS"
#define DBPW "wisolfab!"
namespace Ui {
class operating_ratio_action;
}

class operating_ratio_action : public QWidget
{
    Q_OBJECT

public:
    explicit operating_ratio_action(QWidget *parent = 0);
    QSqlDatabase my_mesdb;
    ~operating_ratio_action();

private slots:

    void on_process_cb_currentIndexChanged(const QString &arg1);

    void on_machinename_cb_currentIndexChanged(const QString &arg1);

    void on_RUN_btn_clicked();

    void on_ENGR1_btn_clicked();

    void on_SCHDOWN1_btn_clicked();

    void on_USCHDOWN3_btn_clicked();

    void on_WAIT_btn_clicked();

private:
    Ui::operating_ratio_action *ui;
};

#endif // OPERATING_RATIO_ACTION_H
