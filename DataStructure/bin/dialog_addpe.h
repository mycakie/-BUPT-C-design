#ifndef DIALOG_ADDPE_H
#define DIALOG_ADDPE_H

#include <QDialog>
#include "eventsql.h"

namespace Ui {
class Dialog_addpe;
}

class Dialog_addpe : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_addpe(QWidget *parent = nullptr);
    ~Dialog_addpe();

private slots:
    void on_buttonBox_accepted();

    void on_finish_accepted();

    void on_finish_rejected();

private:
    Ui::Dialog_addpe *ui;
     eventSql *m_ptreventSql;
};

#endif // DIALOG_ADDPE_H
