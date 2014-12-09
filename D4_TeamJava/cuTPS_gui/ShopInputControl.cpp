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
    if(payInfo == NULL){
        throw QString("Error: No Payment Information, enter your payment Information");
    }

    if(payInfo->getBillInfo().getName().length() <1){
        throw QString("Error: Blank name, enter a name ").arg(payInfo->getBillInfo().getName());
    }

    if(payInfo->getBillInfo().getHouseNumber() < 1){
        throw QString("Error: Invalid House Number: %1, enter a positive house number").arg(payInfo->getBillInfo().getHouseNumber());
    }
    if(payInfo->getBillInfo().getStreetName().length() < 1){
        throw QString("Error: Invalid Street Name: %1, enter a street name").arg(payInfo->getBillInfo().getStreetName());
    }
    if(payInfo->getBillInfo().getCity().length() < 1){
        throw QString("Error: Invalid City: %1, enter a city").arg(payInfo->getBillInfo().getCity());
    }
    if(payInfo->getBillInfo().getProvince().length() <1){
        throw QString("Error: Invalid Province: %1, enter a province").arg(payInfo->getBillInfo().getProvince());
    }
    if(payInfo->getBillInfo().getPostalCode().length() <1){
        throw QString("Error:Invalid Postal Code: %1, enter a postal code").arg(payInfo->getBillInfo().getPostalCode());
    }
    if(payInfo->getCreditCardInfo().getCreditCardNo().length() <1){
        throw QString("Error: Invalid Credit Card Info: %1, enter a credit card number").arg(payInfo->getCreditCardInfo().getCreditCardNo());
    }
    if(payInfo->getCreditCardInfo().getCVV().length() != 3){
        throw QString("Error: Invalid CVV: %1, enter a CVV digit of length 3").arg(payInfo->getCreditCardInfo().getCVV());
    }
    if(payInfo->getCreditCardInfo().getExpDate() < QDate::fromString("20141209","yyyyMMdd")){
        throw QString("Error: Expired Date: %1, Enter a credit card with a valid expiry date").arg(payInfo->getCreditCardInfo().getExpDate().toString("yyyyMMdd"));
    }

}
