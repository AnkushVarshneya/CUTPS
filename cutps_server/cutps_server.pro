#-------------------------------------------------
#
# Project created by QtCreator 2014-10-24T13:48:05
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = cutps_server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    BillingAddress.cpp \
    CUtpsDataObject.cpp \
    CUtpsServer.cpp \
    Chapter.cpp \
    Section.cpp \
    PurchasableItem.cpp \
    Textbook.cpp

HEADERS += \
    BillingAddress.h \
    CUtpsDataObject.h \
    CUtpsServer.h \
    Section.h \
    Chapter.h \
    PurchasableItem.h \
    Textbook.h
