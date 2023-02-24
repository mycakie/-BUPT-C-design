#ifndef CONNNECTION_H
#define CONNNECTION_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
static bool createConnection()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
    if(!db.open()){
        QMessageBox::critical(0,"错误","文件读取出错");
        return false;
    }
    QSqlQuery query;
    query.exec(QString("create table delivery (number vchar, sender vchar, receiver vchar, sendtime vchar,receive time,status vchar,description vchar, details vchar)"));
    return true;
}
#endif // CONNNECTION_H
