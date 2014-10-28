#-------------------------------------------------
#
# Project created by QtCreator 2014-10-16T13:15:38
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui_test
TEMPLATE = app


SOURCES +=\
        mainwindow.cpp \
    connectionmanager.cpp \
    BillingAddress.cpp \
    CUtpsDataObject.cpp \
    main.cpp \
    origmain2.cpp

HEADERS  += mainwindow.h \
    User.h \
    Student.h \
    ContentManager.h \
    PaymentInformation.h \
    BillingAddress.h \
    CreditCardInformation.h \
    Course.h \
    Textbook.h \
    PurchasableItem.h \
    Chapter.h \
    Section.h \
    ShoppingCart.h \
    connectionmanager.h \
    Term.h \
    CUtpsDataObject.h


FORMS    += mainwindow.ui
