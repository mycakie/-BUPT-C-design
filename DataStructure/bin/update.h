#ifndef UPDATE_H
#define UPDATE_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTimer>
#include "filecompress.h"

namespace Ui {
class update;
}

class update : public QWidget
{
    Q_OBJECT

public:
    explicit update(QWidget *parent = nullptr);
    ~update();
    void updateFile();


private slots:
    void on_btn_update_clicked();

    void on_pushButton_clicked();

    void on_search_clicked();

private:
    Ui::update *ui;
    QString m_strDataPath;
    QString m_strunPath;
    QStandardItemModel m_model;
    QTimer m_timer;
    FileCompress * com;
};

#endif // UPDATE_H
