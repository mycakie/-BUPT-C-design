#include "page_login.h"
#include "ui_page_login.h"

Page_login::Page_login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page_login)
{
    ui->setupUi(this);
}

Page_login::~Page_login()
{
    delete ui;
}

void Page_login::on_btn_login_clicked()
{
   //数据库查找用户名密码
   //如果失败就提示
   //成功进入主界面
    QString strFilter = ui->le_name->text();
    if(strFilter == "2020211483")
       emit sendLoginSuccessStu();
    if (strFilter == "admin")
       emit sendLoginSuccessMan();
    this ->close();

}

void Page_login::on_btn_exit_clicked()
{
    //退出登录
    exit(0);
}
