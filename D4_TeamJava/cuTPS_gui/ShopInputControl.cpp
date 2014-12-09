#include "ShopInputControl.h"

ShopInputControl::ShopInputControl()
{
}

void ShopInputControl::validateViewContent(Student* student, Term* term) throw(QString){
    if(student == NULL){
        throw QString("No Student");
    }
    if(student->getStudentNum() == NULL || student->getStudentNum().length()<1){
        throw QString("Invalid student number: %1").arg(student->getStudentNum());
    }

    if(term == NULL){
        throw QString("No Term");
    }
    if(term->getTermID() < 0){
        throw QString("Invalid termID: %1").arg(term->getTermID());
    }
}

void ShopInputControl::validateViewShoppingCart(Student* student) throw(QString){
    if(student == NULL){
        throw QString("No Student");
    }
    if(student->getStudentNum() == NULL || student->getStudentNum().length()<1){
        throw QString("Invalid student number: %1").arg(student->getStudentNum());
    }
}

void ShopInputControl::validateAddContent(Student* student, PurchasableItem* item, int quantity) throw(QString){
    if(student == NULL){
        throw QString("No Student");
    }
    if(student->getStudentNum() == NULL || student->getStudentNum().length()<1){
        throw QString("Invalid student number: %1").arg(student->getStudentNum());
    }

    if(item == NULL){
        throw QString("No purchasable item");
    }
    if(item->getItemID() < 0){
        throw QString("Invalid itemID: %1").arg(item->getItemID());
    }
    if(quantity < 1){
        throw QString("Invalid quantity: %1").arg(quantity);
    }
}

void ShopInputControl::validateEmptyShoppingCart(Student* student) throw(QString){
    if(student == NULL){
        throw QString("No Student");
    }
    if(student->getStudentNum() == NULL || student->getStudentNum().length()<1){
        throw QString("Invalid student number: %1").arg(student->getStudentNum());
    }

}

void ShopInputControl::validateUpdatePaymentInformation(Student* student, PaymentInformation* payInfo) throw (QString){
    if(student == NULL){
        throw QString("Error: No Student, Reset the program");
    }

}
