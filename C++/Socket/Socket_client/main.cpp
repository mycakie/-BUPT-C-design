#include "mainwindow.h"
#include <QApplication>
#include <QSqlError>
#include <QDebug>
#include <windows.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindow *w=new mainwindow;
    w->show();
    int ret=a.exec();
    delete w;
    return ret;
}
