#ifndef DELIVERYSQL_H
#define DELIVERYSQL_H
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
struct DeliveryInfo
{
    int id;
    QString number;
    QString sender;
    QString receiver;
    QString sendtime;
    QString status;
    QString courier;
    QString type;
};

class deliverysql : public QObject
{
public:
    static deliverysql *ptrdSql;
    static deliverysql *getinstance()
    {
        if(nullptr == ptrdSql )
           ptrdSql = new deliverysql ;
        return ptrdSql;
    }
    explicit deliverysql(QObject *parent = nullptr);
    //初始化
    void init();
    //获取快递数量
    quint32 getDelCnt();
    //获取快递数据
    QList<DeliveryInfo> getPageDelivery(quint32,quint32);
    //更新表格
    void updateTable(DeliveryInfo);
    //增加快递信息
    bool addDel(DeliveryInfo);
    //用户签收快递
    bool updateDelInfo(DeliveryInfo);
    bool updateDCInfo(DeliveryInfo);
    bool collectDelInfo(DeliveryInfo);
private:
    QSqlDatabase m_db;
};


#endif // DELIVERYSQL_H
