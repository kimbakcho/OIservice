#ifndef MODIFY_MACHINE_DIALOG_H
#define MODIFY_MACHINE_DIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>
#define DBID "EIS"
#define DBPW "wisolfab!"

namespace Ui {
class modify_machine_dialog;
}

class modify_machine_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit modify_machine_dialog(QWidget *parent = 0);
    explicit modify_machine_dialog(QString process,QString machine_name,QString machine_code,QWidget *parent = 0);
    QSqlDatabase my_mesdb;
    QString process;
    QString machine_name;
    QString machine_code;
    ~modify_machine_dialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::modify_machine_dialog *ui;
};

#endif // MODIFY_MACHINE_DIALOG_H
