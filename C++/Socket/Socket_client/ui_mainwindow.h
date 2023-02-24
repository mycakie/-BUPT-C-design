/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwindow
{
public:
    QAction *actionlogin;
    QAction *actionchange_password;
    QAction *actionbalance;
    QAction *actionlogout;
    QAction *actionsearch_delivery;
    QAction *actiondeliverymanage;
    QAction *actionsearch_user;
    QAction *actionsearch_courier;
    QAction *actioncollect_delivery;
    QAction *actionsearch_courierdelivery;
    QAction *actiondistribute;
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *loginpage;
    QComboBox *comboBox;
    QPushButton *LoginButton;
    QPushButton *RegisterButton;
    QLabel *name;
    QLabel *password;
    QLineEdit *le_name;
    QLineEdit *le_pw;
    QWidget *pagemgm;
    QWidget *widget_3;
    QGridLayout *gridLayout_2;
    QPushButton *SingforD;
    QPushButton *send;
    QTableWidget *tableWidget;
    QLineEdit *d_uinfo;
    QPushButton *dsearch;
    QWidget *searchdelivery;
    QLineEdit *le_number;
    QPushButton *searchbutton;
    QTableWidget *searchdtable;
    QWidget *page;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label;
    QWidget *searchuser;
    QLineEdit *le_user;
    QPushButton *searchbutton_2;
    QTableWidget *searchutable;
    QWidget *distributecourier;
    QTableWidget *distributeTable;
    QPushButton *distributeCourier;
    QLineEdit *le_dnumber;
    QWidget *page_2;
    QTableWidget *distributeCTable;
    QPushButton *confirmbutton;
    QLineEdit *le_courier;
    QWidget *page_3;
    QTableWidget *collectTable;
    QLabel *label_2;
    QPushButton *confirmcollect;
    QWidget *page_4;
    QTableWidget *searchCDTable;
    QLineEdit *le_courierdelivery;
    QPushButton *confirmsearch;
    QWidget *page_5;
    QTableWidget *searchCTable;
    QLineEdit *le_searchcourier;
    QPushButton *confirmsearch_courier;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *mainwindow)
    {
        if (mainwindow->objectName().isEmpty())
            mainwindow->setObjectName(QString::fromUtf8("mainwindow"));
        mainwindow->resize(800, 600);
        mainwindow->setStyleSheet(QString::fromUtf8(""));
        actionlogin = new QAction(mainwindow);
        actionlogin->setObjectName(QString::fromUtf8("actionlogin"));
        actionchange_password = new QAction(mainwindow);
        actionchange_password->setObjectName(QString::fromUtf8("actionchange_password"));
        actionbalance = new QAction(mainwindow);
        actionbalance->setObjectName(QString::fromUtf8("actionbalance"));
        actionlogout = new QAction(mainwindow);
        actionlogout->setObjectName(QString::fromUtf8("actionlogout"));
        actionsearch_delivery = new QAction(mainwindow);
        actionsearch_delivery->setObjectName(QString::fromUtf8("actionsearch_delivery"));
        actiondeliverymanage = new QAction(mainwindow);
        actiondeliverymanage->setObjectName(QString::fromUtf8("actiondeliverymanage"));
        actionsearch_user = new QAction(mainwindow);
        actionsearch_user->setObjectName(QString::fromUtf8("actionsearch_user"));
        actionsearch_courier = new QAction(mainwindow);
        actionsearch_courier->setObjectName(QString::fromUtf8("actionsearch_courier"));
        actioncollect_delivery = new QAction(mainwindow);
        actioncollect_delivery->setObjectName(QString::fromUtf8("actioncollect_delivery"));
        actionsearch_courierdelivery = new QAction(mainwindow);
        actionsearch_courierdelivery->setObjectName(QString::fromUtf8("actionsearch_courierdelivery"));
        actiondistribute = new QAction(mainwindow);
        actiondistribute->setObjectName(QString::fromUtf8("actiondistribute"));
        centralwidget = new QWidget(mainwindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 801, 501));
        stackedWidget->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/res/3.jpg);"));
        loginpage = new QWidget();
        loginpage->setObjectName(QString::fromUtf8("loginpage"));
        comboBox = new QComboBox(loginpage);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(30, 360, 91, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        comboBox->setFont(font);
        LoginButton = new QPushButton(loginpage);
        LoginButton->setObjectName(QString::fromUtf8("LoginButton"));
        LoginButton->setGeometry(QRect(150, 360, 231, 33));
        LoginButton->setFont(font);
        RegisterButton = new QPushButton(loginpage);
        RegisterButton->setObjectName(QString::fromUtf8("RegisterButton"));
        RegisterButton->setGeometry(QRect(410, 360, 231, 33));
        RegisterButton->setFont(font);
        name = new QLabel(loginpage);
        name->setObjectName(QString::fromUtf8("name"));
        name->setGeometry(QRect(120, 140, 72, 28));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Agency FB"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        name->setFont(font1);
        password = new QLabel(loginpage);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(120, 240, 48, 28));
        password->setFont(font1);
        le_name = new QLineEdit(loginpage);
        le_name->setObjectName(QString::fromUtf8("le_name"));
        le_name->setGeometry(QRect(240, 140, 383, 31));
        le_pw = new QLineEdit(loginpage);
        le_pw->setObjectName(QString::fromUtf8("le_pw"));
        le_pw->setGeometry(QRect(240, 240, 383, 31));
        le_pw->setEchoMode(QLineEdit::Password);
        stackedWidget->addWidget(loginpage);
        pagemgm = new QWidget();
        pagemgm->setObjectName(QString::fromUtf8("pagemgm"));
        widget_3 = new QWidget(pagemgm);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(620, 140, 131, 131));
        gridLayout_2 = new QGridLayout(widget_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        SingforD = new QPushButton(widget_3);
        SingforD->setObjectName(QString::fromUtf8("SingforD"));
        SingforD->setFont(font);

        gridLayout_2->addWidget(SingforD, 0, 0, 1, 1);

        send = new QPushButton(widget_3);
        send->setObjectName(QString::fromUtf8("send"));
        send->setFont(font);

        gridLayout_2->addWidget(send, 1, 0, 1, 1);

        tableWidget = new QTableWidget(pagemgm);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(40, 90, 571, 411));
        d_uinfo = new QLineEdit(pagemgm);
        d_uinfo->setObjectName(QString::fromUtf8("d_uinfo"));
        d_uinfo->setGeometry(QRect(50, 40, 391, 31));
        dsearch = new QPushButton(pagemgm);
        dsearch->setObjectName(QString::fromUtf8("dsearch"));
        dsearch->setGeometry(QRect(460, 40, 111, 31));
        dsearch->setFont(font);
        stackedWidget->addWidget(pagemgm);
        searchdelivery = new QWidget();
        searchdelivery->setObjectName(QString::fromUtf8("searchdelivery"));
        le_number = new QLineEdit(searchdelivery);
        le_number->setObjectName(QString::fromUtf8("le_number"));
        le_number->setGeometry(QRect(10, 30, 281, 21));
        searchbutton = new QPushButton(searchdelivery);
        searchbutton->setObjectName(QString::fromUtf8("searchbutton"));
        searchbutton->setGeometry(QRect(300, 20, 101, 31));
        searchbutton->setFont(font);
        searchdtable = new QTableWidget(searchdelivery);
        searchdtable->setObjectName(QString::fromUtf8("searchdtable"));
        searchdtable->setGeometry(QRect(10, 70, 641, 421));
        stackedWidget->addWidget(searchdelivery);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        label_3 = new QLabel(page);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 160, 121, 91));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Agency FB"));
        font2.setPointSize(20);
        font2.setBold(true);
        font2.setWeight(75);
        label_3->setFont(font2);
        label_4 = new QLabel(page);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(180, 190, 141, 31));
        label_4->setFont(font1);
        label = new QLabel(page);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(340, 50, 361, 331));
        label->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/res/740.JPG);\n"
