#include "ShoppingManagementFacade.h"

ShoppingManagementFacade::ShoppingManagementFacade()
{
    shopUpdateControl = new ShopUpdateControl();
//100853074
}

QList<Term*> ShoppingManagementFacade::getTermList() throw (QString) {
    return *shopUpdateControl->retrieveAllTerms();

}

QList<Course*> ShoppingManagementFacade::viewContent(Student *student, Term *term) throw (QString) {
    shopInputControl->validateViewContent(student,term);
    return *shopUpdateControl->retrieveContent(student, term);
}

ShoppingCart*  ShoppingManagementFacade::viewShoppingCart(Student *student) throw (QString) {
    shopInputControl->validateViewShoppingCart(student);
    return shopUpdateControl->retrieveShoppingCart(student);
}

bool ShoppingManagementFacade::addContent(Student *student, PurchasableItem *item, int quantity) throw (QString)
{
    shopInputControl->validateAddContent(student,item, quantity);
    return shopUpdateControl->updateShoppingCart(student, item, quantity);
}


bool ShoppingManagementFacade::emptyShoppingCart(Student *student) throw (QString)
{
    shopInputControl->validateEmptyShoppingCart(student);
    return shopUpdateControl->emptyShoppingCart(student);
}

bool ShoppingManagementFacade::checkOutShoppingCart(Student *student) throw (QString)
{
    shopInputControl->validateCheckOut(student);
    return shopUpdateControl->checkOutShoppingCart(student);
}

PaymentInformation* ShoppingManagementFacade::getPaymentInformation(Student *student) throw(QString)
{
    shopInputControl->validateRetrieveStudentPaymentInformation(student);
    PaymentInformation* info = shopUpdateControl->retrieveStudentPaymentInformation(student);
    if(info == NULL ) { info = new PaymentInformation();
        qDebug() << "qdebugging on billing info" ;
        qDebug() << info->getBillInfo().getStreetName();
    }
    return info;
}

bool ShoppingManagementFacade::updatePaymentInformation(Student* stu, PaymentInformation* payInfo) throw (QString){
    shopInputControl->validateUpdatePaymentInformation(stu,payInfo);
    return shopUpdateControl->updatePaymentInformation(stu,payInfo);
}
