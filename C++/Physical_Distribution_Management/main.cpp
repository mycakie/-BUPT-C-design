#include "mainwindow.h"

#include <QApplication>
#include "connnection.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!createConnection()) return 1;//建立数据库链接
    mainwindow w;
    w.show();
    return a.exec();
}
