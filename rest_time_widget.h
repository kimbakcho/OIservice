#ifndef REST_TIME_WIDGET_H
#define REST_TIME_WIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlTableModel>
#include <QDateTime>
#define DBID "EIS"
#define DBPW "wisolfab!"
namespace Ui {
class rest_time_widget;
}

class rest_time_widget : public QWidget
{
    Q_OBJECT

public:
    explicit rest_time_widget(QWidget *parent = 0);
    QSqlDatabase my_mesdb;
    QSqlTableModel *rest_time_model;

    ~rest_time_widget();

private slots:
    void on_add_btn_clicked();

    void on_del_btn_clicked();

private:
    void closeEvent(QCloseEvent *event);
    Ui::rest_time_widget *ui;
};

#endif // REST_TIME_WIDGET_H
