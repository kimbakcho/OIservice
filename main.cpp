#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>
#include <machine_statue_data.h>
MainWindow *m_window;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<machine_statue_data>("machine_statue_data");
    QTranslator qtTranslator;
    qtTranslator.load(":/lang/lang_oi_ko.qm");
    a.installTranslator(&qtTranslator);
    MainWindow w;
    w.show();

    return a.exec();
}
