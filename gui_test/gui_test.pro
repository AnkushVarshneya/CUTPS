#-------------------------------------------------
#
# Project created by QtCreator 2014-10-16T13:15:38
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui_test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    User.h \
    Student.h \
    ContentManager.h

FORMS    += mainwindow.ui
