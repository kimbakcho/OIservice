#include "b_label.h"

B_Label::B_Label(QString str): QLabel(str)
{

}
B_Label::B_Label(QString str, QString machine_name, QString machine_code,QString process): QLabel(str)
{
    this->machine_name = machine_name;
    this->machine_code = machine_code;
    this->process = process;
    menu.addAction(tr("RUN"),this,SLOT(RUN_slot()));
    menu.addAction(tr("ENGR1"),this,SLOT(ENGR1_slot()));
    menu.addAction(tr("SCHDOWN1"),this,SLOT(SCHDOWN1_slot()));
    menu.addAction(tr("USCHDOWN3"),this,SLOT(USCHDOWN3_slot()));
    menu.addAction(tr("WAIT"),this,SLOT(WAIT_slot()));
    this->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    QFont font = this->font();
    font.setBold(true);
    this->setFont(font);
}

QString B_Label::getProcess() const
{
    return process;
}

void B_Label::setProcess(const QString &value)
{
    process = value;
}


QString B_Label::getMachine_name() const
{
    return machine_name;
}

void B_Label::setMachine_name(const QString &value)
{
    machine_name = value;
}

QString B_Label::getMachine_code() const
{
    return machine_code;
}

void B_Label::setMachine_code(const QString &value)
{
    machine_code = value;
}

void B_Label::mousePressEvent(QMouseEvent *ev)
{
    QLabel::mousePressEvent(ev);
    if(ev->button()==Qt::RightButton){
        menu.exec(QCursor::pos());
    }
}

void B_Label::RUN_slot()
{
    login_form *from = new login_form("RUN",machine_code,machine_name,process);
    from->show();
}

void B_Label::ENGR1_slot()
{
    login_form *from = new login_form("ENGR1",machine_code,machine_name,process);
    from->show();
}

void B_Label::SCHDOWN1_slot()
{
    login_form *from = new login_form("SCHDOWN1",machine_code,machine_name,process);
    from->show();
}

void B_Label::USCHDOWN3_slot()
{
    login_form *from = new login_form("USCHDOWN3",machine_code,machine_name,process);
    from->show();
}

void B_Label::WAIT_slot()
{
    login_form *from = new login_form("WAIT",machine_code,machine_name,process);
    from->show();
}
