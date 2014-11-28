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
    ContentManagerInterfaceWindow.cpp \
    managetextbooksinterfacewindow.cpp \
    createtextbookformwindow.cpp \
    createchapterformwindow.cpp

HEADERS  += mainwindow.h \
    ContentManagerInterfaceWindow.h \
    managetextbooksinterfacewindow.h \
    createtextbookformwindow.h \
    createchapterformwindow.h

FORMS    += mainwindow.ui \
    ContentManagerInterfaceWindow.ui \
    studentinterfacewindow.ui \
    managetextbooksinterfacewindow.ui \
    createtextbookformwindow.ui \
    createchapterformwindow.ui