"background-repeat:no-repeat;\n"
"background-position:center;"));
        stackedWidget->addWidget(page);
        searchuser = new QWidget();
        searchuser->setObjectName(QString::fromUtf8("searchuser"));
        le_user = new QLineEdit(searchuser);
        le_user->setObjectName(QString::fromUtf8("le_user"));
        le_user->setGeometry(QRect(10, 40, 281, 21));
        searchbutton_2 = new QPushButton(searchuser);
        searchbutton_2->setObjectName(QString::fromUtf8("searchbutton_2"));
        searchbutton_2->setGeometry(QRect(310, 30, 101, 31));
        searchbutton_2->setFont(font);
        searchutable = new QTableWidget(searchuser);
        searchutable->setObjectName(QString::fromUtf8("searchutable"));
        searchutable->setGeometry(QRect(10, 70, 671, 421));
        stackedWidget->addWidget(searchuser);
        distributecourier = new QWidget();
        distributecourier->setObjectName(QString::fromUtf8("distributecourier"));
        distributeTable = new QTableWidget(distributecourier);
        distributeTable->setObjectName(QString::fromUtf8("distributeTable"));
        distributeTable->setGeometry(QRect(30, 80, 581, 421));
        distributeCourier = new QPushButton(distributecourier);
        distributeCourier->setObjectName(QString::fromUtf8("distributeCourier"));
        distributeCourier->setGeometry(QRect(440, 20, 111, 41));
        distributeCourier->setFont(font);
        le_dnumber = new QLineEdit(distributecourier);
        le_dnumber->setObjectName(QString::fromUtf8("le_dnumber"));
        le_dnumber->setGeometry(QRect(110, 30, 311, 31));
        stackedWidget->addWidget(distributecourier);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        distributeCTable = new QTableWidget(page_2);
        distributeCTable->setObjectName(QString::fromUtf8("distributeCTable"));
        distributeCTable->setGeometry(QRect(30, 70, 581, 421));
        confirmbutton = new QPushButton(page_2);
        confirmbutton->setObjectName(QString::fromUtf8("confirmbutton"));
        confirmbutton->setGeometry(QRect(410, 20, 111, 41));
        confirmbutton->setFont(font);
        le_courier = new QLineEdit(page_2);
        le_courier->setObjectName(QString::fromUtf8("le_courier"));
        le_courier->setGeometry(QRect(40, 30, 351, 31));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        collectTable = new QTableWidget(page_3);
        collectTable->setObjectName(QString::fromUtf8("collectTable"));
        collectTable->setGeometry(QRect(30, 80, 581, 421));
        label_2 = new QLabel(page_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 20, 361, 41));
        label_2->setFont(font1);
        confirmcollect = new QPushButton(page_3);
        confirmcollect->setObjectName(QString::fromUtf8("confirmcollect"));
        confirmcollect->setGeometry(QRect(620, 140, 111, 41));
        confirmcollect->setFont(font);
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        searchCDTable = new QTableWidget(page_4);
        searchCDTable->setObjectName(QString::fromUtf8("searchCDTable"));
        searchCDTable->setGeometry(QRect(50, 80, 581, 421));
        le_courierdelivery = new QLineEdit(page_4);
        le_courierdelivery->setObjectName(QString::fromUtf8("le_courierdelivery"));
        le_courierdelivery->setGeometry(QRect(50, 40, 351, 31));
        confirmsearch = new QPushButton(page_4);
        confirmsearch->setObjectName(QString::fromUtf8("confirmsearch"));
        confirmsearch->setGeometry(QRect(420, 30, 111, 41));
        confirmsearch->setFont(font);
        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        searchCTable = new QTableWidget(page_5);
        searchCTable->setObjectName(QString::fromUtf8("searchCTable"));
        searchCTable->setGeometry(QRect(60, 70, 581, 421));
        le_searchcourier = new QLineEdit(page_5);
        le_searchcourier->setObjectName(QString::fromUtf8("le_searchcourier"));
        le_searchcourier->setGeometry(QRect(60, 30, 351, 31));
        confirmsearch_courier = new QPushButton(page_5);
        confirmsearch_courier->setObjectName(QString::fromUtf8("confirmsearch_courier"));
        confirmsearch_courier->setGeometry(QRect(430, 20, 111, 41));
        confirmsearch_courier->setFont(font);
        stackedWidget->addWidget(page_5);
        mainwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mainwindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        mainwindow->setMenuBar(menubar);
        statusBar = new QStatusBar(mainwindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        mainwindow->setStatusBar(statusBar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu->addAction(actionlogin);
        menu->addAction(actionchange_password);
        menu->addAction(actiondeliverymanage);
        menu->addAction(actionbalance);
        menu->addAction(actionlogout);
        menu_2->addAction(actionsearch_delivery);
        menu_2->addAction(actionsearch_user);
        menu_2->addAction(actionsearch_courier);
        menu_2->addAction(actiondistribute);
        menu_3->addAction(actioncollect_delivery);
        menu_3->addAction(actionsearch_courierdelivery);

        retranslateUi(mainwindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(mainwindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainwindow)
    {
        mainwindow->setWindowTitle(QCoreApplication::translate("mainwindow", "\347\211\251\346\265\201\347\256\241\347\220\206\347\263\273\347\273\237", nullptr));
        actionlogin->setText(QCoreApplication::translate("mainwindow", "\347\231\273\345\275\225", nullptr));
        actionlogin->setIconText(QCoreApplication::translate("mainwindow", "\347\231\273\345\275\225", nullptr));
#if QT_CONFIG(tooltip)
        actionlogin->setToolTip(QCoreApplication::translate("mainwindow", "\347\231\273\345\275\225", nullptr));
#endif // QT_CONFIG(tooltip)
        actionchange_password->setText(QCoreApplication::translate("mainwindow", "\344\277\256\346\224\271\345\257\206\347\240\201", nullptr));
        actionchange_password->setIconText(QCoreApplication::translate("mainwindow", "\344\277\256\346\224\271\345\257\206\347\240\201", nullptr));
#if QT_CONFIG(tooltip)
        actionchange_password->setToolTip(QCoreApplication::translate("mainwindow", "\344\277\256\346\224\271\345\257\206\347\240\201", nullptr));
#endif // QT_CONFIG(tooltip)
        actionbalance->setText(QCoreApplication::translate("mainwindow", "\344\275\231\351\242\235\347\256\241\347\220\206", nullptr));
        actionbalance->setIconText(QCoreApplication::translate("mainwindow", "\344\275\231\351\242\235\347\256\241\347\220\206", nullptr));
#if QT_CONFIG(tooltip)
        actionbalance->setToolTip(QCoreApplication::translate("mainwindow", "\344\275\231\351\242\235\347\256\241\347\220\206", nullptr));
#endif // QT_CONFIG(tooltip)
        actionlogout->setText(QCoreApplication::translate("mainwindow", "\346\263\250\351\224\200", nullptr));
        actionsearch_delivery->setText(QCoreApplication::translate("mainwindow", "\346\237\245\350\257\242\345\277\253\351\200\222", nullptr));
#if QT_CONFIG(tooltip)
        actionsearch_delivery->setToolTip(QCoreApplication::translate("mainwindow", "\346\237\245\350\257\242\347\256\241\347\220\206", nullptr));
#endif // QT_CONFIG(tooltip)
        actiondeliverymanage->setText(QCoreApplication::translate("mainwindow", "\345\277\253\351\200\222\347\256\241\347\220\206", nullptr));
        actionsearch_user->setText(QCoreApplication::translate("mainwindow", "\346\237\245\350\257\242\347\224\250\346\210\267", nullptr));
        actionsearch_courier->setText(QCoreApplication::translate("mainwindow", "\346\237\245\350\257\242\345\277\253\351\200\222\345\221\230", nullptr));
        actioncollect_delivery->setText(QCoreApplication::translate("mainwindow", "\346\217\275\346\224\266\345\277\253\351\200\222", nullptr));
        actionsearch_courierdelivery->setText(QCoreApplication::translate("mainwindow", "\346\237\245\350\257\242\345\277\253\351\200\222", nullptr));
        actiondistribute->setText(QCoreApplication::translate("mainwindow", "\345\210\206\351\205\215\345\277\253\351\200\222\345\221\230", nullptr));
        LoginButton->setText(QCoreApplication::translate("mainwindow", "\347\231\273\345\275\225", nullptr));
        RegisterButton->setText(QCoreApplication::translate("mainwindow", "\346\263\250\345\206\214", nullptr));
        name->setText(QCoreApplication::translate("mainwindow", "\347\224\250\346\210\267\345\220\215", nullptr));
        password->setText(QCoreApplication::translate("mainwindow", "\345\257\206\347\240\201", nullptr));
        SingforD->setText(QCoreApplication::translate("mainwindow", "\347\255\276\346\224\266\345\277\253\351\200\222", nullptr));
        send->setText(QCoreApplication::translate("mainwindow", "\345\217\221\351\200\201\345\277\253\351\200\222", nullptr));
        d_uinfo->setPlaceholderText(QCoreApplication::translate("mainwindow", "\350\257\267\350\276\223\345\205\245\346\203\263\350\246\201\346\237\245\346\211\276\347\232\204\345\277\253\351\200\222\344\277\241\346\201\257", nullptr));
        dsearch->setText(QCoreApplication::translate("mainwindow", "\346\237\245\346\211\276\345\277\253\351\200\222", nullptr));
        le_number->setInputMask(QString());
        le_number->setText(QString());
        le_number->setPlaceholderText(QCoreApplication::translate("mainwindow", "\350\257\267\350\276\223\345\205\245\346\203\263\350\246\201\346\237\245\350\257\242\347\232\204\345\277\253\351\200\222\347\233\270\345\205\263\344\277\241\346\201\257", nullptr));
        searchbutton->setText(QCoreApplication::translate("mainwindow", "\346\237\245\350\257\242", nullptr));
        label_3->setText(QCoreApplication::translate("mainwindow", "\346\254\242\350\277\216\357\274\201", nullptr));
        label_4->setText(QCoreApplication::translate("mainwindow", "TextLabel", nullptr));
        label->setText(QString());
        le_user->setInputMask(QString());
        le_user->setText(QString());
        le_user->setPlaceholderText(QCoreApplication::translate("mainwindow", "\350\257\267\350\276\223\345\205\245\346\203\263\350\246\201\346\237\245\350\257\242\347\232\204\347\224\250\346\210\267\347\233\270\345\205\263\344\277\241\346\201\257", nullptr));
        searchbutton_2->setText(QCoreApplication::translate("mainwindow", "\346\237\245\350\257\242", nullptr));
        distributeCourier->setText(QCoreApplication::translate("mainwindow", "\347\241\256\345\256\232", nullptr));
        le_dnumber->setPlaceholderText(QCoreApplication::translate("mainwindow", "\350\257\267\350\276\223\345\205\245\344\275\240\346\203\263\350\246\201\345\210\206\351\205\215\345\277\253\351\200\222\345\221\230\347\232\204\345\277\253\351\200\222\345\215\225\345\217\267", nullptr));
        confirmbutton->setText(QCoreApplication::translate("mainwindow", "\347\241\256\345\256\232\345\210\206\351\205\215", nullptr));
        le_courier->setPlaceholderText(QCoreApplication::translate("mainwindow", "\350\257\267\350\276\223\345\205\245\344\275\240\351\200\211\346\213\251\347\232\204\345\277\253\351\200\222\345\221\230", nullptr));
        label_2->setText(QCoreApplication::translate("mainwindow", "\350\257\267\347\202\271\345\207\273\344\275\240\346\217\275\346\224\266\347\232\204\345\277\253\351\200\222\345\215\225\345\217\267\342\206\223\342\206\223", nullptr));
        confirmcollect->setText(QCoreApplication::translate("mainwindow", "\347\241\256\345\256\232\346\217\275\346\224\266", nullptr));
        le_courierdelivery->setPlaceholderText(QCoreApplication::translate("mainwindow", "\350\257\267\350\276\223\345\205\245\344\275\240\346\203\263\350\246\201\346\237\245\346\211\276\347\232\204\345\277\253\351\200\222\344\277\241\346\201\257", nullptr));
        confirmsearch->setText(QCoreApplication::translate("mainwindow", "\346\237\245\346\211\276", nullptr));
        le_searchcourier->setPlaceholderText(QCoreApplication::translate("mainwindow", "\350\257\267\350\276\223\345\205\245\344\275\240\346\203\263\350\246\201\346\237\245\346\211\276\347\232\204\345\277\253\351\200\222\345\221\230\344\277\241\346\201\257", nullptr));
        confirmsearch_courier->setText(QCoreApplication::translate("mainwindow", "\346\237\245\346\211\276", nullptr));
        menu->setTitle(QCoreApplication::translate("mainwindow", "\347\224\250\346\210\267", nullptr));
        menu_2->setTitle(QCoreApplication::translate("mainwindow", "\347\256\241\347\220\206\345\221\230", nullptr));
        menu_3->setTitle(QCoreApplication::translate("mainwindow", "\345\277\253\351\200\222\345\221\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainwindow: public Ui_mainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
