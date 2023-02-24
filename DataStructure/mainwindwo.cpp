#include "mainwindwo.h"
#include "ui_mainwindwo.h"

MainWindwo * MainWindwo::ptrmainWindwo = nullptr ;

MainWindwo::MainWindwo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindwo),
    m_ptreventSql(nullptr)
{
    ui->setupUi(this);
    m_dlgLogin.show();
    auto f = [&](){
        this->show();
    };
    connect(&m_dlgLogin,&Page_login::sendLoginSuccessStu,this,f);
    day = 1;
    hour = 0;
    minute = 0;
    second = 0;
    myday = -1;
    myhour = -1;
    myminute = -1;
    TimerID = startTimer(1000/360);
}

MainWindwo::~MainWindwo()
{
    delete ui;
}

void MainWindwo::timerEvent(QTimerEvent * e)
{
    if (e->timerId() == TimerID)
        {
            second++;
            if (second == 60)
            {
                second = 0;
                minute++;
                if (minute == 60)
                {
                    minute = 0;
                    hour++;
                    if (hour == 24)
                    {
                        hour = 0;
                        day++;
                        if (day == 8)
                            day = 1;
                    }
                }
            }
         }
    repaint();



}


void MainWindwo::paintEvent(QPaintEvent *)
{
    //每天的闹钟中午十二点响起
    if (hour == 12 && minute == 0 && second == 0)
    {
        QMessageBox::information(nullptr,"信息","午休时间到！");
        qDebug()<<"闹钟响了";
    }
    //每周的闹钟周一早六点响起
    if(day == 1 && hour == 6 && minute == 0 && second == 0)
    {
        QMessageBox::information(nullptr,"信息","又到周一了，快起来上早八！");
        qDebug()<<"闹钟响了";
    }
    //建立闹钟
    if (day == myday &&hour == myhour && minute == myminute && second == 0)
    {
        QMessageBox::information(nullptr,"信息","闹钟响了！");
        qDebug()<<"闹钟响了";
    }

    QPainter pt(this);
    QString str = QString::number(hour) + ":" + QString::number(minute) + ":" + QString::number(second);
    QString week_day;
        switch (day)
        {
        case 1:
            week_day = "Monday";
            break;
        case 2:
            week_day = "Tuesday";
            break;
        case 3:
            week_day = "Wednesday";
            break;
        case 4:
            week_day = "Thursday";
            break;
        case 5:
            week_day = "Friday";
            break;
        case 6:
            week_day = "Saturday";
            break;
        case 7:
            week_day = "Sunday";
            break;
        }
        ui->Weekday->setText(week_day);
        ui->VirtualTime->setText(str);
        QFont fo("新宋体", 12, QFont::Bold, true);
        pt.setFont(fo);
        pt.setPen(Qt::black);

}


void MainWindwo::on_switch_2_clicked()
{
    //点击进入导航界面
     QtSGS *navigation=new QtSGS;  //给窗口2创建一个对象
     this ->close();                //this是当前窗体（窗口1）的指针，关闭
     navigation ->show();              //窗口2显示出来

}

void MainWindwo::on_add_clicked()
{
    m_dialog_addpe.exec();
    updateTable();

}

void MainWindwo::updateTable()
{

    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(8);
    QStringList l;
    l<<"序号"<<"名称"<<"老师"<<"地点"<<"时间"<<"考试时间"<<"考试地点"<<"课程群";
    ui->tableWidget->setHorizontalHeaderLabels(l);
    m_ptreventSql = eventSql::getinstance();
    m_ptreventSql ->init();
    auto cnt = m_ptreventSql ->getEveCnt();
    QList<EventInfo> lEvents = m_ptreventSql->getPageEvent(0,cnt);
    ui->tableWidget->setRowCount(cnt);
    for(int i = 0;i<lEvents.size();i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(i)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(lEvents[i].name));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(lEvents[i].teacher));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(lEvents[i].location));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(lEvents[i].time));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(lEvents[i].test_time));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(lEvents[i].test_loc));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(lEvents[i].group_number));
     }
}

