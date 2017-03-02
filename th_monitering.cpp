#include "th_monitering.h"

Th_monitering::Th_monitering(QVector<machine_statue_data> datalist)
{
    this->datalist = datalist;
    QString msdb_name = QString("MS_MESDB_%1").arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"));
    while(true){
        if(!ms_mesdb.contains(msdb_name)){
            ms_mesdb = QSqlDatabase::addDatabase("QODBC",msdb_name);
            QString serverinfo = "DRIVER={SQL Server};Server=10.20.10.221;Database=MESDB;Uid=fabview;Port=1433;Pwd=fabview";
            ms_mesdb.setDatabaseName(serverinfo);
            if(!ms_mesdb.open()){
                qDebug()<<"fasle";
                qDebug()<<ms_mesdb.lastError().text();
            }else {
                qDebug()<<"open";
            }
            break;
        }else {
            msdb_name.append("S");
        }
    }
}

void Th_monitering::run()
{
    QSqlQuery query(ms_mesdb);
    bool USCHDOWN3_flag = false;
    while(!isInterruptionRequested()){
         int i =0;
        QString append_txt;
        QVector<machine_statue_data> current_datalist;
        for(int i=0;i<datalist.count();i++){
            if(i==datalist.count()-1){
                append_txt = append_txt.append(QString("'%1'").arg(datalist.at(i).getMachine_code()));
            }else {
                append_txt = append_txt.append(QString("'%1',").arg(datalist.at(i).getMachine_code()));
            }
        }
        query.exec(QString("select EQUIPMENT_ID,EQUIPMENT_NAME,LAST_EVENT_ID from NM_EQUIPMENT (NOLOCK) where EQUIPMENT_ID IN(%1) AND DELETE_FLAG = 'N'").arg(append_txt));
        while(query.next()){
            i++;
            machine_statue_data temp_data;
            temp_data.setMachine_code(query.value("EQUIPMENT_ID").toString());
            QString event_data= query.value("LAST_EVENT_ID").toString();
            if(event_data=="RUN"){
                temp_data.setCurrent_event(tr("RUN"));
                temp_data.setColor(QColor("#80ff80"));
            }else if(event_data=="ENGR1"){
                temp_data.setCurrent_event(tr("ENGR1"));
                temp_data.setColor(QColor("#8080ff"));
            }else if(event_data=="SCHDOWN1"){
                temp_data.setCurrent_event(tr("SCHDOWN1"));
                temp_data.setColor(QColor("#ff80ff"));
            }else if(event_data=="USCHDOWN3"){
                temp_data.setCurrent_event(tr("USCHDOWN3"));
                if(!USCHDOWN3_flag){
                    temp_data.setColor(QColor("#ff1f21"));
                }else {
                    temp_data.setColor(QColor("#FF9090"));
                }
            }else if(event_data=="WAIT"){
                temp_data.setCurrent_event(tr("WAIT"));
                temp_data.setColor(QColor("#ffff80"));
            }else if(event_data=="SCHDOWN2"){
                temp_data.setCurrent_event(tr("SCHDOWN2"));
                temp_data.setColor(QColor("#ffff80"));
            }else if(event_data=="USCHDOWN4"){
                temp_data.setCurrent_event(tr("USCHDOWN4"));
                temp_data.setColor(QColor("#ffff80"));
            }else if(event_data=="USCHDOWN1"){
                temp_data.setCurrent_event(tr("USCHDOWN1"));
                temp_data.setColor(QColor("#ffff80"));
            }else if(event_data=="USCHDOWN2"){
                temp_data.setCurrent_event(tr("USCHDOWN2"));
                temp_data.setColor(QColor("#ffff80"));
            }else if(event_data=="NONSCHED"){
                temp_data.setCurrent_event(tr("NONSCHED"));
                temp_data.setColor(QColor("#ffff80"));
            }else {
                temp_data.setCurrent_event(tr("dontknow"));
                temp_data.setColor(QColor("#ffffff"));
            }
            emit send_listdata(temp_data);
            current_datalist.append(temp_data);

        }

        if(!USCHDOWN3_flag){
            USCHDOWN3_flag=true;
        }else {
            USCHDOWN3_flag = false;
        }
        if (i == 0){
            QString msdb_name = QString("MS_MESDB_%1").arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"));
            while(true){
                ms_mesdb.close();
                msdb_name.append("S");
                if(!ms_mesdb.contains(msdb_name)){
                    ms_mesdb = QSqlDatabase::addDatabase("QODBC",msdb_name);
                    QString serverinfo = "DRIVER={SQL Server};Server=10.20.10.221;Database=MESDB;Uid=fabview;Port=1433;Pwd=fabview";
                    ms_mesdb.setDatabaseName(serverinfo);

                        if(!ms_mesdb.open()){
                            qDebug()<<"fasle";
                            qDebug()<<ms_mesdb.lastError().text();
                        }else {
                            qDebug()<<"open";
                        }

                    break;
                }else {
                    msdb_name.append("S");
                }
            }
        }
        QThread::sleep(1);

    }
    qDebug()<<"delete";

}
