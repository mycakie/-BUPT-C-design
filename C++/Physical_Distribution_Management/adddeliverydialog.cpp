#include "adddeliverydialog.h"
#include "ui_adddeliverydialog.h"
#include "deliverysql.h"
#include "mainwindow.h"
#include "QMessageBox"
adddeliverydialog::adddeliverydialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adddeliverydialog)
{
    ui->setupUi(this);
}

adddeliverydialog::~adddeliverydialog()
{
    delete ui;
}

void adddeliverydialog::on_buttonBox_accepted()
{
    DeliveryInfo info;
    info.sender = ui->le_sender->text();
    info.receiver = ui->le_receiver->text();
    info.sendtime = ui->le_time->text();
    info.detail = ui->le_detail->text();
    auto ptr = deliverysql::getinstance();
    ptr->addDel(info);
    QMessageBox::information(nullptr,"信息","快件创建成功");
}

void adddeliverydialog::on_buttonBox_rejected()
{
    this->hide();
}
