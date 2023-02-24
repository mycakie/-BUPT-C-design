#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/qsqltablemodel.h>
#include <QStandardItemModel>
#include "user.h"
#include "deliverysql.h"
#include "usersql.h"
#include "adddeliverydialog.h"
#include "package.h"
#include "couriersql.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    mainwindow(QWidget *parent = nullptr);
    ~mainwindow();
    User *pr; //用户指针
    package *pp;//快件指针
private slots:

    void on_LoginButton_clicked();

    void on_RegisterButton_clicked();

    void on_SingforD_clicked();

    void on_send_clicked();

    void on_searchbutton_clicked();

    void on_searchbutton_2_clicked();

    void on_dsearch_clicked();

    void on_distributeCourier_clicked();

    void on_confirmbutton_clicked();

    void on_confirmcollect_clicked();

    void on_confirmsearch_clicked();

    void on_confirmsearch_courier_clicked();

private:
    Ui::mainwindow *ui;
    int state; //记录登录状态
    QSqlTableModel *model; //快递数据模型
    deliverysql *m_ptrdSql;
    usersql *m_ptruSql;
    couriersql *m_ptrcSql;
    adddeliverydialog m_adddeliverydialog;
    QSqlDatabase m_db;
    void updateDTable();//上载快递表
    void updateUTable();//上载用户表
    void updateUDTable();//上载某用户的快递表
    void updateDUTable();//上载待分配快递表
    void updateCTable();//上载快递员表
    void updateCDTable();//上载某快递员负责的快递
    void updateCDUTable();//上载某快递员待揽收的快递
};
#endif // MAINWINDOW_H
