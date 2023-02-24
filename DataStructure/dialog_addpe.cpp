#include "dialog_addpe.h"
#include "ui_dialog_addpe.h"
#include "eventsql.h"
#include "mainwindwo.h"
#include "timesort.h"
#include "QMessageBox"
#include <QDebug>
Dialog_addpe::Dialog_addpe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_addpe)
{
    ui->setupUi(this);
}

Dialog_addpe::~Dialog_addpe()
{
    delete ui;
}


void Dialog_addpe::on_finish_accepted()
{
  EventInfo info;
  info.name = ui->name->text();
  info.time = ui->time->text();
  info.location = ui->location->text();
  //冲突检测
  m_ptreventSql = eventSql::getinstance();
  m_ptreventSql ->init();
  auto cnt = m_ptreventSql ->getEveCnt();
  QList<EventInfo> lEvents = m_ptreventSql->getPageEvent(0,cnt);
  bool f = 1;
  for(int i = 0;i<lEvents.size()&&f;i++)
  {
      if(lEvents[i].time.mid(1,4)==info.time.mid(1,4))
          f=0;
  }
  if(f)
  {
     auto ptr = eventSql::getinstance();
     ptr->addEve(info);
     QMessageBox::information(nullptr,"个人活动","添加成功");
     qDebug()<<"用户添加了个人活动";
  }
  else
  {
     QMessageBox::information(nullptr,"警告","时间冲突！");
     qDebug()<<"用户添加个人活动时检测到时间冲突";
  }
}

void Dialog_addpe::on_finish_rejected()
{
    this->hide();
}
