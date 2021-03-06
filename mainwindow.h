#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <machine_statue_data.h>
#include <QDateTime>
#include <rest_time_widget.h>
#include <th_monitering.h>
#include <b_table_widget2.h>

#include <login_form.h>
#include <QSqlQueryModel>
#include <b_label.h>
#include <manager_login.h>
#include <add_machine_dialog.h>
#include <modify_machine_dialog.h>


#define Onedaymin 1180
#define DBID "EIS"
#define DBPW "wisolfab!"

#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QSqlDatabase my_mesdb;
    QSqlDatabase light_db;
    QString current_machine_code;
    QString current_machine_name;
    QString current_process;
    QString current_process_manager;
    QSqlQueryModel  history_model;
    Th_monitering *depostion_thread;
    Th_monitering *light_thread;
    Th_monitering *eatching_thread;
    Th_monitering *probe_thread;
    Th_monitering *probe1_thread;
//    QVector<OI_data> OIdata_list;
    QSqlQueryModel detail_table_model;
    QSqlQueryModel total_table_model;

    QSqlQueryModel rest_table_model;
    QSqlQueryModel depostion_deatil_model;
    QSqlQueryModel light_deatil_model;
    QSqlQueryModel eatch_deatil_model;
    QSqlQueryModel probe_deatil_model;



    ~MainWindow();

    QString getCurrent_machine_name() const;

    void setCurrent_machine_name(const QString &value);

    void on_search_btn_clicked_connection();

    void on_calc(QString select_machine);

    QString from_sec_to_timestr(int secs);

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

    void on_processbox_currentIndexChanged(const QString &arg1);


    void on_add_machine_clicked();

    void on_modify_machine_clicked();

    void on_delete_macihne_clicked();

    void on_managermode_btn_clicked();

    void on_calc_btn_clicked();

    void on_show_detail_total_clicked();

    void on_total_table_clicked(const QModelIndex &index);

    void on_research_start_date_dateTimeChanged(const QDateTime &dateTime);

    void on_research_end_date_dateTimeChanged(const QDateTime &dateTime);

    void on_detail_table_clicked(const QModelIndex &index);

    void on_resttime_setup_clicked();

    void chart_search();

    void on_detail_chart_seartch_btn_clicked();

    void on_CB_data_list_type_currentIndexChanged(const QString &arg1);

    void on_CB_detaildatalist_currentIndexChanged(const QString &arg1);


    void on_deposition_font_size_textEdited(const QString &arg1);

    void on_deposition_rowsize_textEdited(const QString &arg1);

    void on_light_rowsize_textEdited(const QString &arg1);

    void on_light_fontsize_textEdited(const QString &arg1);

    void on_eatching_rowsize_textEdited(const QString &arg1);

    void on_eatching_fontsize_textEdited(const QString &arg1);

    void on_probe_rowsize_textEdited(const QString &arg1);

    void on_probe_fontsize_textEdited(const QString &arg1);

    void on_probe1_rowsize_textEdited(const QString &arg1);

    void on_probe1_fontsize_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
