#ifndef B_TABLE_WIDGET2_H
#define B_TABLE_WIDGET2_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QKeyEvent>
#include <QApplication>
#include <QClipboard>
#include <QLabel>
class B_table_widget2 : public QTableWidget
{
    Q_OBJECT
public:
    B_table_widget2(QObject *parent = 0);
private:
   void keyPressEvent(QKeyEvent *event);
};

#endif // B_TABLE_WIDGET2_H
