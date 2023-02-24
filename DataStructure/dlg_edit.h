#ifndef DLG_EDIT_H
#define DLG_EDIT_H

#include <QDialog>

namespace Ui {
class dlg_edit;
}

class dlg_edit : public QDialog
{
    Q_OBJECT

public:
    explicit dlg_edit(QWidget *parent = nullptr);
    ~dlg_edit();

private slots:
    void on_edit_accepted();

    void on_edit_rejected();

private:
    Ui::dlg_edit *ui;
};

#endif // DLG_EDIT_H
