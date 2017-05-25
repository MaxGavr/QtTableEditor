#-------------------------------------------------
#
# Project created by QtCreator 2017-04-26T15:59:06
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtTableEditor
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
    mainwindow.cpp \
    model/student.cpp \
    model/database.cpp \
    manager/manager.cpp \
    table/table.cpp \
    dialogs/adddialog.cpp \
    model/xmlhandler.cpp \
    dialogs/searchdialog.cpp \
    model/searchpattern.cpp \
    dialogs/searchwidget.cpp \
    dialogs/deletedialog.cpp

HEADERS  += mainwindow.h \
    model/student.h \
    model/database.h \
    manager/manager.h \
    table/table.h \
    dialogs/adddialog.h \
    model/xmlhandler.h \
    dialogs/searchdialog.h \
    model/searchpattern.h \
    dialogs/searchwidget.h \
    dialogs/deletedialog.h

RESOURCES += \
    icons.qrc
