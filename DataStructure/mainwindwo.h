#ifndef MAINWINDWO_H
#define MAINWINDWO_H

#include <QWidget>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QApplication>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>
#include <QMutex>
#include <QString>
#include <qapplication.h>
#include <QMessageBox>
#include "page_login.h"
#include "qtsgs.h"
#include "dialog_addpe.h"
#include "eventsql.h"
#include "update.h"
#include "filecompress.h"
#include "dlg_setalarm.h"
#include "timesort.h"
#include "Search.h"

namespace Ui {
class MainWindwo;
}

class MainWindwo : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindwo(QWidget *parent = nullptr);
    ~MainWindwo();
    static MainWindwo *ptrmainWindwo;
    static MainWindwo *getinstance()
    {
        if(nullptr == ptrmainWindwo )
            ptrmainWindwo = new MainWindwo ;
        return ptrmainWindwo;
    }
    void timerEvent(QTimerEvent*);
    void paintEvent(QPaintEvent*);
    //void WriteData(QtMsgType, const QMessageLogContext &, const QString &);//将信息写入日志文件
private slots:

    void on_switch_2_clicked();

    void on_add_clicked();

    void on_load_clicked();

    void on_search_clicked();

    void on_search_2_clicked();

    void on_fastTime_clicked();

    void on_stopTime_clicked();

    void on_start_clicked();

    void on_set_clicked();

    void on_bytime_clicked();

private:
    Ui::MainWindwo *ui;
    Page_login m_dlgLogin;
    Dialog_addpe m_dialog_addpe;
    eventSql *m_ptreventSql;
    void updateTable();
    int day,hour, minute, second;//时分秒
    int TimerID;//计时器ID
    int myday,myhour,myminute;//设置的闹钟时间
};


#endif // MAINWINDWO_H
