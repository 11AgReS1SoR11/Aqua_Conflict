QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ai.cpp \
    battlefield.cpp \
    battlesolo.cpp \
    battletogether.cpp \
    battlewindow.cpp \
    cell.cpp \
    easyai.cpp \
    getmodewindow.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    mediumai.cpp \
    mylib.cpp \
    settings.cpp \
    startchoosewin.cpp

HEADERS += \
    ai.h \
    battlefield.h \
    battlesolo.h \
    battletogether.h \
    battlewindow.h \
    cell.h \
    easyai.h \
    getmodewindow.h \
    mainwindow.h \
    map.h \
    mediumai.h \
    mylib.h \
    settings.h \
    startchoosewin.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
