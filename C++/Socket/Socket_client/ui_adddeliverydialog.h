/********************************************************************************
** Form generated from reading UI file 'adddeliverydialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDDELIVERYDIALOG_H
#define UI_ADDDELIVERYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_adddeliverydialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLabel *label;
    QLineEdit *le_sender;
    QLineEdit *le_address;
    QLabel *label_3;
    QLineEdit *le_time;
    QLineEdit *le_receiver;
    QLabel *label_6;
    QLabel *label_2;
    QComboBox *comboBox;

    void setupUi(QDialog *adddeliverydialog)
    {
        if (adddeliverydialog->objectName().isEmpty())
            adddeliverydialog->setObjectName(QString::fromUtf8("adddeliverydialog"));
        adddeliverydialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(adddeliverydialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(40, 250, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        widget = new QWidget(adddeliverydialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(50, 18, 301, 221));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label_5->setFont(font);

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        le_sender = new QLineEdit(widget);
        le_sender->setObjectName(QString::fromUtf8("le_sender"));

        gridLayout->addWidget(le_sender, 0, 1, 1, 1);

        le_address = new QLineEdit(widget);
        le_address->setObjectName(QString::fromUtf8("le_address"));

        gridLayout->addWidget(le_address, 2, 1, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        le_time = new QLineEdit(widget);
        le_time->setObjectName(QString::fromUtf8("le_time"));

        gridLayout->addWidget(le_time, 3, 1, 1, 1);

        le_receiver = new QLineEdit(widget);
        le_receiver->setObjectName(QString::fromUtf8("le_receiver"));

        gridLayout->addWidget(le_receiver, 1, 1, 1, 1);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 4, 1, 1, 1);


        retranslateUi(adddeliverydialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), adddeliverydialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), adddeliverydialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(adddeliverydialog);
    } // setupUi

    void retranslateUi(QDialog *adddeliverydialog)
    {
        adddeliverydialog->setWindowTitle(QCoreApplication::translate("adddeliverydialog", "Dialog", nullptr));
        label_5->setText(QCoreApplication::translate("adddeliverydialog", "\345\217\221\350\264\247\346\227\266\351\227\264", nullptr));
        label->setText(QCoreApplication::translate("adddeliverydialog", "\345\257\204\344\273\266\344\272\272", nullptr));
        label_3->setText(QCoreApplication::translate("adddeliverydialog", "\346\224\266\350\264\247\345\234\260\345\235\200", nullptr));
        label_6->setText(QCoreApplication::translate("adddeliverydialog", "\345\277\253\344\273\266\347\261\273\345\236\213", nullptr));
        label_2->setText(QCoreApplication::translate("adddeliverydialog", "\346\224\266\344\273\266\344\272\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class adddeliverydialog: public Ui_adddeliverydialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDDELIVERYDIALOG_H
