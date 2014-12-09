#include "ShopUpdateControl.h"

ShopUpdateControl::ShopUpdateControl()
{
    mc = ClientCommunicatorManagementControl::getInstance();
}

QList<Term*>* ShopUpdateControl::retrieveAllTerms(){
    return mc->retrieveAllTerms();
}

QList<Course*>* ShopUpdateControl::retrieveContent(Student *stu, Term *term){
    return mc->retrieveContent(stu,term);
}

ShoppingCart*  ShopUpdateControl::retrieveShoppingCart(Student* stu){
    return mc->retrieveShoppingCart(stu);
}

bool ShopUpdateControl::updateShoppingCart(Student* stu, PurchasableItem* item, qint32 quantity){
    return mc->updateShoppingCart(stu, item, quantity);
}

bool ShopUpdateControl::checkOutShoppingCart(Student* stu){
    return mc->checkOutShoppingCart(stu);
}

bool ShopUpdateControl::emptyShoppingCart(Student* stu){
    return mc->emptyShoppingCart(stu);
}

bool ShopUpdateControl::updatePaymentInformation(Student* stu, PaymentInformation* payInfo){
    return mc->updatePaymentInformation(stu,payInfo);
}

PaymentInformation* ShopUpdateControl::retrieveStudentPaymentInformation(Student* stu){
    return mc->retrieveStudentPaymentInformation(stu);
}
