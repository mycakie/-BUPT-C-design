#ifndef CHANGEFILE_H
#define CHANGEFILE_H

#include <QFile>
#include <QMessageBox>
#include <QInputDialog>
#include <QDir>
#include <QStringList>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include <QTextStream>
#include "mainwindow.h"

void changeFile(int index, int type, mainwindow *m, QString text){
    QString path;
    if(index==0){
        path="D:\\userdata\\user.txt";
    }
    else if(index==1){
        path="D:\\userdata\\manager.txt";
    }
    else
        path="D:\\userdata\\courier.txt";
    //读取文件，将文件按行分开
    QFile readfile(path);
    if (!readfile.open(QIODevice::ReadOnly | QIODevice::Text)){
         QMessageBox::critical(m,"错误","文件读取出错");
         return;
    }
    QTextStream stream(&readfile);
    QString strall=stream.readAll();
    QStringList strlist=strall.split("\n"); //将文件流按行分开
    readfile.close();
    //重写文件
    QFile writefile(path);
    if (!writefile.open(QIODevice::WriteOnly | QIODevice::Text)){
         QMessageBox::critical(m,"错误","文件读取出错");
         return;
    }
    QTextStream stream1(&writefile);
    if(index==0){
        for(int i=0;i<strlist.count();i++){
            QString line=strlist.at(i);
            if(line.section(" ",0,0)==m->pr->account){
                if(type==1){
                    stream1<<m->pr->account<<" "<<text<<" "<<line.section(" ",2,2)<<endl; //替换密码
                }else{
                    stream1<<m->pr->account<<" "<<line.section(" ",1,1)<<" "<<text<<endl; //替换余额
                }
            }else{
                stream1<<line<<endl;
            }
        }
    }
    else if(index==1){
        stream1<<"admin"<<" "<<12345<<" "<<text;
    }
    else{
        for(int i=0;i<strlist.count();i++){
            QString line=strlist.at(i);
            if(line.section(" ",0,0)==m->pr->account){
                stream1<<m->pr->account<<" "<<line.section(" ",1,1)<<" "<<text<<endl; //替换余额
            }else{
                stream1<<line<<endl;
            }
        }
    }
    writefile.close();
}

#endif // CHANGEFILE_H
