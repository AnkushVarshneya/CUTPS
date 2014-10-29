#-------------------------------------------------
#
# Project created by QtCreator 2014-10-16T13:15:38
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui_test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    test.cpp \
    Term.cpp \
    connectionmanager.cpp \
    BillingAddress.cpp \
    User.cpp \
    PurchasableItem.cpp \
    Course.cpp \
    Textbook.cpp \
    Chapter.cpp \
    Section.cpp \
    ShoppingCart.cpp \
    CreditCardInformation.cpp \
    Student.cpp


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
    Types.h


FORMS    += mainwindow.ui
