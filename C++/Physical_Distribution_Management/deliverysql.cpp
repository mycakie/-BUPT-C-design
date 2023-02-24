#include "deliverysql.h"

#include <QMessageBox>
#include <QtDebug>
#include <QCoreApplication>
#include <QTime>

deliverysql * deliverysql::ptrdSql = nullptr ;
deliverysql::deliverysql(QObject *parent): QObject(parent)
{


}

void deliverysql::init()
{
    if (QSqlDatabase::drivers().isEmpty())
        qDebug()<<"No database drivers found";
    m_db = QSqlDatabase::addDatabase("QSQLITE","MyConnection");

    m_db.setDatabaseName("D:\\database.db");
    if (!m_db.open())
        qDebug()<<"db cannot be opened" ;

}

quint32 deliverysql::getDelCnt()
{
    QSqlQuery sql(m_db);
    sql.exec("select count(id) from delivery;");
    quint32 uiCnt = 0;
    while(sql.next()){
        uiCnt = sql.value(0).toUInt();
    }
    return uiCnt;
}

QList<DeliveryInfo> deliverysql::getPageDelivery(quint32 page,quint32 cnt)
{
    QList<DeliveryInfo> l;
    QSqlQuery sql(m_db);
    QString strsql = QString("select * from delivery order by id limit %1 offset %2").
            arg(cnt).arg(page*cnt);
    sql.exec(strsql);
    DeliveryInfo info;
    while(sql.next()){
        info.id = sql.value(0).toUInt();
        info.number = sql.value(1).toString();
        info.sender = sql.value(2).toString();
        info.receiver = sql.value(3).toString();
        info.sendtime = sql.value(4).toString();
        info.receivetime = sql.value(5).toString();
        info.status = sql.value(6).toString();
        info.detail = sql.value(7).toString();
        l.append(info);
    }
    return l;

}

bool deliverysql::addDel(DeliveryInfo info)
{

    QString str;                 /*声明用来保存随机字符串的str*/
    char c;                     /*声明字符c，用来保存随机生成的字符*/
    /*循环向字符串中添加随机生成的字符*/
    for(int idx = 0;idx < 2;idx ++)
    {
        /*rand()%26是取余，余数为0~25加上'a',就是字母a~z,详见asc码表*/
        c = 'A' + rand()%26;
        str.push_back(c);       /*push_back()是string类尾插函数。这里插入随机字符c*/
    }
    for(int j = 0;j < 10;j ++)
    {
        /*rand()%10是取余，余数为0~9加上'1',就是数字0~9,详见asc码表*/
        c = '0' + rand()%10;
        str.push_back(c);       /*push_back()是string类尾插函数。这里插入随机字符c*/
    }
    QSqlQuery sql(m_db);
    QString strSql = QString("insert into delivery values (null,'%1','%2','%3','%4','%5','%6','%7')").
            arg(str).
            arg(info.sender).
            arg(info.receiver).
            arg(info.sendtime).
            arg("未送达").
            arg("待签收").
            arg(info.detail);
    return sql.exec(strSql);
}

bool deliverysql::updateDelInfo(DeliveryInfo info)
{
    QString str = "已签收";
    QSqlQuery sql(m_db);
    QString time = QDate::currentDate().toString("yyyy-MM-dd");
    QString strSql = QString("update delivery set status  = '%1',receivetime = '%2' where number = '%3' ").
            arg(str).
            arg(time).
            arg(info.number);
   return sql.exec(strSql);

}
