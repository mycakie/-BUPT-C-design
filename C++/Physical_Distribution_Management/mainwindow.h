#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/qsqltablemodel.h>
#include <QStandardItemModel>
#include "user.h"
#include "deliverysql.h"
#include "usersql.h"
#include "adddeliverydialog.h"

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
private slots:

    void on_LoginButton_clicked();

    void on_RegisterButton_clicked();

    void on_SingforD_clicked();

    void on_send_clicked();

    void on_searchbutton_clicked();

    void on_searchbutton_2_clicked();

    void on_dsearch_clicked();

private:
    Ui::mainwindow *ui;
    int state; //记录登录状态
    QSqlTableModel *model; //快递数据模型
    deliverysql *m_ptrdSql;
    usersql *m_ptruSql;
    adddeliverydialog m_adddeliverydialog;
    void updateDTable();
    void updateUTable();
    void updateUDTable();
};
#endif // MAINWINDOW_H
