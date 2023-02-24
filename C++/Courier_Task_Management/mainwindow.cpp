#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <QPixmap>
#include <QPalette>
#include <QHeaderView>
#include <QByteArray>
#include <QMessageBox>
#include <QInputDialog>
#include <qdir.h>
#include <QFile>

#include "balancedialog.h"
#include "ChangeFile.h"
#include "manager.h"
#include "realuser.h"
#include "courier.h"

int k; //记录模型中的快递数量
DeliveryInfo dinfo;
mainwindow::mainwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainwindow)
{


    //设置初始状态为未登录
    state=0;
    ui->setupUi(this);
    //开始时进入登录页面并加载数据
    ui->stackedWidget->setCurrentIndex(0);
    //设置下拉框
    QStringList strlist;
    strlist<<"用户"<<"管理员"<<"快递员";
    ui->comboBox->addItems(strlist);
    //界面美化
    ui->le_pw->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:20px;"       //内边距-字体缩进
                                    "background-color: rgb(240,255,255);" //背景颜色
                                    "border:2px solid rgb(255,248,220);border-radius:15px;");//边框粗细-颜色-圆角设置
    ui->le_name->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:20px;"       //内边距-字体缩进
                                    "background-color: rgb(240, 255, 255);" //背景颜色
                                    "border:2px solid rgb(255,248,220);border-radius:15px;");//边框粗细-颜色-圆角设置
    ui->LoginButton->setStyleSheet("QPushButton{background-color: rgb(	255,240,245);"
                                    "border: none;border-radius:15px;}");
    ui->RegisterButton->setStyleSheet("QPushButton{background-color: rgb(	255,240,245);"
                                    "border: none;border-radius:15px;}");
    //设置菜单栏槽函数
    connect(ui->actionlogin,&QAction::triggered,[=](){ //登录
        if(state==0){
             ui->stackedWidget->setCurrentIndex(0);
        }else{
            QMessageBox::warning(this,"警告","您已登录");
        }
    });

    connect(ui->actionlogout,&QAction::triggered,[=](){ //注销
        if(state==0){
             QMessageBox::warning(this,"警告","您还未登录");
        }else{
             ui->stackedWidget->setCurrentIndex(0);
             ui->le_name->clear();
             ui->le_pw->clear();
             state=0;
             delete pr;
        }
    });

    connect(ui->actionchange_password,&QAction::triggered,[=](){ //密码管理
        if(state){
             bool ok;
             QString text = QInputDialog::getText(this, "修改密码",
                                                         "新密码:", QLineEdit::Normal,
                                                          QDir::home().dirName(), &ok);
             if (ok){
                  if(text!=""){
                      if(text.indexOf(" ")!=-1){
                           QMessageBox::warning(this,"警告","密码不能包含空格");
                       }else{
                            int index=pr->getUserType();
                            pr->password=text;
                            changeFile(index,1,this,text);
                            QMessageBox::information(this,"提示","密码修改成功");
                       }
                   }else{
                        QMessageBox::warning(this,"警告","密码不能为空");
                   }
                }
            }else{
                QMessageBox::warning(this,"警告","您还未登录");
            }
    });

    connect(ui->actionbalance,&QAction::triggered,[=](){ //余额管理
        if(state){
             BalanceDialog *mydialog = new BalanceDialog(this,pr->balance);
             Qt::WindowFlags flags=mydialog->windowFlags();
             mydialog->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);//设置窗口为固定大小
             int ret=mydialog->exec () ;
             if (ret==BalanceDialog::Accepted){
                  QString text=mydialog->getBalance();
                  if(text!=""){
                      int index=pr->getUserType();
                      pr->balance+=text.toDouble();
                      changeFile(index,2,this,QString("%1").arg(pr->balance));
                      QMessageBox::information(this,"提示","充值成功");
                  }
             }
         }else{
                QMessageBox::warning(this,"警告","您还未登录");
         }
    });

    connect(ui->actiondeliverymanage,&QAction::triggered,[=](){ //快递管理
        if(state==0){
             QMessageBox::warning(this,"警告","您还未登录");
        }else{
             //切页
             ui->stackedWidget->setCurrentIndex(1);
             //准备表格
             updateUDTable();
        }
    });

    connect(ui->actionsearch_user,&QAction::triggered,[=](){
        ui->stackedWidget->setCurrentIndex(4);
        updateUTable();
    });
   connect(ui->actionsearch_delivery,&QAction::triggered,[=](){
        ui->stackedWidget->setCurrentIndex(2);
        updateDTable();
   });
   connect(ui->actiondistribute,&QAction::triggered,[=](){
        ui->stackedWidget->setCurrentIndex(5);
        updateDUTable();

   });
   connect(ui->actioncollect_delivery,&QAction::triggered,[=](){
        ui->stackedWidget->setCurrentIndex(7);
        updateCDUTable();
   });
   connect(ui->actionsearch_courierdelivery,&QAction::triggered,[=](){
        ui->stackedWidget->setCurrentIndex(8);
        updateCDTable();
   });
   connect(ui->actionsearch_courier,&QAction::triggered,[=](){
        ui->stackedWidget->setCurrentIndex(9);
        ui->searchCTable->clear();
        ui->searchCTable->setColumnCount(4);
        QStringList l;
        l<<"序号"<<"姓名"<<"电话号码"<<"账号";
        ui->searchCTable->setHorizontalHeaderLabels(l);
        m_ptrcSql = couriersql::getinstance();
        m_ptrcSql ->init();
        auto cnt = m_ptrcSql ->getCourierCnt();
        QList<CourierInfo> lCourier = m_ptrcSql->getPageCourier(0,cnt);
        ui->searchCTable->setRowCount(cnt);
        for(int i = 0;i<lCourier.size();i++)
        {
            ui->searchCTable->setItem(i,0,new QTableWidgetItem(QString::number(i)));
            ui->searchCTable->setItem(i,1,new QTableWidgetItem(lCourier[i].name));
            ui->searchCTable->setItem(i,2,new QTableWidgetItem(lCourier[i].phonenumber));
            ui->searchCTable->setItem(i,3,new QTableWidgetItem(lCourier[i].account));
        }
   });
}

