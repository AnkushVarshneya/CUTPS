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
    ManageTextbooksInterfaceWindow.cpp \
    CreateTextbookFormWindow.cpp \
    CreateChapterFormWindow.cpp \
    CreateSectionFormWindow.cpp \
    ManageContentControl.cpp \
    Term.cpp \
    CUtpsDataObject.cpp \
    Textbook.cpp \
    Chapter.cpp \
    Section.cpp \
    PurchaseablItem.cpp \
    StudentInterfaceWindow.cpp \
    ContentInputOutputManager.cpp \
    MainInputOutputManager.cpp \
    StudentInputOutputManager.cpp \
    Course.cpp \
    Student.cpp \
    User.cpp \
    PaymentInformation.cpp \
    BillingAddress.cpp \
    CreditCardInformation.cpp \
    ShoppingCart.cpp \
    ShoppingManagementFacade.cpp \
    ShopInputControl.cpp \
    ShoppingControl.cpp \
    ShopUpdateControl.cpp \
    Shop.cpp \
    ContentManagementFacade.cpp \
    ContentManagementInputControl.cpp

HEADERS  += mainwindow.h \
    ContentManagerInterfaceWindow.h \
    ManageTextbooksInterfaceWindow.h \
    ManageContentControl.h \
    types.h \
    Term.h \
    CUtpsDataObject.h \
    CreateTextbookFormWindow.h \
    CreateChapterFormWindow.h \
    CreateSectionFormWindow.h \
    Textbook.h \
    Chapter.h \
    Section.h \
    PurchasableItem.h \
    StudentInterfaceWindow.h \
    ContentInputOutputManager.h \
    MainInputOutputManager.h \
    StudentInputOutputManager.h \
    Course.h \
    Student.h \
    User.h \
    PaymentInformation.h \
    BillingAddress.h \
    CreditCardInformation.h \
    ShoppingCart.h \
    ShoppingManagementFacade.h \
    ShopInputControl.h \
    ShoppingControl.h \
    ShopUpdateControl.h \
    Shop.h \
    ContentManagementFacade.h \
    ContentManagementInputControl.h

FORMS    += mainwindow.ui \
    ContentManagerInterfaceWindow.ui \
    ManageTextbooksInterfaceWindow.ui \
    CreateTextbookFormWindow.ui \
    CreateChapterFormWindow.ui \
    CreateSectionFormWindow.ui \
    StudentInterfaceWindow.ui
