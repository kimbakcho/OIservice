#include "machine_list_item.h"
#include "ui_machine_list_item.h"

machine_list_item::machine_list_item(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::machine_list_item)
{
    ui->setupUi(this);
}

machine_list_item::~machine_list_item()
{
    delete ui;
}
