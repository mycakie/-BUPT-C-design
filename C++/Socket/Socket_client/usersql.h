#ifndef USERSQL_H
#define USERSQL_H
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
struct UserInfo{
    int id;
    QString name;
    QString phonenumber;
    QString account;
    QString address;
};

class usersql : public QObject
{
public:
    static usersql *ptruSql;
    static usersql *getinstance()
    {
        if(nullptr == ptruSql )
           ptruSql = new usersql ;
        return ptruSql;
    }
    explicit usersql(QObject *parent = nullptr);
    //初始化
    void init();
    //获取用户数量
    quint32 getUserCnt();
    //获取用户数据
    QList<UserInfo> getPageUser(quint32,quint32);
    //更新表格
    void updateUTable(UserInfo);
    //增加用户
    bool addUser(UserInfo);

private:
    QSqlDatabase m_db;
};

#endif // USERSQL_H
