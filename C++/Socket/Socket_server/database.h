#ifndef FILE_H
#define FILE_H
#include <QFile>
#include <QMessageBox>
#include <QByteArray>
#include <QDebug>
#include "mainwindow.h"

//发送数据
void sendFile(MainWindow *m)
{
    QFile file("D:\\data.db");
    //打开文件
    bool ok = file.open(QIODevice::ReadOnly);
    if(!ok){
        QMessageBox::critical(m,"错误","文件读取出错");
        return;
    }
    //开始发文件
    QByteArray buf;
    buf = file.readAll();
    m->conn->write(buf);
    file.close();
}
//接收数据写入文件
void receiveFile(MainWindow *m, QByteArray a, bool flag)
{
    QFile file("D:\\data.db");
    //打开文件
    bool ok;
    if(!flag){
        ok = file.open(QIODevice::WriteOnly|QIODevice::Truncate);
    }else{
        ok = file.open(QIODevice::WriteOnly|QIODevice::Append);
    }
    if(!ok){
        QMessageBox::critical(m,"错误","文件读取出错");
        return;
    }
    //开始写文件
    int len=file.write(a);
    qDebug()<<len;
    file.close();
    //回复客户端接收
    m->conn->write("yes");
}

#endif // FILE_H
