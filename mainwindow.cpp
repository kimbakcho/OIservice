#include "ui_mainwindow.h"

#include "mainwindow.h"

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


    QDateTime start_time;
    start_time.setDate(ui->research_start_date->date());
    start_time.setTime(QTime(8,0,0));
    QString start_time_str = start_time.toString("yyyy-MM-dd hh:mm:ss");
    QDateTime end_time;
    end_time.setDate(ui->research_end_date->date().addDays(1));
    end_time.setTime(QTime(7,59,59));
    QString end_time_str = end_time.toString("yyyy-MM-dd hh:mm:ss");

    ui->LA_start_time->setText(start_time_str);
    ui->LA_EndTime->setText(end_time_str);


    ui->tabWidget->tabBar()->setTabEnabled(3,false);
    ui->tabWidget->tabBar()->setTabEnabled(4,false);

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
    QSqlQuery query3(my_mesdb);
    QString query_txt5;
    QDateTime start_time;
    start_time.setDate(ui->research_start_date->date());
    start_time.setTime(QTime(8,0,0));
    QString start_time_str = start_time.toString("yyyy-MM-dd hh:mm:ss");
    QDateTime end_time;
    end_time.setDate(ui->research_end_date->date().addDays(1));
    end_time.setTime(QTime(7,59,59));
    QString end_time_str = end_time.toString("yyyy-MM-dd hh:mm:ss");

    while(ui->total_table->rowCount()>0){
        ui->total_table->removeRow(0);
    }

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
                             "`PTrate` DOUBLE NULL, " //공정설비 테스트
                             "`PMrate` DOUBLE NULL, " //예방정비
                             "`MTrate` DOUBLE NULL, " //설비 고장
                             "`Waitrate` DOUBLE NULL," //대기
                             "`USCHDOWN4` DOUBLE NULL, " //순간정지
                             "`USCHDOWN1` DOUBLE NULL, " //자재 품절
                             "`SCHDOWN2` DOUBLE NULL, " //기종 변경
                             "`USCHDOWN2` DOUBLE NULL, " //품질문제
                             "`NONSCHED` DOUBLE NULL );" //휴지
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
                if(end_time.secsTo(runtime)>0){
                    runtime = end_time;
                }
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
            query_txt5 = QString("select SUM(remove_sec)AS'remove_sec' from OI_system_remove_event_time "
                                         "where remove_time between '%1' AND '%2'")
                                         .arg(stoptime.toString("yyyy-MM-dd hh:mm:ss"))
                                         .arg(runtime.toString("yyyy-MM-dd hh:mm:ss"));
            query3.exec(query_txt5);
            if(query3.next()){
                temp_calc = temp_calc - query3.value("remove_sec").toInt();
                if(temp_calc<0){
                    query_txt5 = QString("select * from OI_system_remove_event_time "
                                                 "where remove_time between '%1' AND '%2' order by remove_time desc")
                                                 .arg(stoptime.toString("yyyy-MM-dd hh:mm:ss"))
                                                 .arg(runtime.toString("yyyy-MM-dd hh:mm:ss"));
                    QSqlQuery query5(my_mesdb);
                    query5.exec(query_txt5);
                    if(query5.next()){
                        runtime = query5.value("remove_time").toDateTime();
                        temp_calc = stoptime.secsTo(runtime);
                    }
                }
            }
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
                                         .arg(from_sec_to_timestr(temp_calc));
            light_query1.exec(query_txt3);
        }


        QSqlQuery light_query2(light_db);
        int days = start_time.daysTo(end_time);
        int oneday_sec = Onedaymin*60;
        int total_sec = oneday_sec* days;
        double rate;
        if(lost_sec != 0 ){
            rate = 100.0-(((double)lost_sec/(double)total_sec)*100.0);
            if(rate<0){
                rate = 0;
            }
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
            query_txt5 = QString("select SUM(remove_sec)AS'remove_sec' from OI_system_remove_event_time "
                                         "where remove_time between '%1' AND '%2'")
                                         .arg(light_query2.value("stop_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                                         .arg(light_query2.value("run_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            query3.exec(query_txt5);
            if(query3.next()){
                PTtotal_sec = PTtotal_sec - query3.value("remove_sec").toInt();
                if(PTtotal_sec<0){
                    query_txt5 = QString("select * from OI_system_remove_event_time "
                                                 "where remove_time between '%1' AND '%2' order by remove_time desc")
                                                 .arg(light_query2.value("stop_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                                                 .arg(light_query2.value("run_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                    QSqlQuery query5(my_mesdb);
                    query5.exec(query_txt5);
                    if(query5.next()){
                        PTtotal_sec = light_query2.value("stop_time").toDateTime().secsTo(query5.value("remove_time").toDateTime());
                    }
                }
            }
        }

        double PTrate;
        if(PTtotal_sec != 0 ){
            PTrate = (((double)PTtotal_sec/(double)total_sec)*100.0);
            if(PTrate>=100){
                PTrate = 100;
            }
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
            query_txt5 = QString("select SUM(remove_sec)AS'remove_sec' from OI_system_remove_event_time "
                                         "where remove_time between '%1' AND '%2'")
                                        .arg(light_query2.value("stop_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                                        .arg(light_query2.value("run_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            query3.exec(query_txt5);
            if(query3.next()){
                PMtotal_sec = PMtotal_sec - query3.value("remove_sec").toInt();
                if(PMtotal_sec<0){
                    query_txt5 = QString("select * from OI_system_remove_event_time "
                                                 "where remove_time between '%1' AND '%2' order by remove_time desc")
                                                 .arg(light_query2.value("stop_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                                                 .arg(light_query2.value("run_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                    QSqlQuery query5(my_mesdb);
                    query5.exec(query_txt5);
                    if(query5.next()){
                        PMtotal_sec = light_query2.value("stop_time").toDateTime().secsTo(query5.value("remove_time").toDateTime());
                    }
                }
            }
        }

        double PMrate;
        if(PMtotal_sec != 0 ){
            PMrate = (((double)PMtotal_sec/(double)total_sec)*100.0);
            if(PMrate>=100){
                PMrate = 100;
            }
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
            query_txt5 = QString("select SUM(remove_sec)AS'remove_sec' from OI_system_remove_event_time "
                                         "where remove_time between '%1' AND '%2'")
                                    .arg(light_query2.value("stop_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                                    .arg(light_query2.value("run_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            query3.exec(query_txt5);
            if(query3.next()){
                MTtotal_sec = MTtotal_sec - query3.value("remove_sec").toInt();
                if(MTtotal_sec<0){
                    query_txt5 = QString("select * from OI_system_remove_event_time "
                                                 "where remove_time between '%1' AND '%2' order by remove_time desc")
                                                 .arg(light_query2.value("stop_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                                                 .arg(light_query2.value("run_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                    QSqlQuery query5(my_mesdb);
                    query5.exec(query_txt5);
                    if(query5.next()){
                        MTtotal_sec = light_query2.value("stop_time").toDateTime().secsTo(query5.value("remove_time").toDateTime());
                    }
                }
            }
        }

        double MTrate;
        if(MTtotal_sec != 0 ){
            MTrate = (((double)MTtotal_sec/(double)total_sec)*100.0);
            if(MTrate>=100){
                MTrate = 100;
            }
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
            query_txt5 = QString("select SUM(remove_sec)AS'remove_sec' from OI_system_remove_event_time "
                                         "where remove_time between '%1' AND '%2'")
                                    .arg(light_query2.value("stop_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                                    .arg(light_query2.value("run_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            query3.exec(query_txt5);
            if(query3.next()){
                Waittotal_sec = Waittotal_sec - query3.value("remove_sec").toInt();
                if(Waittotal_sec<0){
                    query_txt5 = QString("select * from OI_system_remove_event_time "
                                                 "where remove_time between '%1' AND '%2' order by remove_time desc")
                                                 .arg(light_query2.value("stop_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                                                 .arg(light_query2.value("run_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                    QSqlQuery query5(my_mesdb);
                    query5.exec(query_txt5);
                    if(query5.next()){
                        Waittotal_sec = light_query2.value("stop_time").toDateTime().secsTo(query5.value("remove_time").toDateTime());
                    }
                }
            }
        }

        double Waitrate;
        if(Waittotal_sec != 0 ){
            Waitrate = (((double)Waittotal_sec/(double)total_sec)*100.0);
            if(Waitrate>=100){
                Waitrate = 100;
            }
        }else {
            Waitrate = 0;
        }

        int USCHDOWN4_total_sec = 0;
        QString query_txt3_2 = QString("select * from OI_system_time where "
                                     "((run_time between '%1' AND '%2') "
                                     "or (stop_time between '%1' AND '%2')) "
                                     "AND stop_data = '%3' AND machine_name = '%4'")
                                     .arg(start_time_str).arg(end_time_str)
                                     .arg(tr("USCHDOWN4")).arg(query2.value("machine_name").toString());
        light_query2.exec(query_txt3_2);
        while(light_query2.next()){
            int sec_time  = light_query2.value("stop_time").toDateTime().secsTo(light_query2.value("run_time").toDateTime());
            USCHDOWN4_total_sec = USCHDOWN4_total_sec + sec_time;
            query_txt5 = QString("select SUM(remove_sec)AS'remove_sec' from OI_system_remove_event_time "
                                         "where remove_time between '%1' AND '%2'")
                                         .arg(light_query2.value("stop_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                                         .arg(light_query2.value("run_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            query3.exec(query_txt5);
            if(query3.next()){
                USCHDOWN4_total_sec = USCHDOWN4_total_sec - query3.value("remove_sec").toInt();
                if(USCHDOWN4_total_sec<0){
                    query_txt5 = QString("select * from OI_system_remove_event_time "
                                                 "where remove_time between '%1' AND '%2' order by remove_time desc")
                                                 .arg(light_query2.value("stop_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                                                 .arg(light_query2.value("run_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                    QSqlQuery query5(my_mesdb);
                    query5.exec(query_txt5);
                    if(query5.next()){
                        USCHDOWN4_total_sec = light_query2.value("stop_time").toDateTime().secsTo(query5.value("remove_time").toDateTime());
                    }
                }

            }
        }
        double USCHDOWN4rate;
        if(USCHDOWN4_total_sec != 0 ){
            USCHDOWN4rate = (((double)USCHDOWN4_total_sec/(double)total_sec)*100.0);
            if(USCHDOWN4rate>=100){
                USCHDOWN4rate = 100;
            }
        }else {
            USCHDOWN4rate = 0;
        }

        int USCHDOWN1_total_sec = 0;
        QString query_txt3_3 = QString("select * from OI_system_time where "
                                     "((run_time between '%1' AND '%2') "
                                     "or (stop_time between '%1' AND '%2')) "
                                     "AND stop_data = '%3' AND machine_name = '%4'")
                                     .arg(start_time_str).arg(end_time_str)
                                     .arg(tr("USCHDOWN1")).arg(query2.value("machine_name").toString());
        light_query2.exec(query_txt3_3);
        while(light_query2.next()){
            int sec_time  = light_query2.value("stop_time").toDateTime().secsTo(light_query2.value("run_time").toDateTime());
            USCHDOWN1_total_sec = USCHDOWN1_total_sec + sec_time;
            query_txt5 = QString("select SUM(remove_sec)AS'remove_sec' from OI_system_remove_event_time "
                                         "where remove_time between '%1' AND '%2'")
                                         .arg(light_query2.value("stop_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                                         .arg(light_query2.value("run_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            query3.exec(query_txt5);
            if(query3.next()){
                USCHDOWN1_total_sec = USCHDOWN1_total_sec - query3.value("remove_sec").toInt();
            }
        }
        double USCHDOWN1rate;
        if(USCHDOWN1_total_sec != 0 ){
            USCHDOWN1rate = (((double)USCHDOWN1_total_sec/(double)total_sec)*100.0);
            if(USCHDOWN1rate>=100){
                USCHDOWN1rate = 100;
            }
        }else {
            USCHDOWN1rate = 0;
        }

        int SCHDOWN2_total_sec = 0;
        QString query_txt3_4 = QString("select * from OI_system_time where "
                                     "((run_time between '%1' AND '%2') "
                                     "or (stop_time between '%1' AND '%2')) "
                                     "AND stop_data = '%3' AND machine_name = '%4'")
                                     .arg(start_time_str).arg(end_time_str)
                                     .arg(tr("SCHDOWN2")).arg(query2.value("machine_name").toString());
        light_query2.exec(query_txt3_4);
        while(light_query2.next()){
            int sec_time  = light_query2.value("stop_time").toDateTime().secsTo(light_query2.value("run_time").toDateTime());
            SCHDOWN2_total_sec = SCHDOWN2_total_sec + sec_time;
            query_txt5 = QString("select SUM(remove_sec)AS'remove_sec' from OI_system_remove_event_time "
                                         "where remove_time between '%1' AND '%2'")
                                         .arg(light_query2.value("stop_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                                         .arg(light_query2.value("run_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            query3.exec(query_txt5);
            if(query3.next()){
                SCHDOWN2_total_sec = SCHDOWN2_total_sec - query3.value("remove_sec").toInt();
            }
        }
        double SCHDOWN2rate;
        if(SCHDOWN2_total_sec != 0 ){
            SCHDOWN2rate = (((double)SCHDOWN2_total_sec/(double)total_sec)*100.0);
            if(SCHDOWN2rate>=100){
                SCHDOWN2rate = 100;
            }
        }else {
            SCHDOWN2rate = 0;
        }

        int USCHDOWN2_total_sec = 0;
        QString query_txt3_5 = QString("select * from OI_system_time where "
                                     "((run_time between '%1' AND '%2') "
                                     "or (stop_time between '%1' AND '%2')) "
                                     "AND stop_data = '%3' AND machine_name = '%4'")
                                     .arg(start_time_str).arg(end_time_str)
                                     .arg(tr("USCHDOWN2")).arg(query2.value("machine_name").toString());
        light_query2.exec(query_txt3_5);
        while(light_query2.next()){
            int sec_time  = light_query2.value("stop_time").toDateTime().secsTo(light_query2.value("run_time").toDateTime());
            USCHDOWN2_total_sec = USCHDOWN2_total_sec + sec_time;
            query_txt5 = QString("select SUM(remove_sec)AS'remove_sec' from OI_system_remove_event_time "
                                         "where remove_time between '%1' AND '%2'")
                                         .arg(light_query2.value("stop_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                                         .arg(light_query2.value("run_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            query3.exec(query_txt5);
            if(query3.next()){
                USCHDOWN2_total_sec = USCHDOWN2_total_sec - query3.value("remove_sec").toInt();
            }
        }
        double USCHDOWN2rate;
        if(USCHDOWN2_total_sec != 0 ){
            USCHDOWN2rate = (((double)USCHDOWN2_total_sec/(double)total_sec)*100.0);
            if(USCHDOWN2rate>=100){
                USCHDOWN2rate = 100;
            }
        }else {
            USCHDOWN2rate = 0;
        }

        int NONSCHED_total_sec = 0;
        QString query_txt3_6 = QString("select * from OI_system_time where "
                                     "((run_time between '%1' AND '%2') "
                                     "or (stop_time between '%1' AND '%2')) "
                                     "AND stop_data = '%3' AND machine_name = '%4'")
                                     .arg(start_time_str).arg(end_time_str)
                                     .arg(tr("NONSCHED")).arg(query2.value("machine_name").toString());
        light_query2.exec(query_txt3_6);
        while(light_query2.next()){
            int sec_time  = light_query2.value("stop_time").toDateTime().secsTo(light_query2.value("run_time").toDateTime());
            NONSCHED_total_sec = NONSCHED_total_sec + sec_time;
            query_txt5 = QString("select SUM(remove_sec)AS'remove_sec' from OI_system_remove_event_time "
                                         "where remove_time between '%1' AND '%2'")
                                         .arg(light_query2.value("stop_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                                         .arg(light_query2.value("run_time").toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            query3.exec(query_txt5);
            if(query3.next()){
                NONSCHED_total_sec = NONSCHED_total_sec - query3.value("remove_sec").toInt();
            }
        }
        double NONSCHEDrate;
        if(NONSCHED_total_sec != 0 ){
            NONSCHEDrate = (((double)NONSCHED_total_sec/(double)total_sec)*100.0);
            if(NONSCHEDrate>=100){
                NONSCHEDrate = 100;
            }
        }else {
            NONSCHEDrate = 0;
        }

        QString query_txt4 = QString("INSERT INTO  "
                                     "`OI_system_time_2` "
                                     "(`process`,`machine_name`, `machine_code`,"
                                     "`stop_time_calc`,`rate`,`PTrate`,`PMrate`,`MTrate`,"
                                     "`Waitrate`,`USCHDOWN4`,`USCHDOWN1`,`SCHDOWN2`,`USCHDOWN2`,`NONSCHED`)  VALUES "
                                     "('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14')" )
                                     .arg(query2.value("Main_process").toString())
                                     .arg(query2.value("machine_name").toString())
                                     .arg(query2.value("machine_code").toString())
                                     .arg(from_sec_to_timestr(lost_sec))
                                     .arg(rate)
                                     .arg(PTrate)
                                     .arg(PMrate)
                                     .arg(MTrate)
                                     .arg(Waitrate)
                                     .arg(USCHDOWN4rate)
                                     .arg(USCHDOWN1rate)
                                     .arg(SCHDOWN2rate)
                                     .arg(USCHDOWN2rate)
                                     .arg(NONSCHEDrate);
        light_query2.exec(query_txt4);




    }
    QString query_txt3;


    if(ui->CB_select_process->currentText()==tr("ALLPRocess")){
        query_txt3 = QString("select * from OI_system_time order by stop_time_calc desc ");
    }else if(ui->CB_select_process->currentText()==tr("deposition")){
        query_txt3 = QString("select * from OI_system_time order by stop_time_calc desc where process = '%1'").arg(tr("deposition"));
    }else if(ui->CB_select_process->currentText()==tr("light")){
        query_txt3 = QString("select * from OI_system_time order by stop_time_calc desc where process = '%1'").arg(tr("light"));
    }else if(ui->CB_select_process->currentText()==tr("eatching")){
        query_txt3 = QString("select * from OI_system_time order by stop_time_calc desc where process = '%1'").arg(tr("eatching"));
    }else if(ui->CB_select_process->currentText()==tr("ALL probe")){
        query_txt3 = QString("select * from OI_system_time order by stop_time_calc desc where process LIKE '%1%'").arg(tr("ALL probe"));
    }

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

    QString query_txt4;

    if(ui->CB_select_process->currentText()==tr("ALLPRocess")){
        query_txt4 = QString("select process,machine_name,machine_code,"
                                         "stop_time_calc,ROUND(rate,2) AS rate,ROUND(PTrate,2) AS PTrate,ROUND(PMrate,2) AS PMrate,ROUND(MTrate,2) AS MTrate,ROUND(Waitrate,2) AS Waitrate,"
                                         "ROUND(USCHDOWN4,2) AS USCHDOWN4 ,ROUND(USCHDOWN1,2) AS USCHDOWN1,ROUND(SCHDOWN2,2) AS SCHDOWN2,ROUND(USCHDOWN2,2) AS USCHDOWN2,ROUND(NONSCHED,2) AS NONSCHED ,"
                                         "ROUND((PTrate+PMrate+MTrate+Waitrate+USCHDOWN4+USCHDOWN1+SCHDOWN2+USCHDOWN2+NONSCHED),2)AS stop_loss_per  "
                                         "from OI_system_time_2 "
                                         "order by rate asc");
    }else if(ui->CB_select_process->currentText()==tr("deposition")){
        query_txt4 = QString("select process,machine_name,machine_code,"
                                         "stop_time_calc,ROUND(rate,2) AS rate,ROUND(PTrate,2) AS PTrate,ROUND(PMrate,2) AS PMrate,ROUND(MTrate,2) AS MTrate,ROUND(Waitrate,2) AS Waitrate,"
                                         "ROUND(USCHDOWN4,2) AS USCHDOWN4 ,ROUND(USCHDOWN1,2) AS USCHDOWN1,ROUND(SCHDOWN2,2) AS SCHDOWN2,ROUND(USCHDOWN2,2) AS USCHDOWN2,ROUND(NONSCHED,2) AS NONSCHED ,"
                                         "ROUND((PTrate+PMrate+MTrate+Waitrate+USCHDOWN4+USCHDOWN1+SCHDOWN2+USCHDOWN2+NONSCHED),2)AS stop_loss_per  "
                                         "from OI_system_time_2 "
                                         "where process = '%1' order by rate asc").arg(tr("deposition"));
    }else if(ui->CB_select_process->currentText()==tr("light")){
        query_txt4 = QString("select process,machine_name,machine_code,"
                                         "stop_time_calc,ROUND(rate,2) AS rate,ROUND(PTrate,2) AS PTrate,ROUND(PMrate,2) AS PMrate,ROUND(MTrate,2) AS MTrate,ROUND(Waitrate,2) AS Waitrate,"
                                         "ROUND(USCHDOWN4,2) AS USCHDOWN4 ,ROUND(USCHDOWN1,2) AS USCHDOWN1,ROUND(SCHDOWN2,2) AS SCHDOWN2,ROUND(USCHDOWN2,2) AS USCHDOWN2,ROUND(NONSCHED,2) AS NONSCHED ,"
                                         "ROUND((PTrate+PMrate+MTrate+Waitrate+USCHDOWN4+USCHDOWN1+SCHDOWN2+USCHDOWN2+NONSCHED),2)AS stop_loss_per  "
                                         "from OI_system_time_2 "
                                         "where process = '%1' order by rate asc").arg(tr("light"));
    }else if(ui->CB_select_process->currentText()==tr("eatching")){
        query_txt4 = QString("select process,machine_name,machine_code,"
                                         "stop_time_calc,ROUND(rate,2) AS rate,ROUND(PTrate,2) AS PTrate,ROUND(PMrate,2) AS PMrate,ROUND(MTrate,2) AS MTrate,ROUND(Waitrate,2) AS Waitrate,"
                                         "ROUND(USCHDOWN4,2) AS USCHDOWN4 ,ROUND(USCHDOWN1,2) AS USCHDOWN1,ROUND(SCHDOWN2,2) AS SCHDOWN2,ROUND(USCHDOWN2,2) AS USCHDOWN2,ROUND(NONSCHED,2) AS NONSCHED ,"
                                         "ROUND((PTrate+PMrate+MTrate+Waitrate+USCHDOWN4+USCHDOWN1+SCHDOWN2+USCHDOWN2+NONSCHED),2)AS stop_loss_per  "
                                         "from OI_system_time_2 "
                                         "where process = '%1' order by rate asc").arg(tr("eatching"));
    }else if(ui->CB_select_process->currentText()==tr("ALL probe")){
        query_txt4 = QString("select process,machine_name,machine_code,"
                                         "stop_time_calc,ROUND(rate,2) AS rate,ROUND(PTrate,2) AS PTrate,ROUND(PMrate,2) AS PMrate,ROUND(MTrate,2) AS MTrate,ROUND(Waitrate,2) AS Waitrate,"
                                         "ROUND(USCHDOWN4,2) AS USCHDOWN4 ,ROUND(USCHDOWN1,2) AS USCHDOWN1,ROUND(SCHDOWN2,2) AS SCHDOWN2,ROUND(USCHDOWN2,2) AS USCHDOWN2,ROUND(NONSCHED,2) AS NONSCHED ,"
                                         "ROUND((PTrate+PMrate+MTrate+Waitrate+USCHDOWN4+USCHDOWN1+SCHDOWN2+USCHDOWN2+NONSCHED),2)AS stop_loss_per  "
                                         "from OI_system_time_2 "
                                         "where process LIKE '%1%' order by rate asc").arg(tr("ALL probe"));
    }

//    total_table_model.setQuery(query_txt4,light_db);
//    qDebug()<<query_txt4;
//    qDebug()<<total_table_model.lastError().text();
//    total_table_model.setHeaderData(0,Qt::Horizontal,tr("process"));
//    total_table_model.setHeaderData(1,Qt::Horizontal,tr("machine_name"));
//    total_table_model.setHeaderData(3,Qt::Horizontal,tr("stop_time_calc"));
//    total_table_model.setHeaderData(4,Qt::Horizontal,tr("operation_ratio"));
//    total_table_model.setHeaderData(5,Qt::Horizontal,tr("PTrate"));
//    total_table_model.setHeaderData(6,Qt::Horizontal,tr("PMrate"));
//    total_table_model.setHeaderData(7,Qt::Horizontal,tr("MTrate"));
//    total_table_model.setHeaderData(8,Qt::Horizontal,tr("Waitrate"));
//    total_table_model.setHeaderData(9,Qt::Horizontal,tr("USCHDOWN4"));
//    total_table_model.setHeaderData(10,Qt::Horizontal,tr("USCHDOWN1"));
//    total_table_model.setHeaderData(11,Qt::Horizontal,tr("SCHDOWN2"));
//    total_table_model.setHeaderData(12,Qt::Horizontal,tr("USCHDOWN2"));
//    total_table_model.setHeaderData(13,Qt::Horizontal,tr("NONSCHED"));
//    total_table_model.setHeaderData(14,Qt::Horizontal,tr("stop_loss(%)"));


//    ui->total_table->setModel(&total_table_model);

//    total_table_model.submit();
//    ui->total_table->horizontalHeader()->hideSection(2);
    QSqlQuery query_total(light_db);
    query_total.exec(query_txt4);
    while(query_total.next()){
        int row_count = ui->total_table->rowCount();
        ui->total_table->insertRow(row_count);
        ui->total_table->setCellWidget(row_count,0,new QLabel(query_total.value("process").toString()));
        ((QLabel *)ui->total_table->cellWidget(row_count,0))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->total_table->setCellWidget(row_count,1,new QLabel(query_total.value("machine_name").toString()));
        ((QLabel *)ui->total_table->cellWidget(row_count,1))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->total_table->setCellWidget(row_count,2,new QLabel(query_total.value("stop_time_calc").toString()));
        ((QLabel *)ui->total_table->cellWidget(row_count,2))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->total_table->setCellWidget(row_count,3,new QLabel(query_total.value("rate").toString()));
        ((QLabel *)ui->total_table->cellWidget(row_count,3))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->total_table->setCellWidget(row_count,4,new QLabel(query_total.value("PTrate").toString()));
        ((QLabel *)ui->total_table->cellWidget(row_count,4))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->total_table->setCellWidget(row_count,5,new QLabel(query_total.value("PMrate").toString()));
        ((QLabel *)ui->total_table->cellWidget(row_count,5))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->total_table->setCellWidget(row_count,6,new QLabel(query_total.value("MTrate").toString()));
        ((QLabel *)ui->total_table->cellWidget(row_count,6))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->total_table->setCellWidget(row_count,7,new QLabel(query_total.value("Waitrate").toString()));
        ((QLabel *)ui->total_table->cellWidget(row_count,7))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->total_table->setCellWidget(row_count,8,new QLabel(query_total.value("USCHDOWN4").toString()));
        ((QLabel *)ui->total_table->cellWidget(row_count,8))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->total_table->setCellWidget(row_count,9,new QLabel(query_total.value("USCHDOWN1").toString()));
        ((QLabel *)ui->total_table->cellWidget(row_count,9))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->total_table->setCellWidget(row_count,10,new QLabel(query_total.value("SCHDOWN2").toString()));
        ((QLabel *)ui->total_table->cellWidget(row_count,10))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->total_table->setCellWidget(row_count,11,new QLabel(query_total.value("USCHDOWN2").toString()));
        ((QLabel *)ui->total_table->cellWidget(row_count,11))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->total_table->setCellWidget(row_count,12,new QLabel(query_total.value("NONSCHED").toString()));
        ((QLabel *)ui->total_table->cellWidget(row_count,12))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->total_table->setCellWidget(row_count,13,new QLabel(query_total.value("stop_loss_per").toString()));
        ((QLabel *)ui->total_table->cellWidget(row_count,13))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }


    if(ui->CB_select_process->currentText()==tr("ALLPRocess")){
        query_txt4 = QString("select process,ROUND(AVG(rate),2) AS rate,ROUND(AVG(PTrate),2) AS PTrate,ROUND(AVG(PMrate),2) AS PMrate,ROUND(AVG(MTrate),2) AS MTrate,ROUND(AVG(Waitrate),2) AS Waitrate,"
                                         "ROUND(AVG(USCHDOWN4),2) AS USCHDOWN4 ,ROUND(AVG(USCHDOWN1),2) AS USCHDOWN1,ROUND(AVG(SCHDOWN2),2) AS SCHDOWN2,ROUND(AVG(USCHDOWN2),2) AS USCHDOWN2,ROUND(AVG(NONSCHED),2) AS NONSCHED ,"
                                         "ROUND(AVG((PTrate+PMrate+MTrate+Waitrate+USCHDOWN4+USCHDOWN1+SCHDOWN2+USCHDOWN2+NONSCHED)),2)AS stop_loss_per  "
                                         "from OI_system_time_2 "
                                         "order by rate asc");
    }else if(ui->CB_select_process->currentText()==tr("deposition")){
        query_txt4 = QString("select process,ROUND(AVG(rate),2) AS rate,ROUND(AVG(PTrate),2) AS PTrate,ROUND(AVG(PMrate),2) AS PMrate,ROUND(AVG(MTrate),2) AS MTrate,ROUND(AVG(Waitrate),2) AS Waitrate,"
                                         "ROUND(AVG(USCHDOWN4),2) AS USCHDOWN4 ,ROUND(AVG(USCHDOWN1),2) AS USCHDOWN1,ROUND(AVG(SCHDOWN2),2) AS SCHDOWN2,ROUND(AVG(USCHDOWN2),2) AS USCHDOWN2,ROUND(AVG(NONSCHED),2) AS NONSCHED ,"
                                         "ROUND(AVG((PTrate+PMrate+MTrate+Waitrate+USCHDOWN4+USCHDOWN1+SCHDOWN2+USCHDOWN2+NONSCHED)),2)AS stop_loss_per  "
                                         "from OI_system_time_2 "
                                         "where process = '%1' order by rate asc").arg(tr("deposition"));
    }else if(ui->CB_select_process->currentText()==tr("light")){
        query_txt4 = QString("select process,ROUND(AVG(rate),2) AS rate,ROUND(AVG(PTrate),2) AS PTrate,ROUND(AVG(PMrate),2) AS PMrate,ROUND(AVG(MTrate),2) AS MTrate,ROUND(AVG(Waitrate),2) AS Waitrate,"
                                         "ROUND(AVG(USCHDOWN4),2) AS USCHDOWN4 ,ROUND(AVG(USCHDOWN1),2) AS USCHDOWN1,ROUND(AVG(SCHDOWN2),2) AS SCHDOWN2,ROUND(AVG(USCHDOWN2),2) AS USCHDOWN2,ROUND(AVG(NONSCHED),2) AS NONSCHED ,"
                                         "ROUND(AVG((PTrate+PMrate+MTrate+Waitrate+USCHDOWN4+USCHDOWN1+SCHDOWN2+USCHDOWN2+NONSCHED)),2)AS stop_loss_per  "
                                         "from OI_system_time_2 "
                                         "where process = '%1' order by rate asc").arg(tr("light"));
    }else if(ui->CB_select_process->currentText()==tr("eatching")){
        query_txt4 = QString("select process,ROUND(AVG(rate),2) AS rate,ROUND(AVG(PTrate),2) AS PTrate,ROUND(AVG(PMrate),2) AS PMrate,ROUND(AVG(MTrate),2) AS MTrate,ROUND(AVG(Waitrate),2) AS Waitrate,"
                                         "ROUND(AVG(USCHDOWN4),2) AS USCHDOWN4 ,ROUND(AVG(USCHDOWN1),2) AS USCHDOWN1,ROUND(AVG(SCHDOWN2),2) AS SCHDOWN2,ROUND(AVG(USCHDOWN2),2) AS USCHDOWN2,ROUND(AVG(NONSCHED),2) AS NONSCHED ,"
                                         "ROUND(AVG((PTrate+PMrate+MTrate+Waitrate+USCHDOWN4+USCHDOWN1+SCHDOWN2+USCHDOWN2+NONSCHED)),2)AS stop_loss_per  "
                                         "from OI_system_time_2 "
                                         "where process = '%1' order by rate asc").arg(tr("eatching"));
    }else if(ui->CB_select_process->currentText()==tr("ALL probe")){
        query_txt4 = QString("select process,ROUND(AVG(rate),2) AS rate,ROUND(AVG(PTrate),2) AS PTrate,ROUND(AVG(PMrate),2) AS PMrate,ROUND(AVG(MTrate),2) AS MTrate,ROUND(AVG(Waitrate),2) AS Waitrate,"
                                         "ROUND(AVG(USCHDOWN4),2) AS USCHDOWN4 ,ROUND(AVG(USCHDOWN1),2) AS USCHDOWN1,ROUND(AVG(SCHDOWN2),2) AS SCHDOWN2,ROUND(AVG(USCHDOWN2),2) AS USCHDOWN2,ROUND(AVG(NONSCHED),2) AS NONSCHED ,"
                                         "ROUND(AVG((PTrate+PMrate+MTrate+Waitrate+USCHDOWN4+USCHDOWN1+SCHDOWN2+USCHDOWN2+NONSCHED)),2)AS stop_loss_per  "
                                         "from OI_system_time_2 "
                                         "where process LIKE '%1%' order by rate asc").arg(tr("ALL probe"));
    }

    query_total.exec(query_txt4);
    qDebug()<<query_total.lastQuery();
    qDebug()<<query_total.lastError().text();
    int row_count = ui->total_table->rowCount();
    query_total.next();
    ui->total_table->insertRow(row_count);
    ui->total_table->setCellWidget(row_count,0,new QLabel(tr("AVG")));
    ((QLabel *)ui->total_table->cellWidget(row_count,0))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->total_table->setCellWidget(row_count,1,new QLabel(""));
    ((QLabel *)ui->total_table->cellWidget(row_count,1))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->total_table->setCellWidget(row_count,2,new QLabel(""));
    ((QLabel *)ui->total_table->cellWidget(row_count,2))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->total_table->setCellWidget(row_count,3,new QLabel(query_total.value("rate").toString()));
    ((QLabel *)ui->total_table->cellWidget(row_count,3))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ((QLabel *)ui->total_table->cellWidget(row_count,3))->setStyleSheet(QString("background-color: #ff5500"));
    ui->total_table->setCellWidget(row_count,4,new QLabel(query_total.value("PTrate").toString()));
    ((QLabel *)ui->total_table->cellWidget(row_count,4))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ((QLabel *)ui->total_table->cellWidget(row_count,4))->setStyleSheet(QString("background-color: #ff5500"));
    ui->total_table->setCellWidget(row_count,5,new QLabel(query_total.value("PMrate").toString()));
    ((QLabel *)ui->total_table->cellWidget(row_count,5))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ((QLabel *)ui->total_table->cellWidget(row_count,5))->setStyleSheet(QString("background-color: #ff5500"));
    ui->total_table->setCellWidget(row_count,6,new QLabel(query_total.value("MTrate").toString()));
    ((QLabel *)ui->total_table->cellWidget(row_count,6))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ((QLabel *)ui->total_table->cellWidget(row_count,6))->setStyleSheet(QString("background-color: #ff5500"));
    ui->total_table->setCellWidget(row_count,7,new QLabel(query_total.value("Waitrate").toString()));
    ((QLabel *)ui->total_table->cellWidget(row_count,7))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ((QLabel *)ui->total_table->cellWidget(row_count,7))->setStyleSheet(QString("background-color: #ff5500"));
    ui->total_table->setCellWidget(row_count,8,new QLabel(query_total.value("USCHDOWN4").toString()));
    ((QLabel *)ui->total_table->cellWidget(row_count,8))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ((QLabel *)ui->total_table->cellWidget(row_count,8))->setStyleSheet(QString("background-color: #ff5500"));
    ui->total_table->setCellWidget(row_count,9,new QLabel(query_total.value("USCHDOWN1").toString()));
    ((QLabel *)ui->total_table->cellWidget(row_count,9))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ((QLabel *)ui->total_table->cellWidget(row_count,9))->setStyleSheet(QString("background-color: #ff5500"));
    ui->total_table->setCellWidget(row_count,10,new QLabel(query_total.value("SCHDOWN2").toString()));
    ((QLabel *)ui->total_table->cellWidget(row_count,10))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ((QLabel *)ui->total_table->cellWidget(row_count,10))->setStyleSheet(QString("background-color: #ff5500"));
    ui->total_table->setCellWidget(row_count,11,new QLabel(query_total.value("USCHDOWN2").toString()));
    ((QLabel *)ui->total_table->cellWidget(row_count,11))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ((QLabel *)ui->total_table->cellWidget(row_count,11))->setStyleSheet(QString("background-color: #ff5500"));
    ui->total_table->setCellWidget(row_count,12,new QLabel(query_total.value("NONSCHED").toString()));
    ((QLabel *)ui->total_table->cellWidget(row_count,12))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ((QLabel *)ui->total_table->cellWidget(row_count,12))->setStyleSheet(QString("background-color: #ff5500"));
    ui->total_table->setCellWidget(row_count,13,new QLabel(query_total.value("stop_loss_per").toString()));
    ((QLabel *)ui->total_table->cellWidget(row_count,13))->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ((QLabel *)ui->total_table->cellWidget(row_count,13))->setStyleSheet(QString("background-color: #ff5500"));



    chart_search();

    QString query_txt6 = QString("select machine_name,ROUND(rate,2)AS'rate' from OI_system_time_2 where process = '%1' order by rate asc ").arg(tr("deposition"));
    depostion_deatil_model.setQuery(query_txt6,light_db);
    ui->depostion_deatil_view->setModel(&depostion_deatil_model);
    depostion_deatil_model.submit();

    QString query_txt7 = QString("select machine_name,ROUND(rate,2)AS'rate' from OI_system_time_2 where process = '%1' order by rate asc ").arg(tr("light"));
    light_deatil_model.setQuery(query_txt7,light_db);
    ui->light_detail_view->setModel(&light_deatil_model);
    light_deatil_model.submit();

    QString query_txt8 = QString("select machine_name,ROUND(rate,2)AS'rate' from OI_system_time_2 where process = '%1' order by rate asc ").arg(tr("eatching"));
    eatch_deatil_model.setQuery(query_txt8,light_db);
    ui->eatch_detail_view->setModel(&eatch_deatil_model);
    eatch_deatil_model.submit();

    QString query_txt9 = QString("select machine_name,ROUND(rate,2)AS'rate' from OI_system_time_2 where process = '%1' OR process = '%2' order by rate asc ")
                                .arg(tr("ALL probe")).arg(tr("probe1"));

    probe_deatil_model.setQuery(query_txt9,light_db);
    ui->probe_detail_view->setModel(&probe_deatil_model);
    probe_deatil_model.submit();



}

void MainWindow::on_calc(QString select_machine)
{
//    light_db.close();
    QSqlQuery query1(my_mesdb);
    QSqlQuery query2(my_mesdb);
    QSqlQuery query3(my_mesdb);
    QString query_txt5;
    QDateTime start_time;
    start_time.setDate(ui->research_start_date->date());
    start_time.setTime(QTime(8,0,0));
    QString start_time_str = start_time.toString("yyyy-MM-dd hh:mm:ss");
    QDateTime end_time;
    end_time.setDate(ui->research_end_date->date().addDays(1));
    end_time.setTime(QTime(7,59,59));
    QString end_time_str = end_time.toString("yyyy-MM-dd hh:mm:ss");


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
    int minute = (secs%3600)/60;
    int sec = (secs%3600)%60;
    QString reslut = QString("%1:%2:%3").arg(hour).arg(minute).arg(sec);
    return reslut;
}

void MainWindow::on_show_detail_total_clicked()
{
    on_calc_btn_clicked();
}

void MainWindow::on_total_table_clicked(const QModelIndex &index)
{
    QString machine_name;
    QLabel *temp_label = (QLabel *)ui->total_table->cellWidget(index.row(),1);
    machine_name = temp_label->text();
    on_calc(machine_name);
}

void MainWindow::on_research_start_date_dateTimeChanged(const QDateTime &dateTime)
{
    QDateTime start_time;
    start_time.setDate(ui->research_start_date->date());
    start_time.setTime(QTime(8,0,0));
    QString start_time_str = start_time.toString("yyyy-MM-dd hh:mm:ss");

    ui->LA_start_time->setText(start_time_str);

}

void MainWindow::on_research_end_date_dateTimeChanged(const QDateTime &dateTime)
{
    QDateTime end_time;
    end_time.setDate(ui->research_end_date->date().addDays(1));
    end_time.setTime(QTime(7,59,59));
    QString end_time_str = end_time.toString("yyyy-MM-dd hh:mm:ss");
    ui->LA_EndTime->setText(end_time_str);
}

void MainWindow::on_detail_table_clicked(const QModelIndex &index)
{
     int row = index.row();
     QString stoptime_str=index.model()->index(row,3).data().toString();
     QString runtime_str=index.model()->index(row,4).data().toString();
     QString query_txt  = QString("select remove_time,Round(remove_sec/60)AS'remove_min',content from OI_system_remove_event_time "
                                  "where remove_time between '%1' AND '%2'")
                                 .arg(stoptime_str)
                                 .arg(runtime_str);
    rest_table_model.setQuery(query_txt,my_mesdb);
    ui->rest_time_view->setModel(&rest_table_model);
    rest_table_model.submit();

    ui->rest_time_view->horizontalHeader()->resizeSection(0,150);
    ui->rest_time_view->horizontalHeader()->resizeSection(1,100);
    ui->rest_time_view->horizontalHeader()->resizeSection(2,100);

    rest_table_model.setHeaderData(0,Qt::Horizontal,tr("restime"));
    rest_table_model.setHeaderData(1,Qt::Horizontal,tr("removemin"));
    rest_table_model.setHeaderData(2,Qt::Horizontal,tr("content"));

}

void MainWindow::on_resttime_setup_clicked()
{
    rest_time_widget *event_widget = new rest_time_widget();
    event_widget->show();
}

void MainWindow::chart_search()
{
    ui->oi_total_ratio_widget->setDb(light_db);
    ui->oi_total_ratio_widget->chart_update();
}

void MainWindow::on_detail_chart_seartch_btn_clicked()
{
    foreach(QModelIndex index,ui->depostion_deatil_view->selectionModel()->selectedIndexes()){
        qDebug() << index.row();
    }
}
