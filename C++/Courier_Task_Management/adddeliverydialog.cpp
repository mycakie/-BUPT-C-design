#include "adddeliverydialog.h"
#include "ui_adddeliverydialog.h"
#include "deliverysql.h"
#include "mainwindow.h"
#include "QMessageBox"
#include "package.h"
#include "package.h"

adddeliverydialog::adddeliverydialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adddeliverydialog)
{
    ui->setupUi(this);
    //设置下拉框
    QStringList strlist;
    strlist<<"易碎品"<<"图书"<<"普通快递";
    ui->comboBox->addItems(strlist);
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
    info.type = ui->comboBox->currentText();
    auto ptr = deliverysql::getinstance();
    ptr->addDel(info);   
    QMessageBox::information(nullptr,"信息","快件创建成功");
    package_type = ui->comboBox->currentIndex();
}

void adddeliverydialog::on_buttonBox_rejected()
{
    package_type = -1;
    this->hide();
}
