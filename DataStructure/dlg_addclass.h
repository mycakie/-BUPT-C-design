#ifndef DLG_ADDCLASS_H
#define DLG_ADDCLASS_H

#include <QDialog>


namespace Ui {
class dlg_addclass;
}

class dlg_addclass : public QDialog
{
    Q_OBJECT

public:
    explicit dlg_addclass(QWidget *parent = nullptr);
    ~dlg_addclass();

private slots:
    void on_finish_accepted();

    void on_finish_rejected();

private:
    Ui::dlg_addclass *ui;
};

#endif // DLG_ADDCLASS_H
