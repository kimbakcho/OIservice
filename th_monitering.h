#ifndef TH_MONITERING_H
#define TH_MONITERING_H

#include <QObject>
#include <QThread>
#include <machine_statue_data.h>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#define DBID "EIS"
#define DBPW "wisolfab!"
class Th_monitering : public QThread
{
    Q_OBJECT
public:
    explicit Th_monitering(QVector<machine_statue_data> datalist);
    QVector<machine_statue_data> datalist;
    QSqlDatabase ms_mesdb;

private:
    void run();

signals:
    void send_listdata(machine_statue_data data);

public slots:
};

#endif // TH_MONITERING_H
