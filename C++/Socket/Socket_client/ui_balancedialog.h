/********************************************************************************
** Form generated from reading UI file 'balancedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BALANCEDIALOG_H
#define UI_BALANCEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_BalanceDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLabel *balencelabel;
    QLabel *label;

    void setupUi(QDialog *BalanceDialog)
    {
        if (BalanceDialog->objectName().isEmpty())
            BalanceDialog->setObjectName(QString::fromUtf8("BalanceDialog"));
        BalanceDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(BalanceDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit = new QLineEdit(BalanceDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(140, 160, 181, 21));
        label_2 = new QLabel(BalanceDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 160, 81, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        balencelabel = new QLabel(BalanceDialog);
        balencelabel->setObjectName(QString::fromUtf8("balencelabel"));
        balencelabel->setGeometry(QRect(160, 120, 72, 15));
        label = new QLabel(BalanceDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 120, 101, 21));
        label->setFont(font);

        retranslateUi(BalanceDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), BalanceDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), BalanceDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(BalanceDialog);
    } // setupUi

    void retranslateUi(QDialog *BalanceDialog)
    {
        BalanceDialog->setWindowTitle(QCoreApplication::translate("BalanceDialog", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("BalanceDialog", "\345\205\205\345\200\274", nullptr));
        balencelabel->setText(QCoreApplication::translate("BalanceDialog", "TextLabel", nullptr));
        label->setText(QCoreApplication::translate("BalanceDialog", "\345\275\223\345\211\215\344\275\231\351\242\235", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BalanceDialog: public Ui_BalanceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BALANCEDIALOG_H
