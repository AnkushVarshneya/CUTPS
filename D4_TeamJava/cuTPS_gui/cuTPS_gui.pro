#-------------------------------------------------
#
# Project created by QtCreator 2014-11-25T13:46:06
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cuTPS_gui
TEMPLATE = app


SOURCES += main.cpp \
        mainwindow.cpp \
    ContentManagerInterfaceWindow.cpp \
    ManageTextbooksInterfaceWindow.cpp \
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
    OurStandardItem.cpp \
    ShoppingManagementFacade.cpp \
    ShopInputControl.cpp \
    ShopUpdateControl.cpp \
    ContentManagementFacade.cpp \
    ContentManagementInputControl.cpp \
    EditChapterFormWindow.cpp \
    EditTextbookFormWindow.cpp \
    EditSectionFormWindow.cpp \
    ContentManagementUpdateControl.cpp \
    CourseManagementFacade.cpp \
    CourseManagementInputControl.cpp \
    CourseManagementUpdateControl.cpp \
    ClientCommunicatorManagementControl.cpp \
    ClientCommunicatorRequestManager.cpp \
    TextbookDetailsWindow.cpp \
    StudentShopView.cpp \
    ShoppingCartWidget.cpp \
    CheckoutDialogWidget.cpp \
    ManageCoursesInterfaceWindow.cpp \
    ModifyCourseFormWindow.cpp \
    LinkTextbookFormWindow.cpp \
    LinkStudentFormWindow.cpp \
    CourseInputOutputManager.cpp \
    CheckoutFormDialog.cpp \
    ConfirmationDialogWindow.cpp \
    MessageDialog.cpp

HEADERS  += mainwindow.h \
    ContentManagerInterfaceWindow.h \
    ManageTextbooksInterfaceWindow.h \
    Term.h \
    CUtpsDataObject.h \
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
    OurStandardItem.h \
    ShoppingManagementFacade.h \
    ShopInputControl.h \
    ShopUpdateControl.h \
    ContentManagementFacade.h \
    ContentManagementInputControl.h \
    EditChapterFormWindow.h \
    EditSectionFormWindow.h \
    EditTextbookFormWindow.h \
    ContentManagementUpdateControl.h \
    CourseManagementFacade.h \
    CourseManagementInputControl.h \
    CourseManagementUpdateControl.h \
    ClientCommunicatorManagementControl.h \
    ClientCommunicatorRequestManager.h \
    TextbookDetailsWindow.h \
    StudentShopView.h \
    ShoppingCartWidget.h \
    CheckoutDialogWidget.h \
    ManageCoursesInterfaceWindow.h \
    ModifyCourseFormWindow.h \
    LinkTextbookFormWindow.h \
    LinkStudentFormWindow.h \
    CourseInputOutputManager.h \
    CheckoutFormDialog.h \
    ConfirmationDialogWindow.h \
    MessageDialog.h \
    CourseInputOutputManager.h


FORMS    += mainwindow.ui \
    ContentManagerInterfaceWindow.ui \
    ManageTextbooksInterfaceWindow.ui \
    StudentInterfaceWindow.ui \
    EditChapterFormWindow.ui \
    EditSectionFormWindow.ui \
    EditTextbookFormWindow.ui \
    TextbookDetailsWindow.ui \
    StudentShopView.ui \
    ShoppingCartWidget.ui \
    CheckoutDialogWidget.ui \
    ManageCoursesInterfaceWindow.ui \
    ModifyCourseFormWindow.ui \
    LinkTextbookFormWindow.ui \
    LinkStudentFormWindow.ui \
    CheckoutFormDialog.ui \
    ConfirmationDialogWindow.ui \
    MessageDialog.ui

