#include "ShoppingManagementFacade.h"

ShoppingManagementFacade::ShoppingManagementFacade()
{
    shopUpdateControl = new ShopUpdateControl();
//100853074
}

QList<Term*>        ShoppingManagementFacade::getTermList() {
    return *shopUpdateControl->retrieveAllTerms();

}

QList<Course*>      ShoppingManagementFacade::viewContent(Student *student, Term *term) {

    return *shopUpdateControl->retrieveContent(student, term);
}

ShoppingCart*       ShoppingManagementFacade::viewShoppingCart(Student *student) {
return shopUpdateControl->retrieveShoppingCart(student);
}

void                ShoppingManagementFacade::addContent(Student *student, PurchasableItem *item, int quantity)
{
       shopUpdateControl->updateShoppingCart(student, item, quantity);
}


void                ShoppingManagementFacade::emptyShoppingCart(Student *student)
{
    shopUpdateControl->emptyShoppingCart(student);
}

void                ShoppingManagementFacade::checkout(Student *student)
{
    shopUpdateControl->checkout(student);
}

PaymentInformation* ShoppingManagementFacade::getPaymentInformation(Student *student)
{
    PaymentInformation* info = shopUpdateControl->retrieveStudentPaymentInformation(student);
    if(info == NULL ) { info = new PaymentInformation();
        qDebug() << "qdebugging on billing info" ;
        qDebug() << info->getBillInfo().getStreetName();
    }
    return info;
}
