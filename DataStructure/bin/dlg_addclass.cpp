#include "dlg_addclass.h"
#include "ui_dlg_addclass.h"
#include "eventsql.h"
#include "manager.h"
#include "QMessageBox"
#include <QDebug>
dlg_addclass::dlg_addclass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlg_addclass)
{
    ui->setupUi(this);
}

dlg_addclass::~dlg_addclass()
{
    delete ui;
}

void dlg_addclass::on_finish_accepted()
{
    EventInfo info;
    info.name = ui->le_name->text();
    info.teacher = ui->le_teacher->text();
    info.location = ui->le_loc->text();
    info.time = ui->le_time->text();
    info.test_time = ui->le_testtime->text();
    info.test_loc = ui->le_testloc->text();
    info.group_number = ui->lineEdit_7->text();
    auto ptr = eventSql::getinstance();
    ptr->addEve(info);
    QMessageBox::information(nullptr,"课程","添加成功");
    qDebug()<<"管理员添加课程信息";

}

void dlg_addclass::on_finish_rejected()
{
    this->hide();
}
