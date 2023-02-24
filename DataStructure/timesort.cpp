#include "timesort.h"
#include <QDebug>
#include<QStack>
TimeSort::TimeSort(QObject *parent) : QObject(parent)
{
    m_ptreventSql = eventSql::getinstance();
    m_ptreventSql ->init();
    auto cnt = m_ptreventSql ->getEveCnt();
    QList<EventInfo> lEvents = m_ptreventSql->getPageEvent(0,cnt);
    init(t,lEvents);
    QuickSortNoR(t,0,lEvents.size()-1);
}
//单趟排序
int TimeSort::sort(TimeInfo a[],int begin,int end)
{
    if (begin >= end)//当只有一个数据或是序列不存在时，不需要进行操作
            return -1;

        int left = begin;//L
        int right = end;//R
        int id = a[left].id;//在最左边形成一个坑位
        int key_w = a[left].week;
        int key_h = a[left].hour;
        while (left < right)
        {
            //right向左，找小
            while (left < right&&(a[right].week > key_w||(a[right].week == key_w&&a[right].hour>key_h)))
            {
                right--;
            }
            //填坑
            a[left].id = a[right].id;
            a[left].week = a[right].week;
            a[left].hour = a[right].hour;
            //left向右，找大
            while (left < right&&(a[left].week < key_w||(a[left].week == key_w&&a[left].hour < key_h)))
            {
                left++;
            }
            //填坑
            a[right].id = a[left].id;
            a[right].week = a[left].week;
            a[right].hour = a[left].hour;
        }
        int meeti = left;//L和R的相遇点
        a[meeti].id = id;//将key抛入坑位
        a[meeti].week = key_w;
        a[meeti].hour = key_h;
        return meeti;
        //sort(a, begin, meeti - 1);//key的左序列进行此操作
        //sort(a, meeti + 1, end);//key的右序列进行此操作

}

void TimeSort::init(TimeInfo t[], QList<EventInfo> lEvents)
{

    for(int i=0;i<lEvents.size();i++)
    {
        t[i].id=i;
        //存周次
        if(lEvents[i].time.mid(2,1)=="一")
            t[i].week=1;
        else if(lEvents[i].time.mid(2,1)=="二")
            t[i].week=2;
        else if(lEvents[i].time.mid(2,1)=="三")
            t[i].week=3;
        else if(lEvents[i].time.mid(2,1)=="四")
            t[i].week=4;
        else if(lEvents[i].time.mid(2,1)=="五")
            t[i].week=5;
        else if(lEvents[i].time.mid(2,1)=="六")
            t[i].week=6;
        else if(lEvents[i].time.mid(2,1)=="日")
            t[i].week=7;
        else
        {
            if(lEvents[i].time.mid(1,1)=="二")
               t[i].week=2;
            else
               t[i].week=6;
        }
        //存时
        if(lEvents[i].time.mid(3,2)=="08")
            t[i].hour=8;
        else if(lEvents[i].time.mid(3,2)=="09")
            t[i].hour=9;
        else if(lEvents[i].time.mid(3,2)=="10")
            t[i].hour=10;
        else if(lEvents[i].time.mid(3,2)=="11")
            t[i].hour=11;
        else if(lEvents[i].time.mid(3,2)=="12")
            t[i].hour=12;
        else if(lEvents[i].time.mid(3,2)=="13")
            t[i].hour=13;
        else if(lEvents[i].time.mid(3,2)=="14")
            t[i].hour=14;
        else if(lEvents[i].time.mid(3,2)=="15")
            t[i].hour=15;
        else if(lEvents[i].time.mid(3,2)=="16")
            t[i].hour=16;
        else if(lEvents[i].time.mid(3,2)=="17")
            t[i].hour=17;
        else if(lEvents[i].time.mid(3,2)=="18")
            t[i].hour=18;
        else if(lEvents[i].time.mid(3,2)=="19")
            t[i].hour=19;
        else if(lEvents[i].time.mid(3,2)=="20")
            t[i].hour=20;
        else if(lEvents[i].time.mid(3,2)=="21")
            t[i].hour=21;
        else if(lEvents[i].time.mid(3,2)=="22")
            t[i].hour=22;
        else
        {
            if(lEvents[i].time.mid(7,2)=="13")
               t[i].hour=13;
            if(lEvents[i].time.mid(5,2)=="08")
               t[i].hour=8;
            if(lEvents[i].time.mid(5,2)=="19")
               t[i].hour=19;
        }
    }

}


void TimeSort::QuickSortNoR(TimeInfo* arr, int begin, int end)
{
    QStack<int> st;
    //先入右边
    st.push(end);
    //再入左边
    st.push(begin);
    while (!st.empty())
    {
        //左区间
        int left = st.top();
        st.pop();
        //右区间
        int right = st.top();
        st.pop();
        //中间数
        int mid = sort(arr, left, right);
        //当左区间>=mid-1则证明左区间已经排好序了
        if (left < mid - 1)
        {
            st.push(mid - 1);
            st.push(left);
        }
        //当mid+1>=右区间则证明右区间已经排好序
        if (right > mid + 1)
        {
            st.push(right);
            st.push(mid + 1);
        }
    }
}


