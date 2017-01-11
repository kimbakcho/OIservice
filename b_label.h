#ifndef B_LABEL_H
#define B_LABEL_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <QMenu>
#include <QDebug>
#include <login_form.h>
class B_Label : public QLabel
{
    Q_OBJECT
public:
    explicit B_Label(QString str);
    explicit B_Label(QString str, QString machine_name, QString machine_code, QString process);
    QString machine_code;
    QString machine_name;
    QString process;
    QMenu menu;
    QString getMachine_code() const;
    void setMachine_code(const QString &value);

    QString getMachine_name() const;
    void setMachine_name(const QString &value);


    QString getProcess() const;
    void setProcess(const QString &value);

private:
    void mousePressEvent(QMouseEvent *ev);

signals:

public slots:
    void RUN_slot();
    void ENGR1_slot();
    void SCHDOWN1_slot();
    void USCHDOWN3_slot();
    void WAIT_slot();
};

#endif // B_LABEL_H