mainwindow::~mainwindow()
{
    delete ui;
}


void mainwindow::on_LoginButton_clicked()
{
    QString a=ui->le_name->text(),p=ui->le_pw->text();
    if(a!=""&&p!=""){
        QString path;
        int index=ui->comboBox->currentIndex();
        if(index==0){
            path="D:\\userdata\\user.txt";
        }
        else if(index==1){
            path="D:\\userdata\\manager.txt";
        }
            else{
            path="D:\\userdata\\courier.txt";
        }
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
             QMessageBox::critical(this,"错误","文件读取出错");
             return;
        }
           //检查是否存在此账户
        QTextStream in(&file);
        QString l="",r="";
        double c=0;
        while(!in.atEnd()){
            QString line=in.readLine(0);
            l=line.section(" ",0,0);
            r=line.section(" ",1,1);
            c=line.section(" ",2,2).toDouble();
            if(l==a){
                break;
            }
        }
        if(l==a&&r==p){
            ui->stackedWidget->setCurrentIndex(3);
            ui->label_4->setText(a);
            state=1;
            if(index==0){
                this->pr=new realUser(a,p,c,0);
            }
            else if(index==1){
                this->pr=new manager(a,p,c,1);
            }
            else
                this->pr=new courier(a,p,c,2);
         }else{
             QMessageBox::warning(this,"警告","账号或密码错误");
         }
         file.close();
    }else{
        QMessageBox::warning(this,"警告","账号和密码不能为空");
    }
}

void mainwindow::on_RegisterButton_clicked()
{
    QString a=ui->le_name->text(),p=ui->le_pw->text();
    if(a!=""&&p!=""){
        int i=a.indexOf(" "),j=p.indexOf(" ");
        if(i!=-1||j!=-1){
            QMessageBox::warning(this,"警告","账号和密码不能包含空格");
            return;
        }

     QString path;
     if(ui->comboBox->currentIndex()==0){
        path="D:\\userdata\\user.txt";
        }
     if(ui->comboBox->currentIndex()==2){
             path="D:\\userdata\\courier.txt";
        }
     QFile file(path);
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
           QMessageBox::critical(this,"错误","文件读取出错");
           return;
      }
      //检查账号是否被注册过
      QTextStream in(&file);
      QString l="";
      while(!in.atEnd()){
           QString line=in.readLine(0);
           int i=line.indexOf(" ");
           l=line.left(i);
           qDebug()<<l;
           if(l==a){
               break;
           }
      }
      if(l==a){
           QMessageBox::warning(this,"警告","此账号已被注册");
                return;
      }
      file.close();
      if (!file.open(QIODevice::WriteOnly | QIODevice::Append)){
            QMessageBox::critical(this,"错误","文件读取出错");
            return;
       }
       //写入文件
       QTextStream out(&file);
       out<<a<<" "<<p<<" "<<"0"<<endl;
       out.flush();
       file.close();
       //写入数据库
       UserInfo info;
       info.account=a;
       auto ptr = usersql::getinstance();
       ptr->addUser(info);
       QMessageBox::information(this,"提示","注册成功");
       }else{
            QMessageBox::warning(this,"警告","账号和密码不能为空");
    }
}

