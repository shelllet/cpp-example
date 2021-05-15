#-------------------------------------------------
#
# Project created by QtCreator 2019-08-19T10:51:18
#
#-------------------------------------------------

QT       += core gui qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = shelllet
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        dialog.cpp \
        main.cpp \
        mainwindow.cpp \
        setting.cpp \
        tablemodel.cpp \
        workerthread.cpp

HEADERS += \
        dialog.h \
        mainwindow.h \
        setting.h \
        tablemodel.h \
        workerthread.h

FORMS += \
        dialog.ui \
        mainwindow.ui \
        setting.ui

RESOURCES += \
    shelllet.qrc

DISTFILES +=

RC_ICONS = favicon.ico

