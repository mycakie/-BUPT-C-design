#include "couriersql.h"

#include <QMessageBox>
#include <QtDebug>
#include <QCoreApplication>

couriersql * couriersql::ptrcSql = nullptr ;
couriersql::couriersql(QObject *parent): QObject(parent)
{

}
void couriersql::init()
{
    if (QSqlDatabase::drivers().isEmpty())
        qDebug()<<"No database drivers found";
    m_db = QSqlDatabase::addDatabase("QSQLITE");

    m_db.setDatabaseName("D:\\database.db");
    if (!m_db.open())
        qDebug()<<"db cannot be opened" ;
}

quint32 couriersql::getCourierCnt()
{
    QSqlQuery sql(m_db);
    sql.exec("select count(id) from courier;");
    quint32 uiCnt = 0;
    while(sql.next()){
        uiCnt = sql.value(0).toUInt();
    }
    return uiCnt;
}

QList<CourierInfo> couriersql::getPageCourier(quint32 page,quint32 cnt)
{
    QList<CourierInfo> l;
    QSqlQuery sql(m_db);
    QString strsql = QString("select * from courier order by id limit %1 offset %2").
            arg(cnt).arg(page*cnt);
    sql.exec(strsql);
    CourierInfo info;
    while(sql.next()){
        info.id = sql.value(0).toUInt();
        info.name = sql.value(1).toString();
        info.phonenumber=sql.value(2).toString();
        info.account = sql.value(3).toString();
        l.append(info);
    }
    return l;

}

bool couriersql::addCourier(CourierInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("insert into user values (null,'%1','%2','%3')").
            arg(info.name).
            arg(info.phonenumber).
            arg(info.account);
    return sql.exec(strSql);
}
