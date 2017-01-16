#include "mainwindow.h"
#include "ui_mainwindow.h"
extern MainWindow *m_window;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_window = this;
    ui->add_machine->setVisible(false);

    ui->modify_machine->setVisible(false);

    ui->delete_macihne->setVisible(false);

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
    ui->deposition_listview->horizontalHeader()->hideSection(2);
    ui->light_listview->horizontalHeader()->hideSection(2);
    ui->eatching_listview->horizontalHeader()->hideSection(2);
    ui->probe_listview->horizontalHeader()->hideSection(2);
    ui->probe1_listview->horizontalHeader()->hideSection(2);


    QString deposition = tr("deposition");
    QString light = tr("light");
    QString eatching = tr("eatching");
    QString all_probe = tr("ALL probe");
    QString probe1 = tr("probe1");
    QSqlQuery query(my_mesdb);
    query.exec(QString("select * from OI_system_machine_table where Main_process = '%1' order by number asc").arg(deposition));
    QVector<machine_statue_data> depostiondata_list;
    while(query.next()){
        machine_statue_data tempdata;
        tempdata.setMachine_name(query.value("machine_name").toString());
        tempdata.setMachine_code(query.value("machine_code").toString());
        int count = ui->deposition_listview->rowCount();
        ui->deposition_listview->insertRow(count);
        ui->deposition_listview->setCellWidget(count,0,new B_Label(tempdata.getMachine_name(),tempdata.getMachine_name(),tempdata.getMachine_code(),deposition));
        ui->deposition_listview->setCellWidget(count,1,new B_Label("",tempdata.getMachine_name(),tempdata.getMachine_code(),deposition));
        ui->deposition_listview->setCellWidget(count,2,new QLabel(tempdata.getMachine_code()));

        depostiondata_list.append(tempdata);
    }
    depostion_thread = new Th_monitering(depostiondata_list);
    connect(depostion_thread,SIGNAL(send_listdata(machine_statue_data)),this,SLOT(deposition_slot(machine_statue_data)));
    depostion_thread->start();
    query.exec(QString("select * from OI_system_machine_table where Main_process = '%1' order by number asc").arg(light));
    QVector<machine_statue_data> lightdata_list;
    while(query.next()){
        machine_statue_data tempdata;
        tempdata.setMachine_name(query.value("machine_name").toString());
        tempdata.setMachine_code(query.value("machine_code").toString());
        int count = ui->light_listview->rowCount();
        ui->light_listview->insertRow(count);
        ui->light_listview->setCellWidget(count,0,new B_Label(tempdata.getMachine_name(),tempdata.getMachine_name(),tempdata.getMachine_code(),light));
        ui->light_listview->setCellWidget(count,1,new B_Label("",tempdata.getMachine_name(),tempdata.getMachine_code(),light));
        ui->light_listview->setCellWidget(count,2,new QLabel(tempdata.getMachine_code()));
        lightdata_list.append(tempdata);
    }
    light_thread = new Th_monitering(lightdata_list);
    connect(light_thread,SIGNAL(send_listdata(machine_statue_data)),this,SLOT(light_slot(machine_statue_data)));
    light_thread->start();
    query.exec(QString("select * from OI_system_machine_table where Main_process = '%1' order by number asc").arg(eatching));
    QVector<machine_statue_data> eatchingdata_list;
    while(query.next()){
        machine_statue_data tempdata;
        tempdata.setMachine_name(query.value("machine_name").toString());
        tempdata.setMachine_code(query.value("machine_code").toString());
        int count = ui->eatching_listview->rowCount();
        ui->eatching_listview->insertRow(count);
        ui->eatching_listview->setCellWidget(count,0,new B_Label(tempdata.getMachine_name(),tempdata.getMachine_name(),tempdata.getMachine_code(),eatching));
        ui->eatching_listview->setCellWidget(count,1,new B_Label("",tempdata.getMachine_name(),tempdata.getMachine_code(),eatching));
        ui->eatching_listview->setCellWidget(count,2,new QLabel(tempdata.getMachine_code()));
        eatchingdata_list.append(tempdata);
    }
    eatching_thread = new Th_monitering(eatchingdata_list);
    connect(eatching_thread,SIGNAL(send_listdata(machine_statue_data)),this,SLOT(eatching_slot(machine_statue_data)));
    eatching_thread->start();
    query.exec(QString("select * from OI_system_machine_table where Main_process = '%1' order by number asc").arg(all_probe));
    QVector<machine_statue_data> probedata_list;
    while(query.next()){
        machine_statue_data tempdata;
        tempdata.setMachine_name(query.value("machine_name").toString());
        tempdata.setMachine_code(query.value("machine_code").toString());
        int count = ui->probe_listview->rowCount();
        ui->probe_listview->insertRow(count);
        ui->probe_listview->setCellWidget(count,0,new B_Label(tempdata.getMachine_name(),tempdata.getMachine_name(),tempdata.getMachine_code(),all_probe));
        ui->probe_listview->setCellWidget(count,1,new B_Label("",tempdata.getMachine_name(),tempdata.getMachine_code(),all_probe));
        ui->probe_listview->setCellWidget(count,2,new QLabel(tempdata.getMachine_code()));

        probedata_list.append(tempdata);
    }
    probe_thread = new Th_monitering(probedata_list);
    connect(probe_thread,SIGNAL(send_listdata(machine_statue_data)),this,SLOT(probe_slot(machine_statue_data)));
    probe_thread->start();

    query.exec(QString("select * from OI_system_machine_table where Main_process = '%1' order by number asc").arg(probe1));
    QVector<machine_statue_data> probe1data_list;
    while(query.next()){
        machine_statue_data tempdata;
        tempdata.setMachine_name(query.value("machine_name").toString());
        tempdata.setMachine_code(query.value("machine_code").toString());
        int count = ui->probe1_listview->rowCount();
        ui->probe1_listview->insertRow(count);
        ui->probe1_listview->setCellWidget(count,0,new B_Label(tempdata.getMachine_name(),tempdata.getMachine_name(),tempdata.getMachine_code(),all_probe));
        ui->probe1_listview->setCellWidget(count,1,new B_Label("",tempdata.getMachine_name(),tempdata.getMachine_code(),all_probe));
        ui->probe1_listview->setCellWidget(count,2,new QLabel(tempdata.getMachine_code()));
        probe1data_list.append(tempdata);
    }
    probe1_thread = new Th_monitering(probe1data_list);
    connect(probe1_thread,SIGNAL(send_listdata(machine_statue_data)),this,SLOT(probe1_slot(machine_statue_data)));
    probe1_thread->start();
    ui->start_time->setDate(QDate::currentDate());
    ui->start_time->setTime(QTime(8,0,0));
    ui->end_time->setDate(QDate::currentDate());
    ui->end_time->setTime(QTime::currentTime());
    QSqlQuery query1(my_mesdb);
    query1.exec(QString("select event_datetime,name,machine_name,event_type from OI_system_history where event_datetime BETWEEN  '%1' AND '%2' order by event_datetime desc;")
                .arg(ui->start_time->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(ui->end_time->dateTime().toString("yyyy-MM-dd hh:mm:ss")));

    history_model.setQuery(query1);
    ui->history_table->setModel(&history_model);
    history_model.submit();

    ui->history_table->horizontalHeader()->resizeSection(0,150);
    ui->history_table->horizontalHeader()->resizeSection(1,80);
    history_model.setHeaderData(0,Qt::Horizontal,tr("time"));
    history_model.setHeaderData(1,Qt::Horizontal,tr("name"));
    history_model.setHeaderData(2,Qt::Horizontal,tr("machine_name"));
    history_model.setHeaderData(3,Qt::Horizontal,tr("statue"));

    query1.exec(QString("select * from OI_system_machine_table order by machine_name asc"));
    ui->machine_name_box->addItem(tr("ALL"));
    while(query1.next()){
        ui->machine_name_box->addItem(query1.value("machine_name").toString(),QVariant(query1.value("machine_code").toString()));
    }
    ui->research_start_date->setDate(QDate::currentDate().addDays(-1));
    ui->research_end_date->setDate(QDate::currentDate().addDays(-1));


}

