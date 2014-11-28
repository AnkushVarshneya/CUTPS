#-------------------------------------------------
#
# Project created by QtCreator 2014-11-25T13:46:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cuTPS_gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ContentManagerInterfaceWindow.cpp

HEADERS  += mainwindow.h \
    ContentManagerInterfaceWindow.h

FORMS    += mainwindow.ui \
    studentInterfaceForm.ui \
    ContentManagerInterfaceWindow.ui
