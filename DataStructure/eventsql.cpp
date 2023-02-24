#include "eventsql.h"
#include <QMessageBox>
#include <QtDebug>
#include <QCoreApplication>


eventSql * eventSql::ptreventSql = nullptr ;
eventSql::eventSql(QObject *parent) : QObject(parent)
{


}

void eventSql::init()
{
    if (QSqlDatabase::drivers().isEmpty())
        qDebug()<<"No database drivers found";
    m_db = QSqlDatabase::addDatabase("QSQLITE");

    m_db.setDatabaseName("D:\\data.db");
    if (!m_db.open())
        qDebug()<<"db cannot be opened" ;
}

quint32 eventSql::getEveCnt()
{
    QSqlQuery sql(m_db);
    sql.exec("select count(id) from event");
    quint32 uiCnt = 0;
    while(sql.next()){
        uiCnt = sql.value(0).toUInt();
    }
    return uiCnt;
}

QList<EventInfo> eventSql::getPageEvent(quint32 page,quint32 cnt)
{
    QList<EventInfo> l;
    QSqlQuery sql(m_db);
    QString strsql = QString("select * from event order by id limit %1 offset %2").
            arg(cnt).arg(page*cnt);
    sql.exec(strsql);
    EventInfo info;
    while(sql.next()){
        info.id = sql.value(0).toUInt();
        info.name = sql.value(1).toString();
        info.teacher = sql.value(2).toString();
        info.location = sql.value(3).toString();
        info.time = sql.value(4).toString();
        info.test_time = sql.value(5).toString();
        info.test_loc = sql.value(6).toString();
        info.group_number = sql.value(7).toString();
        l.append(info);
    }
    return l;

}

bool eventSql::addEve(EventInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("insert into event values (null,'%1','%2','%3','%4','%5','%6','%7')").
            arg(info.name).
            arg(info.teacher).
            arg(info.location).
            arg(info.time).
            arg(info.test_time).
            arg(info.test_loc).
            arg(info.group_number);
    return sql.exec(strSql);
}

bool eventSql::updateEveInfo(EventInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("update event set test_time  = '%1',test_loc = '%2' where name = '%3' ").
            arg(info.test_time).
            arg(info.test_loc).
            arg(info.name);
    return sql.exec(strSql);
}