QString MainWindow::getCurrent_machine_name() const
{
    return current_machine_name;
}


void MainWindow::setCurrent_machine_name(const QString &value)
{
    current_machine_name = value;
}

void MainWindow::on_search_btn_clicked_connection()
{
    ui->end_time->setDate(QDate::currentDate());
    ui->end_time->setTime(QTime::currentTime().addSecs(20));
    on_search_btn_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::deposition_slot(machine_statue_data data)
{
    for(int i=0;i<ui->deposition_listview->rowCount();i++){
        QLabel *machine_name = (QLabel *)ui->deposition_listview->cellWidget(i,0);
        QLabel *machine_event = (QLabel *)ui->deposition_listview->cellWidget(i,1);
        QLabel *machine_code = (QLabel *)ui->deposition_listview->cellWidget(i,2);
        if(machine_code->text() == data.getMachine_code()){
            machine_event->setText(data.getCurrent_event());
            machine_event->setStyleSheet(QString("background-color: %1").arg(data.getColor().name()));
            break;
        }
    }
}

void MainWindow::light_slot(machine_statue_data data)
{
    for(int i=0;i<ui->light_listview->rowCount();i++){
        QLabel *machine_name = (QLabel *)ui->light_listview->cellWidget(i,0);
        QLabel *machine_event = (QLabel *)ui->light_listview->cellWidget(i,1);
        QLabel *machine_code = (QLabel *)ui->light_listview->cellWidget(i,2);
        if(machine_code->text() == data.getMachine_code()){
            machine_event->setText(data.getCurrent_event());
            machine_event->setStyleSheet(QString("background-color: %1").arg(data.getColor().name()));
        }
    }
}

void MainWindow::eatching_slot(machine_statue_data data)
{
    for(int i=0;i<ui->eatching_listview->rowCount();i++){
        QLabel *machine_name = (QLabel *)ui->eatching_listview->cellWidget(i,0);
        QLabel *machine_event = (QLabel *)ui->eatching_listview->cellWidget(i,1);
        QLabel *machine_code = (QLabel *)ui->eatching_listview->cellWidget(i,2);
        if(machine_code->text() == data.getMachine_code()){
            machine_event->setText(data.getCurrent_event());
            machine_event->setStyleSheet(QString("background-color: %1").arg(data.getColor().name()));
            break;
        }
    }
}

void MainWindow::probe_slot(machine_statue_data data)
{
    for(int i=0;i<ui->probe_listview->rowCount();i++){
        QLabel *machine_name = (QLabel *)ui->probe_listview->cellWidget(i,0);
        QLabel *machine_event = (QLabel *)ui->probe_listview->cellWidget(i,1);
        QLabel *machine_code = (QLabel *)ui->probe_listview->cellWidget(i,2);
        if(machine_code->text() == data.getMachine_code()){
            machine_event->setText(data.getCurrent_event());
            machine_event->setStyleSheet(QString("background-color: %1").arg(data.getColor().name()));
            break;
        }
    }
}

void MainWindow::probe1_slot(machine_statue_data data)
{
    for(int i=0;i<ui->probe1_listview->rowCount();i++){
        QLabel *machine_name = (QLabel *)ui->probe1_listview->cellWidget(i,0);
        QLabel *machine_event = (QLabel *)ui->probe1_listview->cellWidget(i,1);
        QLabel *machine_code = (QLabel *)ui->probe1_listview->cellWidget(i,2);
        if(machine_code->text() == data.getMachine_code()){
            machine_event->setText(data.getCurrent_event());
            machine_event->setStyleSheet(QString("background-color: %1").arg(data.getColor().name()));
            break;
        }
    }
}


void MainWindow::on_RUN_btn_clicked()
{
    login_form *widget = new login_form("RUN",current_machine_code,current_machine_name,current_process);
    widget->show();
}
void MainWindow::on_ENGR1_btn_clicked()
{
    login_form *widget = new login_form("ENGR1",current_machine_code,current_machine_name,current_process);
    widget->show();
}
void MainWindow::on_SCHDOWN1_btn_clicked()
{
    login_form *widget = new login_form("SCHDOWN1",current_machine_code,current_machine_name,current_process);
    widget->show();
}

void MainWindow::on_USCHDOWN3_btn_clicked()
{
    login_form *widget = new login_form("USCHDOWN3",current_machine_code,current_machine_name,current_process);
    widget->show();
}
void MainWindow::on_WAIT_btn_clicked()
{
    login_form *widget = new login_form("WAIT",current_machine_code,current_machine_name,current_process);
    widget->show();
}


void MainWindow::on_deposition_listview_clicked(const QModelIndex &index)
{
    current_machine_name = ((QLabel *)ui->deposition_listview->cellWidget(index.row(),0))->text();
    current_machine_code = ((QLabel *)ui->deposition_listview->cellWidget(index.row(),2))->text();
    current_process = tr("deposition");
    current_process_manager = tr("deposition");
}

void MainWindow::on_light_listview_clicked(const QModelIndex &index)
{
    current_machine_name = ((QLabel *)ui->light_listview->cellWidget(index.row(),0))->text();
    current_machine_code = ((QLabel *)ui->light_listview->cellWidget(index.row(),2))->text();
    current_process = tr("light");
    current_process_manager = tr("light");
}

void MainWindow::on_eatching_listview_clicked(const QModelIndex &index)
{
    current_machine_name = ((QLabel *)ui->eatching_listview->cellWidget(index.row(),0))->text();
    current_machine_code = ((QLabel *)ui->eatching_listview->cellWidget(index.row(),2))->text();
    current_process = tr("eatching");
    current_process_manager = tr("eatching");
}

void MainWindow::on_probe_listview_clicked(const QModelIndex &index)
{
    current_machine_name = ((QLabel *)ui->probe_listview->cellWidget(index.row(),0))->text();
    current_machine_code = ((QLabel *)ui->probe_listview->cellWidget(index.row(),2))->text();
    current_process = tr("ALL probe");
    current_process_manager = tr("ALL probe");
}

void MainWindow::on_probe1_listview_clicked(const QModelIndex &index)
{
    current_machine_name = ((QLabel *)ui->probe1_listview->cellWidget(index.row(),0))->text();
    current_machine_code = ((QLabel *)ui->probe1_listview->cellWidget(index.row(),2))->text();
    current_process = tr("ALL probe");
    current_process_manager = tr("probe1");
}

void MainWindow::on_search_btn_clicked()
{
    QSqlQuery query1(my_mesdb);
    if(ui->processbox->currentText()==tr("ALL") && ui->machine_name_box->currentText()==tr("ALL")){
        query1.exec(QString("select event_datetime,name,machine_name,event_type from OI_system_history where event_datetime BETWEEN  '%1' AND '%2' order by event_datetime desc;")
                    .arg(ui->start_time->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(ui->end_time->dateTime().toString("yyyy-MM-dd hh:mm:ss")));

    }else if(ui->machine_name_box->currentText()==tr("ALL")){
        query1.exec(QString("select event_datetime,name,machine_name,event_type from OI_system_history where event_datetime BETWEEN '%1' AND '%2' AND process = '%3' order by event_datetime desc;")
                    .arg(ui->start_time->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(ui->end_time->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(ui->processbox->currentText()));

    }else {
        query1.exec(QString("select event_datetime,name,machine_name,event_type from OI_system_history where event_datetime BETWEEN '%1' AND '%2' AND machine_name = '%3' order by event_datetime desc;")
                    .arg(ui->start_time->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(ui->end_time->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(ui->machine_name_box->currentText()));

    }
    history_model.setQuery(query1);
    history_model.submit();
}

void MainWindow::on_processbox_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query1(my_mesdb);
    QString deposition = tr("deposition");
    QString light = tr("light");
    QString eatching = tr("eatching");
    QString all_probe = tr("ALL probe");
    QString all = tr("ALL");
    ui->machine_name_box->clear();
    if(arg1 == deposition){
        query1.exec(QString("select * from OI_system_machine_table where Main_process LIKE '%1%' order by number asc").arg(deposition));
        ui->machine_name_box->addItem(all);
        while(query1.next()){
            ui->machine_name_box->addItem(query1.value("machine_name").toString(),QVariant(query1.value("machine_code").toString()));
        }
    }else if(arg1 == light){
        query1.exec(QString("select * from OI_system_machine_table where Main_process LIKE '%1%' order by number asc").arg(light));
        ui->machine_name_box->addItem(all);
        while(query1.next()){
            ui->machine_name_box->addItem(query1.value("machine_name").toString(),QVariant(query1.value("machine_code").toString()));
        }
    }else if(arg1 == eatching){
        query1.exec(QString("select * from OI_system_machine_table where Main_process LIKE '%1%' order by number asc").arg(eatching));
        ui->machine_name_box->addItem(all);
        while(query1.next()){
            ui->machine_name_box->addItem(query1.value("machine_name").toString(),QVariant(query1.value("machine_code").toString()));
        }
    }else if(arg1 ==all_probe){
        query1.exec(QString("select * from OI_system_machine_table where Main_process LIKE '%1%' order by number asc").arg(all_probe));
        ui->machine_name_box->addItem(all);
        while(query1.next()){
            ui->machine_name_box->addItem(query1.value("machine_name").toString(),QVariant(query1.value("machine_code").toString()));
        }
    }else if(arg1 ==all){
        query1.exec(QString("select * from OI_system_machine_table order by machine_name asc"));
        ui->machine_name_box->addItem(all);
        while(query1.next()){
            ui->machine_name_box->addItem(query1.value("machine_name").toString(),QVariant(query1.value("machine_code").toString()));
        }
    }
}


void MainWindow::on_add_machine_clicked()
{
    add_machine_dialog dialog;
    int result = dialog.exec();
    if(result == QDialog::Accepted){
        MainWindow *newmain = new MainWindow();
        newmain->show();
        depostion_thread->requestInterruption();
        light_thread->requestInterruption();
        eatching_thread->requestInterruption();
        probe_thread->requestInterruption();
        probe1_thread->requestInterruption();
        this->close();
    }
}

void MainWindow::on_modify_machine_clicked()
{
    modify_machine_dialog dialog(current_process_manager,current_machine_name,current_machine_code);
    int result = dialog.exec();
    if(result == QDialog::Accepted){
        MainWindow *newmain = new MainWindow();
        newmain->show();
        depostion_thread->requestInterruption();
        light_thread->requestInterruption();
        eatching_thread->requestInterruption();
        probe_thread->requestInterruption();
        probe1_thread->requestInterruption();
        this->close();
    }
}

void MainWindow::on_delete_macihne_clicked()
{
    QSqlQuery query1(my_mesdb);
    QString query_txt = QString("DELETE FROM `OI_system_machine_table`"
                                " WHERE `machine_name`='%1' AND "
                                "`machine_code`='%2' AND "
                                "`Main_process`='%3'")
                                .arg(current_machine_name)
                                .arg(current_machine_code)
                                .arg(current_process_manager);
    query1.exec(query_txt);

    MainWindow *newmain = new MainWindow();
    newmain->show();
    depostion_thread->requestInterruption();
    light_thread->requestInterruption();
    eatching_thread->requestInterruption();
    probe_thread->requestInterruption();
    probe1_thread->requestInterruption();
    this->close();
}

void MainWindow::on_managermode_btn_clicked()
{
    manager_login pupop;
    int reslut = pupop.exec();
    if(reslut == QDialog::Accepted){
        ui->add_machine->setVisible(true);
        ui->modify_machine->setVisible(true);
        ui->delete_macihne->setVisible(true);
    }
}

void MainWindow::on_calc_btn_clicked()
{
    light_db.close();
    QSqlQuery query1(my_mesdb);
    QSqlQuery query2(my_mesdb);
    QDateTime start_time;
    start_time.setDate(ui->research_start_date->date());
    start_time.setTime(QTime(8,0,0));
    QString start_time_str = start_time.toString("yyyy-MM-dd hh:mm:ss");
    QDateTime end_time;
    end_time.setDate(ui->research_end_date->date().addDays(1));
    end_time.setTime(QTime(7,59,59));
    QString end_time_str = end_time.toString("yyyy-MM-dd hh:mm:ss");


    QString db_name = QString("local_DB_OI_%1").arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"));
    if(!light_db.contains(db_name)){
        light_db = QSqlDatabase::addDatabase("QSQLITE",db_name);
        light_db.setDatabaseName(":memory:");
        if(light_db.open()){
            QSqlQuery light_query(light_db);
            light_query.exec("CREATE TABLE `OI_system_time` ( "
                             "`process` TEXT NULL, "
                             "`machine_name` TEXT NULL, "
                             "`machine_code` TEXT NULL, "
                             "`stop_time` DATETIME NULL DEFAULT NULL, "
                             "`run_time` DATETIME NULL DEFAULT NULL, "
                             "`stop_data` TEXT NULL, "
                             "`run_name` TEXT NULL, "
                             "`stop_name` TEXT NULL, "
                             "`stop_time_calc` TIME NULL DEFAULT NULL) "
                         );
            light_query.exec("CREATE TABLE `OI_system_time_2` ( "
                             "`process` TEXT NULL, "
                             "`machine_name` TEXT NULL, "
                             "`machine_code` TEXT NULL, "
                             "`stop_time_calc` TIME NULL DEFAULT NULL, "
                             "`rate` DOUBLE NULL, "
                             "`PTrate` DOUBLE NULL, "
                             "`PMrate` DOUBLE NULL, "
                             "`MTrate` DOUBLE NULL, "
                             "`Waitrate` DOUBLE NULL )"
                         );
        }
    }else {
        light_db = QSqlDatabase::database(db_name);
    }


    QString query_txt = QString("select * from OI_system_machine_table");
    query2.exec(query_txt);

    while(query2.next()){
        int lost_sec = 0;
        QString query_txt2 = QString("select * from OI_system_time where "
                                     "((run_time between '%1' AND '%2') "
                                     "or (stop_time between '%1' AND '%2') "
                                     "or (run_time is null AND stop_time <= '%2')) "
                                     "AND machine_name = '%3' "
                                     "order by run_time asc")
                                    .arg(start_time_str).arg(end_time_str)
                                    .arg(query2.value("machine_name").toString());
        query1.exec(query_txt2);
        while(query1.next()){
            QDateTime runtime;
            QDateTime stoptime;
            QSqlQuery light_query1(light_db);
            stoptime = query1.value("stop_time").toDateTime();
            if(query1.value("run_time").isNull()){
                runtime = QDateTime::currentDateTime();
            }else {
                runtime = query1.value("run_time").toDateTime();
            }
            if(query1.value("run_time").toDateTime().secsTo(end_time)<0){
                runtime = end_time;
            }
            if(query1.value("stop_time").toDateTime().secsTo(start_time)>0){
                stoptime = start_time;
            }
            int temp_calc =  stoptime.secsTo(runtime);
            lost_sec = lost_sec + temp_calc;

            QString query_txt3 = QString("INSERT INTO "
                                         "`OI_system_time` "
                                         "(`process`, `machine_name`, `machine_code`, "
                                         "`stop_time`, `run_time`, `stop_data`, `run_name`, "
                                         "`stop_name`, `stop_time_calc`) VALUES "
                                         "('%1', '%2', '%3', '%4', "
                                         "'%5', '%6', '%7', '%8', "
                                         "'%9');")
                                         .arg(query1.value("process").toString())
                                         .arg(query1.value("machine_name").toString())
                                         .arg(query1.value("machine_code").toString())
                                         .arg(stoptime.toString("yyyy-MM-dd hh:mm:ss"))
                                         .arg(runtime.toString("yyyy-MM-dd hh:mm:ss"))
                                         .arg(query1.value("stop_data").toString())
                                         .arg(query1.value("run_name").toString())
                                         .arg(query1.value("stop_name").toString())
                                         .arg(from_sec_to_timestr(lost_sec));
            light_query1.exec(query_txt3);
        }


        QSqlQuery light_query2(light_db);
        int days = start_time.daysTo(end_time);
        int oneday_sec = Onedaymin*60;
        int total_sec = oneday_sec* days;
        double rate;
        if(lost_sec != 0 ){
            rate = 100.0-(((double)lost_sec/(double)total_sec)*100.0);
        }else {
            rate = 100;
        }

        int PTtotal_sec = 0;
        QString query_txt3_1 = QString("select * from OI_system_time where "
                                     "((run_time between '%1' AND '%2') "
                                     "or (stop_time between '%1' AND '%2')) "
                                     "AND stop_data = '%3' AND machine_name = '%4'")
                                     .arg(start_time_str).arg(end_time_str)
                                     .arg(tr("PTrate")).arg(query2.value("machine_name").toString());
        light_query2.exec(query_txt3_1);
        while(light_query2.next()){
            int sec_time  = light_query2.value("stop_time").toDateTime().secsTo(light_query2.value("run_time").toDateTime());
            PTtotal_sec = PTtotal_sec + sec_time;
        }

        double PTrate;
        if(PTtotal_sec != 0 ){
            PTrate = (((double)PTtotal_sec/(double)total_sec)*100.0);
        }else {
            PTrate = 0;
        }

        int PMtotal_sec = 0;
        query_txt3_1 = QString("select * from OI_system_time where "
                                     "((run_time between '%1' AND '%2') "
                                     "or (stop_time between '%1' AND '%2')) "
                                     "AND stop_data = '%3' AND machine_name = '%4'")
                                     .arg(start_time_str).arg(end_time_str)
                                     .arg(tr("PMrate")).arg(query2.value("machine_name").toString());
        light_query2.exec(query_txt3_1);
        while(light_query2.next()){
            int sec_time  = light_query2.value("stop_time").toDateTime().secsTo(light_query2.value("run_time").toDateTime());
            PMtotal_sec = PMtotal_sec + sec_time;
        }

        double PMrate;
        if(PMtotal_sec != 0 ){
            PMrate = (((double)PMtotal_sec/(double)total_sec)*100.0);
        }else {
            PMrate = 0;
        }

        int MTtotal_sec = 0;
        query_txt3_1 = QString("select * from OI_system_time where "
                                     "((run_time between '%1' AND '%2') "
                                     "or (stop_time between '%1' AND '%2')) "
                                     "AND stop_data = '%3' AND machine_name = '%4'")
                                     .arg(start_time_str).arg(end_time_str)
                                     .arg(tr("MTrate")).arg(query2.value("machine_name").toString());
        light_query2.exec(query_txt3_1);
        while(light_query2.next()){
            int sec_time  = light_query2.value("stop_time").toDateTime().secsTo(light_query2.value("run_time").toDateTime());
            MTtotal_sec = MTtotal_sec + sec_time;
        }

        double MTrate;
        if(MTtotal_sec != 0 ){
            MTrate = (((double)MTtotal_sec/(double)total_sec)*100.0);
        }else {
            MTrate = 0;
        }

        int Waittotal_sec = 0;
        query_txt3_1 = QString("select * from OI_system_time where "
                                     "((run_time between '%1' AND '%2') "
                                     "or (stop_time between '%1' AND '%2')) "
                                     "AND stop_data = '%3' AND machine_name = '%4'")
                                     .arg(start_time_str).arg(end_time_str)
                                     .arg(tr("Waitrate")).arg(query2.value("machine_name").toString());
        light_query2.exec(query_txt3_1);
        while(light_query2.next()){
            int sec_time  = light_query2.value("stop_time").toDateTime().secsTo(light_query2.value("run_time").toDateTime());
            Waittotal_sec = Waittotal_sec + sec_time;
        }

        double Waitrate;
        if(Waittotal_sec != 0 ){
            Waitrate = (((double)Waittotal_sec/(double)total_sec)*100.0);
        }else {
            Waitrate = 0;
        }
        QString query_txt4 = QString("INSERT INTO  "
                                     "`OI_system_time_2` "
                                     "(`process`,`machine_name`, `machine_code`,"
                                     "`stop_time_calc`,`rate`,`PTrate`,`PMrate`,`MTrate`,`Waitrate`)  VALUES "
                                     "('%1','%2','%3','%4','%5','%6','%7','%8','%9')" )
                                     .arg(query2.value("Main_process").toString())
                                     .arg(query2.value("machine_name").toString())
                                     .arg(query2.value("machine_code").toString())
                                     .arg(from_sec_to_timestr(lost_sec))
                                     .arg(rate)
                                     .arg(PTrate)
                                     .arg(PMrate)
                                     .arg(MTrate)
                                     .arg(Waitrate);
        light_query2.exec(query_txt4);
    }
    QString query_txt3;

    query_txt3 = QString("select * from OI_system_time order by stop_time_calc desc");

    detail_table_model.setQuery(query_txt3,light_db);
    detail_table_model.setHeaderData(0,Qt::Horizontal,tr("process"));
    detail_table_model.setHeaderData(1,Qt::Horizontal,tr("machine_name"));
    detail_table_model.setHeaderData(3,Qt::Horizontal,tr("stop_time"));
    detail_table_model.setHeaderData(4,Qt::Horizontal,tr("run_time"));
    detail_table_model.setHeaderData(5,Qt::Horizontal,tr("stop_data"));
    detail_table_model.setHeaderData(6,Qt::Horizontal,tr("run_name"));
    detail_table_model.setHeaderData(7,Qt::Horizontal,tr("stop_name"));
    detail_table_model.setHeaderData(8,Qt::Horizontal,tr("stop_time_calc"));
    ui->detail_table->setModel(&detail_table_model);

    detail_table_model.submit();
    ui->detail_table->horizontalHeader()->hideSection(2);
    ui->detail_table->horizontalHeader()->resizeSection(0,50);
    ui->detail_table->horizontalHeader()->resizeSection(3,150);
    ui->detail_table->horizontalHeader()->resizeSection(4,150);
    ui->detail_table->horizontalHeader()->resizeSection(6,60);
    ui->detail_table->horizontalHeader()->resizeSection(7,60);
    ui->detail_table->horizontalHeader()->resizeSection(8,60);

    QString query_txt4 = QString("select * from OI_system_time_2 order by rate asc");
    total_table_model.setQuery(query_txt4,light_db);
    total_table_model.setHeaderData(0,Qt::Horizontal,tr("process"));
    total_table_model.setHeaderData(1,Qt::Horizontal,tr("machine_name"));
    total_table_model.setHeaderData(3,Qt::Horizontal,tr("stop_time_calc"));
    total_table_model.setHeaderData(4,Qt::Horizontal,tr("operation_ratio"));
    total_table_model.setHeaderData(5,Qt::Horizontal,tr("PTrate"));
    total_table_model.setHeaderData(6,Qt::Horizontal,tr("PMrate"));
    total_table_model.setHeaderData(7,Qt::Horizontal,tr("MTrate"));
    total_table_model.setHeaderData(8,Qt::Horizontal,tr("Waitrate"));

    ui->total_table->setModel(&total_table_model);
    total_table_model.submit();
    ui->total_table->horizontalHeader()->hideSection(2);
}

void MainWindow::on_calc(QString select_machine)
{
    light_db.close();
    QSqlQuery query1(my_mesdb);
    QSqlQuery query2(my_mesdb);
    QDateTime start_time;
    start_time.setDate(ui->research_start_date->date());
    start_time.setTime(QTime(8,0,0));
    QString start_time_str = start_time.toString("yyyy-MM-dd hh:mm:ss");
    QDateTime end_time;
    end_time.setDate(ui->research_end_date->date().addDays(1));
    end_time.setTime(QTime(7,59,59));
    QString end_time_str = end_time.toString("yyyy-MM-dd hh:mm:ss");


    QString db_name = QString("local_DB_OI_%1").arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"));
    if(!light_db.contains(db_name)){
        light_db = QSqlDatabase::addDatabase("QSQLITE",db_name);
        light_db.setDatabaseName(":memory:");
        if(light_db.open()){
            QSqlQuery light_query(light_db);
            light_query.exec("CREATE TABLE `OI_system_time` ( "
                             "`process` TEXT NULL, "
                             "`machine_name` TEXT NULL, "
                             "`machine_code` TEXT NULL, "
                             "`stop_time` DATETIME NULL DEFAULT NULL, "
                             "`run_time` DATETIME NULL DEFAULT NULL, "
                             "`stop_data` TEXT NULL, "
                             "`run_name` TEXT NULL, "
                             "`stop_name` TEXT NULL, "
                             "`stop_time_calc` TIME NULL DEFAULT NULL) "
                         );
            light_query.exec("CREATE TABLE `OI_system_time_2` ( "
                             "`process` TEXT NULL, "
                             "`machine_name` TEXT NULL, "
                             "`machine_code` TEXT NULL, "
                             "`stop_time_calc` TIME NULL DEFAULT NULL, "
                             "`rate` DOUBLE NULL, "
                             "`PTrate` DOUBLE NULL, "
                             "`PMrate` DOUBLE NULL, "
                             "`MTrate` DOUBLE NULL, "
                             "`Waitrate` DOUBLE NULL )"
                         );
        }
    }else {
        light_db = QSqlDatabase::database(db_name);
    }


    QString query_txt = QString("select * from OI_system_machine_table");
    query2.exec(query_txt);

    while(query2.next()){
        int lost_sec = 0;
        QString query_txt2 = QString("select * from OI_system_time where "
                                     "((run_time between '%1' AND '%2') "
                                     "or (stop_time between '%1' AND '%2') "
                                     "or (run_time is null AND stop_time <= '%2')) "
                                     "AND machine_name = '%3' "
                                     "order by run_time asc")
                                    .arg(start_time_str).arg(end_time_str)
                                    .arg(query2.value("machine_name").toString());
        query1.exec(query_txt2);
        while(query1.next()){
            QDateTime runtime;
            QDateTime stoptime;
            QSqlQuery light_query1(light_db);
            stoptime = query1.value("stop_time").toDateTime();
            if(query1.value("run_time").isNull()){
                runtime = QDateTime::currentDateTime();
            }else {
                runtime = query1.value("run_time").toDateTime();
            }
            if(query1.value("run_time").toDateTime().secsTo(end_time)<0){
                runtime = end_time;
            }
            if(query1.value("stop_time").toDateTime().secsTo(start_time)>0){
                stoptime = start_time;
            }
            int temp_calc =  stoptime.secsTo(runtime);
            lost_sec = lost_sec + temp_calc;

            QString query_txt3 = QString("INSERT INTO "
                                         "`OI_system_time` "
                                         "(`process`, `machine_name`, `machine_code`, "
                                         "`stop_time`, `run_time`, `stop_data`, `run_name`, "
                                         "`stop_name`, `stop_time_calc`) VALUES "
                                         "('%1', '%2', '%3', '%4', "
                                         "'%5', '%6', '%7', '%8', "
                                         "'%9');")
                                         .arg(query1.value("process").toString())
                                         .arg(query1.value("machine_name").toString())
                                         .arg(query1.value("machine_code").toString())
                                         .arg(stoptime.toString("yyyy-MM-dd hh:mm:ss"))
                                         .arg(runtime.toString("yyyy-MM-dd hh:mm:ss"))
                                         .arg(query1.value("stop_data").toString())
                                         .arg(query1.value("run_name").toString())
                                         .arg(query1.value("stop_name").toString())
                                         .arg(from_sec_to_timestr(lost_sec));
            light_query1.exec(query_txt3);
        }


        QSqlQuery light_query2(light_db);
        int days = start_time.daysTo(end_time);
        int oneday_sec = Onedaymin*60;
        int total_sec = oneday_sec* days;
        double rate;
        if(lost_sec != 0 ){
            rate = 100.0-(((double)lost_sec/(double)total_sec)*100.0);
        }else {
            rate = 100;
        }

        int PTtotal_sec = 0;
        QString query_txt3_1 = QString("select * from OI_system_time where "
                                     "((run_time between '%1' AND '%2') "
                                     "or (stop_time between '%1' AND '%2')) "
                                     "AND stop_data = '%3' AND machine_name = '%4'")
                                     .arg(start_time_str).arg(end_time_str)
                                     .arg(tr("PTrate")).arg(query2.value("machine_name").toString());
        light_query2.exec(query_txt3_1);
        while(light_query2.next()){
            int sec_time  = light_query2.value("stop_time").toDateTime().secsTo(light_query2.value("run_time").toDateTime());
            PTtotal_sec = PTtotal_sec + sec_time;
        }

        double PTrate;
        if(PTtotal_sec != 0 ){
            PTrate = (((double)PTtotal_sec/(double)total_sec)*100.0);
        }else {
            PTrate = 0;
        }



        int PMtotal_sec = 0;
        query_txt3_1 = QString("select * from OI_system_time where "
                                     "((run_time between '%1' AND '%2') "
                                     "or (stop_time between '%1' AND '%2')) "
                                     "AND stop_data = '%3' AND machine_name = '%4'")
                                     .arg(start_time_str).arg(end_time_str)
                                     .arg(tr("PMrate")).arg(query2.value("machine_name").toString());
        light_query2.exec(query_txt3_1);
        while(light_query2.next()){
            int sec_time  = light_query2.value("stop_time").toDateTime().secsTo(light_query2.value("run_time").toDateTime());
            PMtotal_sec = PMtotal_sec + sec_time;
        }

        double PMrate;
        if(PMtotal_sec != 0 ){
            PMrate = (((double)PMtotal_sec/(double)total_sec)*100.0);
        }else {
            PMrate = 0;
        }

        int MTtotal_sec = 0;
        query_txt3_1 = QString("select * from OI_system_time where "
                                     "((run_time between '%1' AND '%2') "
                                     "or (stop_time between '%1' AND '%2')) "
                                     "AND stop_data = '%3' AND machine_name = '%4'")
                                     .arg(start_time_str).arg(end_time_str)
                                     .arg(tr("MTrate")).arg(query2.value("machine_name").toString());
        light_query2.exec(query_txt3_1);
        while(light_query2.next()){
            int sec_time  = light_query2.value("stop_time").toDateTime().secsTo(light_query2.value("run_time").toDateTime());
            MTtotal_sec = MTtotal_sec + sec_time;
        }

        double MTrate;
        if(MTtotal_sec != 0 ){
            MTrate = (((double)MTtotal_sec/(double)total_sec)*100.0);
        }else {
            MTrate = 0;
        }

        int Waittotal_sec = 0;
        query_txt3_1 = QString("select * from OI_system_time where "
                                     "((run_time between '%1' AND '%2') "
                                     "or (stop_time between '%1' AND '%2')) "
                                     "AND stop_data = '%3' AND machine_name = '%4'")
                                     .arg(start_time_str).arg(end_time_str)
                                     .arg(tr("Waitrate")).arg(query2.value("machine_name").toString());
        light_query2.exec(query_txt3_1);
        while(light_query2.next()){
            int sec_time  = light_query2.value("stop_time").toDateTime().secsTo(light_query2.value("run_time").toDateTime());
            Waittotal_sec = Waittotal_sec + sec_time;
        }

        double Waitrate;
        if(Waittotal_sec != 0 ){
            Waitrate = (((double)Waittotal_sec/(double)total_sec)*100.0);
        }else {
            Waitrate = 0;
        }

        rate = rate + Waitrate+ PTrate;
        QString query_txt4 = QString("INSERT INTO  "
                                     "`OI_system_time_2` "
                                     "(`process`,`machine_name`, `machine_code`,"
                                     "`stop_time_calc`,`rate`,`PTrate`,`PMrate`,`MTrate`,`Waitrate`)  VALUES "
                                     "('%1','%2','%3','%4','%5','%6','%7','%8','%9')" )
                                     .arg(query2.value("Main_process").toString())
                                     .arg(query2.value("machine_name").toString())
                                     .arg(query2.value("machine_code").toString())
                                     .arg(from_sec_to_timestr(lost_sec))
                                     .arg(rate)
                                     .arg(PTrate)
                                     .arg(PMrate)
                                     .arg(MTrate)
                                     .arg(Waitrate);
        light_query2.exec(query_txt4);
    }
    QString query_txt3;

    query_txt3 = QString("select * from OI_system_time where machine_name = '%1' order by stop_time_calc desc ").arg(select_machine);

    detail_table_model.setQuery(query_txt3,light_db);
    detail_table_model.setHeaderData(0,Qt::Horizontal,tr("process"));
    detail_table_model.setHeaderData(1,Qt::Horizontal,tr("machine_name"));
    detail_table_model.setHeaderData(3,Qt::Horizontal,tr("stop_time"));
    detail_table_model.setHeaderData(4,Qt::Horizontal,tr("run_time"));
    detail_table_model.setHeaderData(5,Qt::Horizontal,tr("stop_data"));
    detail_table_model.setHeaderData(6,Qt::Horizontal,tr("run_name"));
    detail_table_model.setHeaderData(7,Qt::Horizontal,tr("stop_name"));
    detail_table_model.setHeaderData(8,Qt::Horizontal,tr("stop_time_calc"));
    ui->detail_table->setModel(&detail_table_model);

    detail_table_model.submit();
    ui->detail_table->horizontalHeader()->hideSection(2);
    ui->detail_table->horizontalHeader()->resizeSection(0,50);
    ui->detail_table->horizontalHeader()->resizeSection(3,150);
    ui->detail_table->horizontalHeader()->resizeSection(4,150);
    ui->detail_table->horizontalHeader()->resizeSection(6,60);
    ui->detail_table->horizontalHeader()->resizeSection(7,60);
    ui->detail_table->horizontalHeader()->resizeSection(8,60);

//    QString query_txt4 = QString("select * from OI_system_time_2 order by rate asc");
//    total_table_model.setQuery(query_txt4,light_db);
//    ui->total_table->setModel(&total_table_model);
//    total_table_model.submit();
//    ui->total_table->horizontalHeader()->hideSection(2);
}

QString MainWindow::from_sec_to_timestr(int secs)
{
    int hour = secs/3600;
    int min = (secs%3600)/60;
    int sec = (secs%3600)%60;
    QString reslut = QString("%1:%2:%3").arg(hour).arg(min).arg(sec);
    return reslut;
}

void MainWindow::on_show_detail_total_clicked()
{
    on_calc_btn_clicked();
}

void MainWindow::on_total_table_clicked(const QModelIndex &index)
{

    on_calc(index.model()->index(index.row(),1).data().toString());
}
