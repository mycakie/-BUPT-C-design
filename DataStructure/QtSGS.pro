QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Search.cpp \
    dialog_addpe.cpp \
    dlg_addclass.cpp \
    dlg_edit.cpp \
    dlg_setalarm.cpp \
    eventsql.cpp \
    filecompress.cpp \
    main.cpp \
    mainwindwo.cpp \
    manager.cpp \
    navigation.cpp \
    page_login.cpp \
    qtsgs.cpp \
    timesort.cpp \
    update.cpp

HEADERS += \
    Search.h \
    dialog_addpe.h \
    dlg_addclass.h \
    dlg_edit.h \
    dlg_setalarm.h \
    eventsql.h \
    filecompress.h \
    mainwindwo.h \
    manager.h \
    navigation.h \
    page_login.h \
    qtsgs.h \
    timesort.h \
    update.h \
    utf.h

FORMS += \
    dialog_addpe.ui \
    dlg_addclass.ui \
    dlg_edit.ui \
    dlg_setalarm.ui \
    mainwindwo.ui \
    manager.ui \
    page_login.ui \
    qtsgs.ui \
    update.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
DESTDIR = $$PWD/bin
