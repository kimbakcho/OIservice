#ifndef MACHINE_STATUE_DATA_H
#define MACHINE_STATUE_DATA_H

#include <QApplication>
#include <QDebug>
#include <QColor>
class machine_statue_data
{
public:
    machine_statue_data();
    QString machine_name;
    QString machine_code;
    QString current_event;
    QString colorstr;
    QColor color;
    QString getMachine_name() const;
    void setMachine_name(const QString &value);
    QString getMachine_code() const;
    void setMachine_code(const QString &value);
    QString getColorstr() const;
    void setColorstr(const QString &value);
    QColor getColor() const;
    void setColor(const QColor &value);
    QString getCurrent_event() const;
    void setCurrent_event(const QString &value);
};

#endif // MACHINE_STATUE_DATA_H
