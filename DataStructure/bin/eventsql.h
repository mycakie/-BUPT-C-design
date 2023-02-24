#ifndef EVENTSQL_H
#define EVENTSQL_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
struct EventInfo
{
    int id;
    QString name;
    QString teacher;
    QString location;
    QString time;
    QString test_time;
    QString test_loc;
    QString group_number;
};
struct UserInfo
{
    QString username;
    QString password;
    QString aut;
};

class eventSql : public QObject
{
    Q_OBJECT
public:  
    static eventSql *ptreventSql;
    static eventSql *getinstance()
    {
        if(nullptr == ptreventSql )
            ptreventSql = new eventSql ;
        return ptreventSql;
    }
    explicit eventSql(QObject *parent = nullptr);
    //初始化
    void init();
    //获取事件数量
    quint32 getEveCnt();
    //获取事件数据
    QList<EventInfo> getPageEvent(quint32,quint32);
    //更新表格
    void updateTable(EventInfo);
    //增加日程信息
    bool addEve(EventInfo);
    //管理员修改课程信息
    bool updateEveInfo(EventInfo);

signals:
private:
    QSqlDatabase m_db;

};

#endif // EVENTSQL_H
