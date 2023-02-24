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


int k; //记录模型中的快递数量
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
    strlist<<"用户"<<"管理员";
    ui->comboBox->addItems(strlist);
    //设置菜单栏槽函数
    connect(ui->actionlogin,&QAction::triggered,[=](){ //登录
        if(state==0){
             ui->stackedWidget->setCurrentIndex(0);
        }else{
            QMessageBox::warning(this,"警告","您已登录");
        }
    });

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
    //

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
        }else{
            path="D:\\userdata\\manager.txt";
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
                pr=new realUser(a,p,c,0);
            }else{
                pr=new manager(a,p,c,1);
            }
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
        }else{
             path="D:\\userdata\\manager.txt";
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
        l<<"序号"<<"单号"<<"发件人"<<"收件人"<<"发件时间"<<" 签收时间"<<"快件状态"<<"物品描述";
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
            ui->searchdtable->setItem(i,5,new QTableWidgetItem(lEvents[i].receivetime));
            ui->searchdtable->setItem(i,6,new QTableWidgetItem(lEvents[i].status));
            ui->searchdtable->setItem(i,7,new QTableWidgetItem(lEvents[i].detail));
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
    l<<"序号"<<"单号"<<"发件人"<<"收件人"<<"发件时间"<<" 签收时间"<<"快件状态"<<"物品描述";
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
        ui->tableWidget->setItem(index,0,new QTableWidgetItem(QString::number(i)));
        ui->tableWidget->setItem(index,1,new QTableWidgetItem(lEvents[i].number));
        ui->tableWidget->setItem(index,2,new QTableWidgetItem(lEvents[i].sender));
        ui->tableWidget->setItem(index,3,new QTableWidgetItem(lEvents[i].receiver));
        ui->tableWidget->setItem(index,4,new QTableWidgetItem(lEvents[i].sendtime));
        ui->tableWidget->setItem(index,5,new QTableWidgetItem(lEvents[i].receivetime));
        ui->tableWidget->setItem(index,6,new QTableWidgetItem(lEvents[i].status));
        ui->tableWidget->setItem(index,7,new QTableWidgetItem(lEvents[i].detail));
        index++;
     }

}

void mainwindow::on_SingforD_clicked()
{
    DeliveryInfo info;
    info.number = ui->d_info->text();
    auto ptr = deliverysql::getinstance();
    ptr->updateDelInfo(info);
    QMessageBox::information(nullptr,"信息","签收成功！");
    updateUDTable();
}

void mainwindow::on_send_clicked()
{
    m_adddeliverydialog.exec();
    //修改余额
    pr->balance-=15.00;
    changeFile(0,2,this,QString("%1").arg(pr->balance));
    //读管理员的余额
    QFile file("D:\\userdata\\manager.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
         QMessageBox::critical(this,"错误","文件读取出错");
         return;
    }
    QTextStream in(&file);
    double c=15;
    QString line=in.readLine(0);
    c+=line.section(" ",2,2).toDouble();
    changeFile(1,2,this,QString("%1").arg(c));
    updateUDTable();

}

void mainwindow::on_searchbutton_clicked()
{
     DeliveryInfo info;
     info.number = ui->le_number->text();
     info.sendtime = ui->le_number->text();
     //准备表格
     ui->searchdtable->clear();
     ui->searchdtable->setColumnCount(8);
     QStringList l;
     l<<"序号"<<"单号"<<"发件人"<<"收件人"<<"发件时间"<<" 签收时间"<<"快件状态"<<"物品描述";
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
         if(!(lEvents[i].number==info.number||lEvents[i].sendtime==info.sendtime))
             continue;
         ui->searchdtable->setItem(index,0,new QTableWidgetItem(QString::number(i)));
         ui->searchdtable->setItem(index,1,new QTableWidgetItem(lEvents[i].number));
         ui->searchdtable->setItem(index,2,new QTableWidgetItem(lEvents[i].sender));
         ui->searchdtable->setItem(index,3,new QTableWidgetItem(lEvents[i].receiver));
         ui->searchdtable->setItem(index,4,new QTableWidgetItem(lEvents[i].sendtime));
         ui->searchdtable->setItem(index,5,new QTableWidgetItem(lEvents[i].receivetime));
         ui->searchdtable->setItem(index,6,new QTableWidgetItem(lEvents[i].status));
         ui->searchdtable->setItem(index,7,new QTableWidgetItem(lEvents[i].detail));
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
    l<<"序号"<<"单号"<<"发件人"<<"收件人"<<"发件时间"<<" 签收时间"<<"快件状态"<<"物品描述";
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
        ui->tableWidget->setItem(index,5,new QTableWidgetItem(lEvents[i].receivetime));
        ui->tableWidget->setItem(index,6,new QTableWidgetItem(lEvents[i].status));
        ui->tableWidget->setItem(index,7,new QTableWidgetItem(lEvents[i].detail));
        index++;
     }

}