void mainwindow::updateDTable()
{
    ui->searchdtable->clear();
        ui->searchdtable->setColumnCount(8);
        QStringList l;
        l<<"序号"<<"单号"<<"发件人"<<"收件人"<<"发件时间"<<"快件状态"<<"快递员"<<"快件类型";
        ui->searchdtable->setHorizontalHeaderLabels(l);
        m_ptrdSql = deliverysql::getinstance();
        m_ptrdSql ->init();
        auto cnt = m_ptrdSql ->getDelCnt();
        QList<DeliveryInfo> lEvents = m_ptrdSql->getPageDelivery(0,cnt);
        ui->searchdtable->setRowCount(cnt);
        for(int i = 0;i<lEvents.size();i++)
        {
            ui->searchdtable->setItem(i,0,new QTableWidgetItem(QString::number(i)));
            ui->searchdtable->setItem(i,1,new QTableWidgetItem(lEvents[i].number));
            ui->searchdtable->setItem(i,2,new QTableWidgetItem(lEvents[i].sender));
            ui->searchdtable->setItem(i,3,new QTableWidgetItem(lEvents[i].receiver));
            ui->searchdtable->setItem(i,4,new QTableWidgetItem(lEvents[i].sendtime));
            ui->searchdtable->setItem(i,5,new QTableWidgetItem(lEvents[i].status));
            ui->searchdtable->setItem(i,6,new QTableWidgetItem(lEvents[i].courier));
            ui->searchdtable->setItem(i,7,new QTableWidgetItem(lEvents[i].type));
        }
}

void mainwindow::updateUTable()
{
    ui->searchutable->clear();
    ui->searchutable->setColumnCount(5);
    QStringList l;
    l<<"序号"<<"姓名"<<"电话号码"<<"账号"<<"地址";
    ui->searchutable->setHorizontalHeaderLabels(l);
    m_ptruSql = usersql::getinstance();
    m_ptruSql ->init();
    auto cnt = m_ptruSql ->getUserCnt();
    QList<UserInfo> lUser = m_ptruSql->getPageUser(0,cnt);
    ui->searchutable->setRowCount(cnt);
    for(int i = 0;i<lUser.size();i++)
    {
        ui->searchutable->setItem(i,0,new QTableWidgetItem(QString::number(i)));
        ui->searchutable->setItem(i,1,new QTableWidgetItem(lUser[i].name));
        ui->searchutable->setItem(i,2,new QTableWidgetItem(lUser[i].phonenumber));
        ui->searchutable->setItem(i,3,new QTableWidgetItem(lUser[i].account));
        ui->searchutable->setItem(i,4,new QTableWidgetItem(lUser[i].address));
    }
}

void mainwindow::updateUDTable()
{
    //准备表格
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(8);
    QStringList l;
    l<<"序号"<<"单号"<<"发件人"<<"收件人"<<"发件时间"<<"快件状态"<<"快递员"<<"快件类型";
    ui->tableWidget->setHorizontalHeaderLabels(l);
    //数据库准备
    m_ptrdSql = deliverysql::getinstance();
    m_ptrdSql ->init();
    m_ptruSql = usersql::getinstance();
    m_ptruSql ->init();
    auto cnt1 = m_ptrdSql ->getDelCnt();
    QList<DeliveryInfo> lEvents = m_ptrdSql->getPageDelivery(0,cnt1);
    ui->tableWidget->setRowCount(cnt1);
    auto cnt2 = m_ptruSql ->getUserCnt();
    QList<UserInfo> lUser = m_ptruSql->getPageUser(0,cnt2);
    QString strFilter;
    //找到该账号用户所对应的姓名
    for(int i = 0;i<lUser.size();i++)
    {
        if(lUser[i].account==pr->account){
           strFilter=lUser[i].name;
           break;
        }
     }
    int index=0;
    for(int i = 0;i<lEvents.size();i++)
    {
        //如果收件人和发件人都不是用户，表格不显示
        if(!(lEvents[i].sender==strFilter||lEvents[i].receiver==strFilter))
            continue;
        ui->tableWidget->setItem(index,0,new QTableWidgetItem(QString::number(index)));
        ui->tableWidget->setItem(index,1,new QTableWidgetItem(lEvents[i].number));
        ui->tableWidget->setItem(index,2,new QTableWidgetItem(lEvents[i].sender));
        ui->tableWidget->setItem(index,3,new QTableWidgetItem(lEvents[i].receiver));
        ui->tableWidget->setItem(index,4,new QTableWidgetItem(lEvents[i].sendtime));
        ui->tableWidget->setItem(index,5,new QTableWidgetItem(lEvents[i].status));
        ui->tableWidget->setItem(index,6,new QTableWidgetItem(lEvents[i].courier));
        ui->tableWidget->setItem(index,7,new QTableWidgetItem(lEvents[i].type));
        index++;
     }

}

