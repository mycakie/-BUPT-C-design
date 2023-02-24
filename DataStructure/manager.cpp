#include "manager.h"
#include "ui_manager.h"

manager::manager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::manager),
    m_ptreventSql(nullptr)
{
    ui->setupUi(this);
    m_dlgLogin.show();
    auto f = [&](){
        this->show();
    };
    connect(&m_dlgLogin,&Page_login::sendLoginSuccessMan,this,f);
}

manager::~manager()
{
    delete ui;
}

void manager::on_load_clicked()
{
    updateTable();
}

void manager::updateTable()
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

void manager::on_add_clicked()
{
    m_dlgaddclass.exec();
    updateTable();
}

void manager::on_edit_clicked()
{
    m_dlgedit.exec();
    updateTable();
}
