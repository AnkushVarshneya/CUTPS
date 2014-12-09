#include "ShopUpdateControl.h"

ShopUpdateControl::ShopUpdateControl()
{
    mc = ClientCommunicatorManagementControl::getInstance();
}

QList<Term*>* ShopUpdateControl::retrieveAllTerms() throw (QString){
    return mc->retrieveAllTerms();
}

QList<Course*>* ShopUpdateControl::retrieveContent(Student *stu, Term *term) throw (QString){
    return mc->retrieveContent(stu,term);
}

ShoppingCart*  ShopUpdateControl::retrieveShoppingCart(Student* stu) throw (QString){
    return mc->retrieveShoppingCart(stu);
}

bool ShopUpdateControl::updateShoppingCart(Student* stu, PurchasableItem* item, qint32 quantity) throw (QString){
    return mc->updateShoppingCart(stu, item, quantity);
}

bool ShopUpdateControl::checkOutShoppingCart(Student* stu) throw (QString){
    return mc->checkOutShoppingCart(stu);
}

bool ShopUpdateControl::emptyShoppingCart(Student* stu) throw (QString){
    return mc->emptyShoppingCart(stu);
}

bool ShopUpdateControl::updatePaymentInformation(Student* stu, PaymentInformation* payInfo) throw (QString){
    return mc->updatePaymentInformation(stu,payInfo);
}

PaymentInformation* ShopUpdateControl::retrieveStudentPaymentInformation(Student* stu) throw (QString){
    return mc->retrieveStudentPaymentInformation(stu);
}
