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
    createchapterformwindow.cpp \
    ManageContentControl.cpp \
    Term.cpp \
    CUtpsDataObject.cpp \
    Textbook.cpp \
    Chapter.cpp \
    Section.cpp \
    PurchaseablItem.cpp \
    StudentInterfaceWindow.cpp

HEADERS  += mainwindow.h \
    ContentManagerInterfaceWindow.h \
    managetextbooksinterfacewindow.h \
    ManageContentControl.h \
    types.h \
    Term.h \
    CUtpsDataObject.h \
    createtextbookformwindow.h \
    createchapterformwindow.h \
    Textbook.h \
    Chapter.h \
    Section.h \
    PurchasableItem.h \
    StudentInterfaceWindow.h

FORMS    += mainwindow.ui \
    ContentManagerInterfaceWindow.ui \
    managetextbooksinterfacewindow.ui \
    createtextbookformwindow.ui \
    createchapterformwindow.ui \
    StudentInterfaceWindow.ui
