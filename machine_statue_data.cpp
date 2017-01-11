#include "machine_statue_data.h"

machine_statue_data::machine_statue_data()
{

}

QString machine_statue_data::getCurrent_event() const
{
    return current_event;
}

void machine_statue_data::setCurrent_event(const QString &value)
{
    current_event = value;
}

QColor machine_statue_data::getColor() const
{
    return color;
}

void machine_statue_data::setColor(const QColor &value)
{
    color = value;
}

QString machine_statue_data::getColorstr() const
{
    return colorstr;
}

void machine_statue_data::setColorstr(const QString &value)
{
    colorstr = value;
}

QString machine_statue_data::getMachine_code() const
{
    return machine_code;
}

void machine_statue_data::setMachine_code(const QString &value)
{
    machine_code = value;
}

QString machine_statue_data::getMachine_name() const
{
    return machine_name;
}

void machine_statue_data::setMachine_name(const QString &value)
{
    machine_name = value;
}
