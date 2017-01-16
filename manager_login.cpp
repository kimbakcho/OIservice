#include "manager_login.h"
#include "ui_manager_login.h"

manager_login::manager_login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manager_login)
{
    ui->setupUi(this);

}

manager_login::~manager_login()
{
    delete ui;
}

void manager_login::on_buttonBox_accepted()
{
    if(ui->LE_Passwrod->text()=="fab!wisol!"){
        return;
    }else {
        this->reject();
    }
}
