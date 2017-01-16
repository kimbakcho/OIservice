#ifndef MANAGER_LOGIN_H
#define MANAGER_LOGIN_H

#include <QDialog>

namespace Ui {
class manager_login;
}

class manager_login : public QDialog
{
    Q_OBJECT

public:
    explicit manager_login(QWidget *parent = 0);
    ~manager_login();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::manager_login *ui;
};

#endif // MANAGER_LOGIN_H