void mainwindow::updateDUTable()
{
    //准备表格
    ui->distributeTable->clear();
    ui->distributeTable->setColumnCount(8);
    QStringList l;
    l<<"序号"<<"单号"<<"发件人"<<"收件人"<<"发件时间"<<"快件状态"<<"快递员"<<"快件类型";
    ui->distributeTable->setHorizontalHeaderLabels(l);
    //数据库准备
    m_ptrdSql = deliverysql::getinstance();
    m_ptrdSql ->init();
    auto cnt = m_ptrdSql ->getDelCnt();
    QList<DeliveryInfo> lEvents = m_ptrdSql->getPageDelivery(0,cnt);
    ui->distributeTable->setRowCount(cnt);
    //筛选待揽收快递
    QString strFilter="待分配";
    int index=0;
    for(int i = 0;i<lEvents.size();i++)
    {
        //如果已经分配了快递员，表格不显示
        if(!(lEvents[i].courier==strFilter))
            continue;
        ui->distributeTable->setItem(index,0,new QTableWidgetItem(QString::number(index)));
        ui->distributeTable->setItem(index,1,new QTableWidgetItem(lEvents[i].number));
        ui->distributeTable->setItem(index,2,new QTableWidgetItem(lEvents[i].sender));
        ui->distributeTable->setItem(index,3,new QTableWidgetItem(lEvents[i].receiver));
        ui->distributeTable->setItem(index,4,new QTableWidgetItem(lEvents[i].sendtime));
        ui->distributeTable->setItem(index,5,new QTableWidgetItem(lEvents[i].status));
        ui->distributeTable->setItem(index,6,new QTableWidgetItem(lEvents[i].courier));
        ui->distributeTable->setItem(index,7,new QTableWidgetItem(lEvents[i].type));
        index++;
    }
}

void mainwindow::updateCTable()
{

    ui->distributeCTable->clear();
    ui->distributeCTable->setColumnCount(4);
    QStringList l;
    l<<"序号"<<"姓名"<<"电话号码"<<"账号";
    ui->distributeCTable->setHorizontalHeaderLabels(l);
    m_ptrcSql = couriersql::getinstance();
    m_ptrcSql ->init();
    auto cnt = m_ptrcSql ->getCourierCnt();
    QList<CourierInfo> lCourier = m_ptrcSql->getPageCourier(0,cnt);
    ui->distributeCTable->setRowCount(cnt);
    for(int i = 0;i<lCourier.size();i++)
    {
        ui->distributeCTable->setItem(i,0,new QTableWidgetItem(QString::number(i)));
        ui->distributeCTable->setItem(i,1,new QTableWidgetItem(lCourier[i].name));
        ui->distributeCTable->setItem(i,2,new QTableWidgetItem(lCourier[i].phonenumber));
        ui->distributeCTable->setItem(i,3,new QTableWidgetItem(lCourier[i].account));
    }
}