void MainWindwo::on_load_clicked()
{
    updateTable();
}

void MainWindwo::on_search_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(8);
    QStringList l;
    l<<"序号"<<"名称"<<"老师"<<"地点"<<"时间"<<"考试时间"<<"考试地点"<<"课程群";
    ui->tableWidget->setHorizontalHeaderLabels(l);
    m_ptreventSql = eventSql::getinstance();
    m_ptreventSql ->init();
    auto cnt = m_ptreventSql ->getEveCnt();
    QList<EventInfo> lEvents = m_ptreventSql->getPageEvent(0,cnt);
    QString strFilter = ui->input->text();
    //string s = strFilter.toStdString();
    int index = 0;
    int *res = Search(lEvents, strFilter);
    for(int i = 0; res[i] != -1; i++){
        ui->tableWidget->setItem(index,0,new QTableWidgetItem(QString::number(res[i])));
        ui->tableWidget->setItem(index,1,new QTableWidgetItem(lEvents[res[i]].name));
        ui->tableWidget->setItem(index,2,new QTableWidgetItem(lEvents[res[i]].teacher));
        ui->tableWidget->setItem(index,3,new QTableWidgetItem(lEvents[res[i]].location));
        ui->tableWidget->setItem(index,4,new QTableWidgetItem(lEvents[res[i]].time));
        ui->tableWidget->setItem(index,5,new QTableWidgetItem(lEvents[res[i]].test_time));
        ui->tableWidget->setItem(index,6,new QTableWidgetItem(lEvents[res[i]].test_loc));
        ui->tableWidget->setItem(index,7,new QTableWidgetItem(lEvents[res[i]].group_number));
        index ++;
    }

    ui->tableWidget->setRowCount(index);
}


void MainWindwo::on_search_2_clicked()
{
    //点击进入文件管理界面
    class update *mgr = new class update; //给文件管理窗口创建一个对象
     mgr ->show();   //窗口显示出来
}

void MainWindwo::on_fastTime_clicked()
{
    killTimer(TimerID);
    TimerID = startTimer(5);

}

void MainWindwo::on_stopTime_clicked()
{
    killTimer(TimerID);
}

void MainWindwo::on_start_clicked()
{
    TimerID = startTimer(1000/360);
}


void MainWindwo::on_set_clicked()
{

    class dlg_setalarm *mgr = new class dlg_setalarm; //给设置闹钟窗口创建一个对象
    mgr ->show();   //窗口显示出来
    myday=mgr->setday+1;
    switch(mgr->sethour){
    case 0:
        myhour=10;
        break;
    case 1:
        myhour=14;
        break;
    case 2:
        myhour=18;
        break;
    }
    switch(mgr->setminute){
    case 0:
        myminute=0;
        break;
    case 1:
        myminute=30;
        break;
    case 2:
        myminute=45;
        break;
    }


}

void MainWindwo::on_bytime_clicked()
{
    //class TimeSort *ts = new TimeSort;
    QSqlDatabase m_db;
    QList<EventInfo> lEvents;
    QSqlQuery sql(m_db);
    QString strsql = QString("select * from event order by time ");
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
        lEvents.append(info);
    }
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(8);
    QStringList l1;
    l1<<"序号"<<"名称"<<"老师"<<"地点"<<"时间"<<"考试时间"<<"考试地点"<<"课程群";
    ui->tableWidget->setHorizontalHeaderLabels(l1);
    m_ptreventSql = eventSql::getinstance();
    m_ptreventSql ->init();
    auto cnt = m_ptreventSql ->getEveCnt();
    //QList<EventInfo> lEvents = m_ptreventSql->getPageEvent(0,cnt);
    ui->tableWidget->setRowCount(cnt);
    for(int i = 0;i<lEvents.size();i++)
    {

        //int index = ts->t[i].id;
        int index = i;
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(index)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(lEvents[index].name));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(lEvents[index].teacher));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(lEvents[index].location));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(lEvents[index].time));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(lEvents[index].test_time));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(lEvents[index].test_loc));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(lEvents[index].group_number));
     }

}
