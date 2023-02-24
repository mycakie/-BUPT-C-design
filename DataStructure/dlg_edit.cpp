#include "dlg_edit.h"
#include "ui_dlg_edit.h"
#include "eventsql.h"
#include "manager.h"
#include "QMessageBox"
#include <QDebug>
dlg_edit::dlg_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlg_edit)
{
    ui->setupUi(this);
}

dlg_edit::~dlg_edit()
{
    delete ui;
}

void dlg_edit::on_edit_accepted()
{
    EventInfo info;
    info.name = ui->le_name->text();
    info.test_time = ui->le_testtime->text();
    info.test_loc = ui->le_testloc->text();
    auto ptr = eventSql::getinstance();
    ptr->updateEveInfo(info);
    QMessageBox::information(nullptr,"考试信息","发布成功");
    qDebug()<<"管理员发布了考试信息";
}

void dlg_edit::on_edit_rejected()
{
    this->hide();
}