void mainwindow::updateCDTable()
{
    //准备表格
    ui->searchCDTable->clear();
    ui->searchCDTable->setColumnCount(8);
    QStringList l;
    l<<"序号"<<"单号"<<"发件人"<<"收件人"<<"发件时间"<<"快件状态"<<"快递员"<<"快件类型";
    ui->searchCDTable->setHorizontalHeaderLabels(l);
    //数据库准备
    m_ptrdSql = deliverysql::getinstance();
    m_ptrdSql ->init();
    m_ptrcSql = couriersql::getinstance();
    m_ptrcSql ->init();
    auto cnt1 = m_ptrdSql ->getDelCnt();
    QList<DeliveryInfo> lEvents = m_ptrdSql->getPageDelivery(0,cnt1);
    ui->searchCDTable->setRowCount(cnt1);
    auto cnt2 = m_ptrcSql ->getCourierCnt();
    QList<CourierInfo> lCourier = m_ptrcSql->getPageCourier(0,cnt2);
    QString strFilter;
    //找到该账号用户所对应的姓名
    for(int i = 0;i<lCourier.size();i++)
    {
        if(lCourier[i].account==pr->account){
           strFilter=lCourier[i].name;
           break;
        }
     }
    int index=0;
    for(int i = 0;i<lEvents.size();i++)
    {
        //如果收件人和发件人都不是用户，表格不显示
        if(!(lEvents[i].courier==strFilter))
            continue;
        ui->searchCDTable->setItem(index,0,new QTableWidgetItem(QString::number(index)));
        ui->searchCDTable->setItem(index,1,new QTableWidgetItem(lEvents[i].number));
        ui->searchCDTable->setItem(index,2,new QTableWidgetItem(lEvents[i].sender));
        ui->searchCDTable->setItem(index,3,new QTableWidgetItem(lEvents[i].receiver));
        ui->searchCDTable->setItem(index,4,new QTableWidgetItem(lEvents[i].sendtime));
        ui->searchCDTable->setItem(index,5,new QTableWidgetItem(lEvents[i].status));
        ui->searchCDTable->setItem(index,6,new QTableWidgetItem(lEvents[i].courier));
        ui->searchCDTable->setItem(index,7,new QTableWidgetItem(lEvents[i].type));
        index++;
     }

}

void mainwindow::updateCDUTable()
{
    ui->collectTable->clear();
    ui->collectTable->setColumnCount(8);
    QStringList l;
    l<<"序号"<<"单号"<<"发件人"<<"收件人"<<"发件时间"<<"快件状态"<<"快递员"<<"快件类型";
    ui->collectTable->setHorizontalHeaderLabels(l);
    m_ptrdSql = deliverysql::getinstance();
    m_ptrdSql ->init();
    m_ptrcSql = couriersql::getinstance();
    m_ptrcSql ->init();
    auto cnt1 = m_ptrdSql ->getDelCnt();
    QList<DeliveryInfo> lEvents = m_ptrdSql->getPageDelivery(0,cnt1);
    ui->collectTable->setRowCount(cnt1);
    auto cnt2 = m_ptrcSql ->getCourierCnt();
    QList<CourierInfo> lCourier = m_ptrcSql->getPageCourier(0,cnt2);
    QString strFilter;
    //找到该账号用户所对应的姓名
    for(int i = 0;i<lCourier.size();i++)
    {
        if(lCourier[i].account==pr->account){
           strFilter=lCourier[i].name;
           break;
        }
     }
    int index=0;
        for(int i = 0;i<lEvents.size();i++)
        {
            if(!(lEvents[i].courier==strFilter&&lEvents[i].status=="待揽收"))
                continue;
            ui->collectTable->setItem(index,0,new QTableWidgetItem(QString::number(index)));
            ui->collectTable->setItem(index,1,new QTableWidgetItem(lEvents[i].number));
            ui->collectTable->setItem(index,2,new QTableWidgetItem(lEvents[i].sender));
            ui->collectTable->setItem(index,3,new QTableWidgetItem(lEvents[i].receiver));
            ui->collectTable->setItem(index,4,new QTableWidgetItem(lEvents[i].sendtime));
            ui->collectTable->setItem(index,5,new QTableWidgetItem(lEvents[i].status));
            ui->collectTable->setItem(index,6,new QTableWidgetItem(lEvents[i].courier));
            ui->collectTable->setItem(index,7,new QTableWidgetItem(lEvents[i].type));
            index++;
        }
}

void mainwindow::on_SingforD_clicked()
{
    DeliveryInfo info;
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    int count = items.count();
    auto ptr = deliverysql::getinstance();
    for(int i = 0; i < count; i++)
    {
        QTableWidgetItem *item = items.at(i);
        info.number = item->text(); //获取内容
        ptr->updateDelInfo(info);
    }
    QMessageBox::information(nullptr,"信息","签收成功！");
    updateUDTable();
}

