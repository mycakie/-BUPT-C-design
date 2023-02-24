#ifndef DLG_SETALARM_H
#define DLG_SETALARM_H

#include <QDialog>

namespace Ui {
class dlg_setalarm;
}

class dlg_setalarm : public QDialog
{
    Q_OBJECT

public:
    explicit dlg_setalarm(QWidget *parent = nullptr);
    ~dlg_setalarm();
    int setday;
    int sethour;
    int setminute;

private slots:
    void on_Button_accepted();

    void on_Button_rejected();

private:
    Ui::dlg_setalarm *ui;
};

#endif // DLG_SETALARM_H
