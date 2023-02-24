#include "dlg_setalarm.h"
#include "ui_dlg_setalarm.h"
#include <QDebug>
#include <QMessageBox>
dlg_setalarm::dlg_setalarm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlg_setalarm)
{
    ui->setupUi(this);
}

dlg_setalarm::~dlg_setalarm()
{
    delete ui;
}

void dlg_setalarm::on_Button_accepted()
{
    setday = ui->weekBox->currentIndex();
    sethour = ui->hourBox->currentIndex();
    setminute = ui->minuteBox->currentIndex();
    QMessageBox::information(nullptr,"闹钟","设置成功");
    qDebug()<<"用户设置了闹钟";
}

void dlg_setalarm::on_Button_rejected()
{
    this->close();
}