void mainwindow::on_send_clicked()
{
    m_adddeliverydialog.exec();
    //修改余额
    double cost;
    if(m_adddeliverydialog.package_type==0)
        cost=8;
    else if(m_adddeliverydialog.package_type==1)
        cost=2;
    else if(m_adddeliverydialog.package_type==2)
        cost=5;
    else
        cost=0;
    pr->balance-=cost;
    if(pr->balance<0){
        QMessageBox::critical(this,"错误","余额不足，请充值！");
        return;
    }
    changeFile(0,2,this,QString("%1").arg(pr->balance));
    //读管理员的余额
    QFile file("D:\\userdata\\manager.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
         QMessageBox::critical(this,"错误","文件读取出错");
         return;
    }
    QTextStream in(&file);
    double c=cost;
    QString line=in.readLine(0);
    c+=line.section(" ",2,2).toDouble();
    changeFile(1,2,this,QString("%1").arg(c));
    updateUDTable();

}

void mainwindow::on_searchbutton_clicked()
{
     DeliveryInfo info;
     info.sender = ui->le_number->text();
     info.receiver = ui->le_number->text();
     info.number = ui->le_number->text();
     info.sendtime = ui->le_number->text();
     info.courier=ui->le_number->text();
     //准备表格
     ui->searchdtable->clear();
     ui->searchdtable->setColumnCount(8);
     QStringList l;
     l<<"序号"<<"单号"<<"发件人"<<"收件人"<<"发件时间"<<"快件状态"<<"快递员"<<"快件类型";
     ui->searchdtable->setHorizontalHeaderLabels(l);
     //数据库准备
     m_ptrdSql = deliverysql::getinstance();
     m_ptrdSql ->init();
     auto cnt1 = m_ptrdSql ->getDelCnt();
     QList<DeliveryInfo> lEvents = m_ptrdSql->getPageDelivery(0,cnt1);
     ui->searchdtable->setRowCount(cnt1);
     int index=0;
     for(int i = 0;i<lEvents.size();i++)
     {
         //如果收件人和发件人都不是用户，表格不显示
         if(!(lEvents[i].number==info.number||lEvents[i].sendtime==info.sendtime||lEvents[i].sender==info.sender||lEvents[i].receiver==info.receiver||lEvents[i].courier==info.courier))
             continue;
         ui->searchdtable->setItem(index,0,new QTableWidgetItem(QString::number(i)));
         ui->searchdtable->setItem(index,1,new QTableWidgetItem(lEvents[i].number));
         ui->searchdtable->setItem(index,2,new QTableWidgetItem(lEvents[i].sender));
         ui->searchdtable->setItem(index,3,new QTableWidgetItem(lEvents[i].receiver));
         ui->searchdtable->setItem(index,4,new QTableWidgetItem(lEvents[i].sendtime));
         ui->searchdtable->setItem(index,5,new QTableWidgetItem(lEvents[i].status));
         ui->searchdtable->setItem(index,6,new QTableWidgetItem(lEvents[i].courier));
         ui->searchdtable->setItem(index,7,new QTableWidgetItem(lEvents[i].type));
         index++;
      }

}

void mainwindow::on_searchbutton_2_clicked()
{
    UserInfo info;
    info.account=ui->le_user->text();
    info.name=ui->le_user->text();
    ui->searchutable->clear();
    ui->searchutable->setColumnCount(5);
    QStringList l;
    l<<"序号"<<"姓名"<<"电话号码"<<"账号"<<"地址";
    ui->searchutable->setHorizontalHeaderLabels(l);
    m_ptruSql = usersql::getinstance();
    m_ptruSql ->init();
    auto cnt = m_ptruSql ->getUserCnt();
    QList<UserInfo> lUser = m_ptruSql->getPageUser(0,cnt);
    ui->searchutable->setRowCount(cnt);
    int index=0;
    for(int i = 0;i<lUser.size();i++)
    {
        if(!(lUser[i].account==info.account||lUser[i].name==info.name))
            continue;
        ui->searchutable->setItem(index,0,new QTableWidgetItem(QString::number(i)));
        ui->searchutable->setItem(index,1,new QTableWidgetItem(lUser[i].name));
        ui->searchutable->setItem(index,2,new QTableWidgetItem(lUser[i].phonenumber));
        ui->searchutable->setItem(index,3,new QTableWidgetItem(lUser[i].account));
        ui->searchutable->setItem(index,4,new QTableWidgetItem(lUser[i].address));
        index++;
    }
}

