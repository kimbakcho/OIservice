#ifndef ADD_MACHINE_DIALOG_H
#define ADD_MACHINE_DIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>
#define DBID "EIS"
#define DBPW "wisolfab!"


namespace Ui {
class add_machine_dialog;
}

class add_machine_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit add_machine_dialog(QWidget *parent = 0);
    QSqlDatabase my_mesdb;
    ~add_machine_dialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::add_machine_dialog *ui;
};

#endif // ADD_MACHINE_DIALOG_H
