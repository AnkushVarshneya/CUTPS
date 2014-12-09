/* Class responsible for rule checking user inputs for a given ShoppingManagementFacade interface
 *
 * Traceability: SS-01-02 (Part of ShoppingManagement Subsystem)
 *
 */
#ifndef SHOPINPUTCONTROL_H
#define SHOPINPUTCONTROL_H

#include "Course.h"
#include "Textbook.h"
#include "Chapter.h"
#include "Section.h"
#include "Term.h"
#include "Student.h"
#include "ShopUpdateControl.h"

class ShopInputControl
{
public:
    ShopInputControl();

    void validateViewContent(Student*, Term*) throw(QString);
    void validateViewShoppingCart(Student*) throw(QString);
    void validateAddContent(Student*, PurchasableItem*, int) throw(QString);
    void validateEmptyShoppingCart(Student*) throw(QString);
    void validateUpdatePaymentInformation(Student*, PaymentInformation*) throw (QString);
};

#endif // SHOPINPUTCONTROL_H