void mainwindow::on_dsearch_clicked()
{
    DeliveryInfo info;
    info.number = ui->d_uinfo->text();
    info.sender = ui->d_uinfo->text();
    info.receiver = ui->d_uinfo->text();
    info.sendtime = ui->d_uinfo->text();
    //准备表格
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(8);
    QStringList l;
    l<<"序号"<<"单号"<<"发件人"<<"收件人"<<"发件时间"<<"快件状态"<<"快递员"<<"快件类型";
    ui->tableWidget->setHorizontalHeaderLabels(l);
    //数据库准备
    m_ptrdSql = deliverysql::getinstance();
    m_ptrdSql ->init();
    m_ptruSql = usersql::getinstance();
    m_ptruSql ->init();
    auto cnt1 = m_ptrdSql ->getDelCnt();
    QList<DeliveryInfo> lEvents = m_ptrdSql->getPageDelivery(0,cnt1);
    ui->tableWidget->setRowCount(cnt1);
    auto cnt2 = m_ptruSql ->getUserCnt();
    QList<UserInfo> lUser = m_ptruSql->getPageUser(0,cnt2);
    QString strFilter;
    //找到该账号用户所对应的姓名
    for(int i = 0;i<lUser.size();i++)
    {
        if(lUser[i].account==pr->account){
           strFilter=lUser[i].name;
           break;
        }
     }
    int index=0;
    for(int i = 0;i<lEvents.size();i++)
    {
        //如果收件人和发件人都不是用户，表格不显示
        if(!((lEvents[i].sender==strFilter||lEvents[i].receiver==strFilter)&&(lEvents[i].number==info.number||lEvents[i].sender==info.sender||lEvents[i].receiver==info.receiver||lEvents[i].sendtime==info.sendtime)))
            continue;
        ui->tableWidget->setItem(index,0,new QTableWidgetItem(QString::number(i)));
        ui->tableWidget->setItem(index,1,new QTableWidgetItem(lEvents[i].number));
        ui->tableWidget->setItem(index,2,new QTableWidgetItem(lEvents[i].sender));
        ui->tableWidget->setItem(index,3,new QTableWidgetItem(lEvents[i].receiver));
        ui->tableWidget->setItem(index,4,new QTableWidgetItem(lEvents[i].sendtime));
        ui->tableWidget->setItem(index,5,new QTableWidgetItem(lEvents[i].status));
        ui->tableWidget->setItem(index,6,new QTableWidgetItem(lEvents[i].courier));
        ui->tableWidget->setItem(index,7,new QTableWidgetItem(lEvents[i].type));
        index++;
     }

}

void mainwindow::on_distributeCourier_clicked()
{
    //获取选中的待分配快递单号
    dinfo.number=ui->le_dnumber->text();
    QSqlQuery query;
    query.exec(QString(R"(SELECT type FROM courier_delivery WHERE number='%1';)")
                   .arg(dinfo.number));

     //获取查询结果的第0个值，
     //如果结果是多行数据，可用while(query.next()){}遍历每一行
     QString type="类型";
     while(query.next()){
          type=query.value(0).toString();
     }
    if(type=="易碎品")
        pr->balance-=4;
    else if(type=="图书")
        pr->balance-=1;
    else if(type=="普通快递")
        pr->balance-=2.5;
    changeFile(1,2,this,QString("%1").arg(pr->balance));
    ui->stackedWidget->setCurrentIndex(6);
    updateCTable();

}

void mainwindow::on_confirmbutton_clicked()
{

    //对选中的快递员进行分配
    dinfo.courier=ui->le_courier->text();
    auto ptr = deliverysql::getinstance();
    DeliveryInfo info;
    info.number=dinfo.number;
    info.courier=dinfo.courier;
    ptr->updateDCInfo(info);
    QMessageBox::information(nullptr,"信息","分配成功！");
}

void mainwindow::on_confirmcollect_clicked()
{
    QList<QTableWidgetItem*> items = ui->collectTable->selectedItems();
    DeliveryInfo info;
    auto ptr = deliverysql::getinstance();
    int count = items.count();

    for(int i = 0; i < count; i++)
        {
            QTableWidgetItem *item = items.at(i);
            info.number = item->text(); //获取揽收的单号
            ptr->collectDelInfo(info);
            //将一半的快递费转给快递员
            QSqlQuery query;
            query.exec(QString(R"(SELECT type FROM courier_delivery WHERE number='%1';)")
                           .arg(info.number));

             //获取查询结果的第0个值，
             //如果结果是多行数据，可用while(query.next()){}遍历每一行
             QString type="类型";
             while(query.next()){
                  type=query.value(0).toString();
             }
            if(type=="易碎品")
                pr->balance+=4.00;
            else if(type=="图书")
                pr->balance+=1.00;
            else if(type=="普通快递")
                pr->balance+=2.50;
            changeFile(2,2,this,QString("%1").arg(pr->balance));
        }
    QMessageBox::information(nullptr,"信息","揽收成功！");
    updateCDUTable();

}

