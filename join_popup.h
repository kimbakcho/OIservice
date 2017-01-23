#ifndef JOIN_POPUP_H
#define JOIN_POPUP_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
namespace Ui {
class join_popup;
}

class join_popup : public QDialog
{
    Q_OBJECT

public:
    explicit join_popup(QWidget *parent = 0);
    QSqlDatabase my_mesdb;
    ~join_popup();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::join_popup *ui;
};

#endif // JOIN_POPUP_H
