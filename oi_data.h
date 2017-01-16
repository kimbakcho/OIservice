#ifndef OI_DATA_H
#define OI_DATA_H

#include <QObject>
#include <QDatetime>

class OI_data
{
public:
    OI_data();
    QString process;
    QString machine_name;
    QString machine_code;
    QDateTime stop_time;
    QDateTime run_time;
    QString stop_data;
    QString run_name;
    QString stop_name;
    QTime lost_time;

    QString getProcess() const;
    void setProcess(const QString &value);
    QString getMachine_name() const;
    void setMachine_name(const QString &value);
    QString getMachine_code() const;
    void setMachine_code(const QString &value);
    QDateTime getStop_time() const;
    void setStop_time(const QDateTime &value);
    QDateTime getRun_time() const;
    void setRun_time(const QDateTime &value);
    QString getStop_data() const;
    void setStop_data(const QString &value);
    QString getRun_name() const;
    void setRun_name(const QString &value);
    QString getStop_name() const;
    void setStop_name(const QString &value);
    QTime getLost_time() const;
    void setLost_time(const QTime &value);
};

#endif // OI_DATA_H
