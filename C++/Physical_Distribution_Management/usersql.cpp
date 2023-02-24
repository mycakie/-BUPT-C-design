#include "usersql.h"
#include <QMessageBox>
#include <QtDebug>
#include <QCoreApplication>

usersql * usersql::ptruSql = nullptr ;
usersql::usersql(QObject *parent): QObject(parent)
{

}
void usersql::init()
{
    if (QSqlDatabase::drivers().isEmpty())
        qDebug()<<"No database drivers found";
    m_db = QSqlDatabase::addDatabase("QSQLITE");

    m_db.setDatabaseName("D:\\database.db");
    if (!m_db.open())
        qDebug()<<"db cannot be opened" ;
}

quint32 usersql::getUserCnt()
{
    QSqlQuery sql(m_db);
    sql.exec("select count(id) from user;");
    quint32 uiCnt = 0;
    while(sql.next()){
        uiCnt = sql.value(0).toUInt();
    }
    return uiCnt;
}

QList<UserInfo> usersql::getPageUser(quint32 page,quint32 cnt)
{
    QList<UserInfo> l;
    QSqlQuery sql(m_db);
    QString strsql = QString("select * from user order by id limit %1 offset %2").
            arg(cnt).arg(page*cnt);
    sql.exec(strsql);
    UserInfo info;
    while(sql.next()){
        info.id = sql.value(0).toUInt();
        info.name = sql.value(1).toString();
        info.phonenumber=sql.value(2).toString();
        info.account = sql.value(3).toString();
        info.address = sql.value(4).toString();
        l.append(info);
    }
    return l;

}

bool usersql::addUser(UserInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("insert into user values (null,'%1','%2','%3','%4')").
            arg(info.name).
            arg(info.phonenumber).
            arg(info.account).
            arg(info.address);
    return sql.exec(strSql);
}
