#include "oi_data.h"

OI_data::OI_data()
{

}

QTime OI_data::getLost_time() const
{
    return lost_time;
}

void OI_data::setLost_time(const QTime &value)
{
    lost_time = value;
}

QString OI_data::getStop_name() const
{
    return stop_name;
}

void OI_data::setStop_name(const QString &value)
{
    stop_name = value;
}

QString OI_data::getRun_name() const
{
    return run_name;
}

void OI_data::setRun_name(const QString &value)
{
    run_name = value;
}

QString OI_data::getStop_data() const
{
    return stop_data;
}

void OI_data::setStop_data(const QString &value)
{
    stop_data = value;
}

QDateTime OI_data::getRun_time() const
{
    return run_time;
}

void OI_data::setRun_time(const QDateTime &value)
{
    run_time = value;
}

QDateTime OI_data::getStop_time() const
{
    return stop_time;
}

void OI_data::setStop_time(const QDateTime &value)
{
    stop_time = value;
}

QString OI_data::getMachine_code() const
{
    return machine_code;
}

void OI_data::setMachine_code(const QString &value)
{
    machine_code = value;
}

QString OI_data::getMachine_name() const
{
    return machine_name;
}

void OI_data::setMachine_name(const QString &value)
{
    machine_name = value;
}

QString OI_data::getProcess() const
{
    return process;
}

void OI_data::setProcess(const QString &value)
{
    process = value;
}
