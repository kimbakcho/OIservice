#include "mainwindow.h"
#include "ui_mainwindow.h"
extern MainWindow *m_window;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_window = this;

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
    Th_monitering *depostion_thread = new Th_monitering(depostiondata_list);
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
    Th_monitering *light_thread = new Th_monitering(lightdata_list);
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
    Th_monitering *eatching_thread = new Th_monitering(eatchingdata_list);
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
    Th_monitering *probe_thread = new Th_monitering(probedata_list);
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
    Th_monitering *probe1_thread = new Th_monitering(probe1data_list);
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
}

void MainWindow::on_light_listview_clicked(const QModelIndex &index)
{
    current_machine_name = ((QLabel *)ui->light_listview->cellWidget(index.row(),0))->text();
    current_machine_code = ((QLabel *)ui->light_listview->cellWidget(index.row(),2))->text();
    current_process = tr("light");
}

void MainWindow::on_eatching_listview_clicked(const QModelIndex &index)
{
    current_machine_name = ((QLabel *)ui->eatching_listview->cellWidget(index.row(),0))->text();
    current_machine_code = ((QLabel *)ui->eatching_listview->cellWidget(index.row(),2))->text();
    current_process = tr("eatching");
}

void MainWindow::on_probe_listview_clicked(const QModelIndex &index)
{
    current_machine_name = ((QLabel *)ui->probe_listview->cellWidget(index.row(),0))->text();
    current_machine_code = ((QLabel *)ui->probe_listview->cellWidget(index.row(),2))->text();
    current_process = tr("ALL probe");
}

void MainWindow::on_probe1_listview_clicked(const QModelIndex &index)
{
    current_machine_name = ((QLabel *)ui->probe1_listview->cellWidget(index.row(),0))->text();
    current_machine_code = ((QLabel *)ui->probe1_listview->cellWidget(index.row(),2))->text();
    current_process = tr("ALL probe");
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
