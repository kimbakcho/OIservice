#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <machine_statue_data.h>
#include <QDateTime>

#include <th_monitering.h>
#include <login_form.h>
#include <QSqlQueryModel>

#define DBID "EIS"
#define DBPW "wisolfab!"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QSqlDatabase my_mesdb;
    QString current_machine_code;
    QString current_machine_name;
    QSqlQueryModel  history_model;
    ~MainWindow();

    QString getCurrent_machine_name() const;
    void setCurrent_machine_name(const QString &value);

private slots:
    void deposition_slot(machine_statue_data data);
    void light_slot(machine_statue_data data);
    void eatching_slot(machine_statue_data data);
    void probe_slot(machine_statue_data data);
    void probe1_slot(machine_statue_data data);

    void on_RUN_btn_clicked();

    void on_deposition_listview_clicked(const QModelIndex &index);

    void on_light_listview_clicked(const QModelIndex &index);

    void on_eatching_listview_clicked(const QModelIndex &index);

    void on_probe_listview_clicked(const QModelIndex &index);

    void on_probe1_listview_clicked(const QModelIndex &index);

    void on_ENGR1_btn_clicked();

    void on_SCHDOWN1_btn_clicked();

    void on_USCHDOWN3_btn_clicked();

    void on_WAIT_btn_clicked();

    void on_search_btn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
