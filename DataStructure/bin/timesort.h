#ifndef TIMESORT_H
#define TIMESORT_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "eventsql.h"
struct TimeInfo
{
    int id;//用于存储记录标号
    int week;
    int hour;
};
class TimeSort : public QObject
{
    Q_OBJECT
public:
    explicit TimeSort(QObject *parent = nullptr);
    //排序函数
    int sort(TimeInfo a[],int begin,int end);
    void init(TimeInfo t[], QList<EventInfo> lEvents);
    void QuickSortNoR(TimeInfo* arr, int begin, int end);
    TimeInfo t[200];
signals:
private:
    eventSql *m_ptreventSql;

};

#endif // TIMESORT_H
