#ifndef COURIERSQL_H
#define COURIERSQL_H
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

struct CourierInfo{
    int id;
    QString name;
    QString phonenumber;
    QString account;
};
class couriersql : public QObject
{
public:
    static couriersql *ptrcSql;
    static couriersql *getinstance()
    {
        if(nullptr == ptrcSql )
           ptrcSql = new couriersql ;
        return ptrcSql;
    }
    explicit couriersql(QObject *parent = nullptr);
    //初始化
    void init();
    //获取用户数量
    quint32 getCourierCnt();
    //获取用户数据
    QList<CourierInfo> getPageCourier(quint32,quint32);
    //更新表格
    void updateCTable(CourierInfo);
    //增加用户
    bool addCourier(CourierInfo);

private:
    QSqlDatabase m_db;
};

#endif // COURIERSQL_H
