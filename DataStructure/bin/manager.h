#ifndef MANAGER_H
#define MANAGER_H

#include <QWidget>
#include "page_login.h"
#include "dlg_addclass.h"
#include "dlg_edit.h"
#include "eventsql.h"

namespace Ui {
class manager;
}

class manager : public QWidget
{
    Q_OBJECT

public:
    explicit manager(QWidget *parent = nullptr);
    ~manager();

private slots:
    void on_load_clicked();

    void on_add_clicked();

    void on_edit_clicked();

private:
    Ui::manager *ui;
    Page_login m_dlgLogin;
    dlg_addclass m_dlgaddclass;
    dlg_edit m_dlgedit;
    eventSql *m_ptreventSql;
    void updateTable();
};

#endif // MANAGER_H
