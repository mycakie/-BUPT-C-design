#ifndef ADDDELIVERYDIALOG_H
#define ADDDELIVERYDIALOG_H

#include <QDialog>

namespace Ui {
class adddeliverydialog;
}

class adddeliverydialog : public QDialog
{
    Q_OBJECT

public:
    explicit adddeliverydialog(QWidget *parent = nullptr);
    ~adddeliverydialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::adddeliverydialog *ui;
};

#endif // ADDDELIVERYDIALOG_H
