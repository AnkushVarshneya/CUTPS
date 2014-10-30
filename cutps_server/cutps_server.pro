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
    chapter.cpp \
    section.cpp

HEADERS += \
    BillingAddress.h \
    CUtpsDataObject.h \
    CUtpsServer.h \
    chapter.h \
    section.h
