#-------------------------------------------------
#
# Project created by QtCreator 2014-10-17T14:43:48
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sqlite_DB
TEMPLATE = app


SOURCES += main.cpp \
        CUtpsDataObject.cpp \
        User.cpp \
        Student.cpp \
        Term.cpp \
        Course.cpp \
        PurchasableItem.cpp \
        Textbook.cpp \
        Chapter.cpp \
        Section.cpp \
        paymentInformation.cpp \
        BillingAddress.cpp \
        CreditCardInformation.cpp \
        ShoppingCart.cpp \
    QueryControl.cpp


HEADERS  += \
        CUtpsDataObject.h \
        User.h \
        Student.h \
        Term.h \
        Course.h \
        PurchasableItem.h \
        Textbook.h \
        Chapter.h \
        Section.h \
        paymentInformation.h \
        BillingAddress.h \
        CreditCardInformation.h \
        ShoppingCart.h \
    QueryControl.h
