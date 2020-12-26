QT       += core gui

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
    *.cpp

HEADERS += \ \
    include/ThostFtdcMdApi.h \
    include/ThostFtdcTraderApi.h \
    include/ThostFtdcUserApiDataType.h \
    include/ThostFtdcUserApiStruct.h \
    include/common.h \
    include/config.h \
    include/db.h \
    include/debug.h \
    include/extend_md_spi.h \
    include/extend_spi.h \
    include/index.h \
    include/login.h \
    include/main.h \
    include/market.h \
    include/order.h \
    include/status.h \
    include/strategy.h \
    include/subscribtion.h \
    include/util.h


FORMS += \
    login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

unix:!macx: LIBS += -L$$PWD/lib/ -lsqlapi -lthosttraderapi_se -lthostmduserapi -lcurl

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include \

DISTFILES += \
    Readme.md
