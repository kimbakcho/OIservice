#ifndef B_TABLE_WIDGET_H
#define B_TABLE_WIDGET_H

#include <QObject>
#include <QTableView>
#include <QKeyEvent>
#include <QApplication>
#include <QClipboard>
class b_table_widget : public QTableView
{
    Q_OBJECT
public:
    explicit b_table_widget(QObject *parent = 0);
private:
   void keyPressEvent(QKeyEvent *event);

signals:

public slots:
};

#endif // B_TABLE_WIDGET_H
