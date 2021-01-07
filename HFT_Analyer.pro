QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += charts

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
    accountpage.cpp \
    clickablelabel.cpp \
    datapage.cpp \
    datapageitem.cpp \
    datapageitemdefault.cpp \
    datapageiteminput.cpp \
    editlabel.cpp \
    initwindow.cpp \
    linechartblockview.cpp \
    little_stratgymanageitem.cpp \
    main.cpp \
    mainwindow.cpp \
    nontitle.cpp \
    orderpage.cpp \
    orderpageitem.cpp \
    passwdchangepage.cpp \
    sponsorpage.cpp \
    stratgymanageitem.cpp \
    stratgymanageitemdefault.cpp \
    stratgymanagepage.cpp \
    testthread.cpp \
    tradingpage.cpp \
    webconfig.cpp

HEADERS += \
    accountpage.h \
    blockview.h \
    clickablelabel.h \
    datapage.h \
    datapageitem.h \
    datapageitemdefault.h \
    datapageiteminput.h \
    editlabel.h \
    initwindow.h \
    linechartblockview.h \
    little_stratgymanageitem.h \
    mainwindow.h \
    nontitle.h \
    orderpage.h \
    orderpageitem.h \
    passwdchangepage.h \
    sponsorpage.h \
    stratgymanageitem.h \
    stratgymanageitemdefault.h \
    stratgymanagepage.h \
    testthread.h \
    tradingpage.h \
    webconfig.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rcs.qrc
