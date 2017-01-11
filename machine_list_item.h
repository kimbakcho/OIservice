#ifndef MACHINE_LIST_ITEM_H
#define MACHINE_LIST_ITEM_H

#include <QWidget>

namespace Ui {
class machine_list_item;
}

class machine_list_item : public QWidget
{
    Q_OBJECT

public:
    explicit machine_list_item(QWidget *parent = 0);
    ~machine_list_item();

private:
    Ui::machine_list_item *ui;
};

#endif // MACHINE_LIST_ITEM_H