void mainwindow::on_confirmsearch_clicked()
{
    DeliveryInfo info;
    info.number = ui->le_courierdelivery->text();
    info.sender = ui->le_courierdelivery->text();
    info.receiver = ui->le_courierdelivery->text();
    info.sendtime = ui->le_courierdelivery->text();
    info.status=ui->le_courierdelivery->text();
    //准备表格
    ui->searchCDTable->clear();
    ui->searchCDTable->setColumnCount(8);
    QStringList l;
    l<<"序号"<<"单号"<<"发件人"<<"收件人"<<"发件时间"<<"快件状态"<<"快递员"<<"快件类型";
    ui->searchCDTable->setHorizontalHeaderLabels(l);
    //数据库准备
    m_ptrdSql = deliverysql::getinstance();
    m_ptrdSql ->init();
    m_ptrcSql = couriersql::getinstance();
    m_ptrcSql ->init();
    auto cnt1 = m_ptrdSql ->getDelCnt();
    QList<DeliveryInfo> lEvents = m_ptrdSql->getPageDelivery(0,cnt1);
    ui->tableWidget->setRowCount(cnt1);
    auto cnt2 = m_ptrcSql ->getCourierCnt();
    QList<CourierInfo> lCourier = m_ptrcSql->getPageCourier(0,cnt2);
    QString strFilter;
    //找到该账号用户所对应的姓名
    for(int i = 0;i<lCourier.size();i++)
    {
        if(lCourier[i].account==pr->account){
           strFilter=lCourier[i].name;
           break;
        }
     }
    int index=0;
    for(int i = 0;i<lEvents.size();i++)
    {
        //如果收件人和发件人都不是用户，表格不显示
        if(!((lEvents[i].courier==strFilter||lEvents[i].receiver==strFilter)&&(lEvents[i].number==info.number||lEvents[i].sender==info.sender||lEvents[i].receiver==info.receiver||lEvents[i].sendtime==info.sendtime||lEvents[i].status==info.status)))
            continue;
        ui->searchCDTable->setItem(index,0,new QTableWidgetItem(QString::number(index)));
        ui->searchCDTable->setItem(index,1,new QTableWidgetItem(lEvents[i].number));
        ui->searchCDTable->setItem(index,2,new QTableWidgetItem(lEvents[i].sender));
        ui->searchCDTable->setItem(index,3,new QTableWidgetItem(lEvents[i].receiver));
        ui->searchCDTable->setItem(index,4,new QTableWidgetItem(lEvents[i].sendtime));
        ui->searchCDTable->setItem(index,5,new QTableWidgetItem(lEvents[i].status));
        ui->searchCDTable->setItem(index,6,new QTableWidgetItem(lEvents[i].courier));
        ui->searchCDTable->setItem(index,7,new QTableWidgetItem(lEvents[i].type));
        index++;
     }
}

void mainwindow::on_confirmsearch_courier_clicked()
{

    CourierInfo info;
    info.name = ui->le_searchcourier->text();
    info.account = ui->le_searchcourier->text();
    ui->searchCTable->clear();
    ui->searchCTable->setColumnCount(4);
    QStringList l;
    l<<"序号"<<"姓名"<<"电话号码"<<"账号";
    ui->searchCTable->setHorizontalHeaderLabels(l);
    m_ptrcSql = couriersql::getinstance();
    m_ptrcSql ->init();
    auto cnt = m_ptrcSql ->getCourierCnt();
    QList<CourierInfo> lCourier = m_ptrcSql->getPageCourier(0,cnt);
    ui->searchCTable->setRowCount(cnt);
    for(int i = 0;i<lCourier.size();i++)
    {
        if(!(lCourier[i].name==info.name||lCourier[i].account==info.account))
            continue;
        ui->searchCTable->setItem(i,0,new QTableWidgetItem(QString::number(i)));
        ui->searchCTable->setItem(i,1,new QTableWidgetItem(lCourier[i].name));
        ui->searchCTable->setItem(i,2,new QTableWidgetItem(lCourier[i].phonenumber));
        ui->searchCTable->setItem(i,3,new QTableWidgetItem(lCourier[i].account));
    }

}
