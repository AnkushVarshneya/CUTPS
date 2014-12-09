/*Class responsible for acting as the single interface for the Student Interface subsystem to interact with to
 *do some specific actions in the application logic
 *
 *Traceability: SS-01-02 (Part of Shopping Management Subsystem)
 *
 *
 */

#ifndef SHOPPINGMANAGEMENTFACADE_H
#define SHOPPINGMANAGEMENTFACADE_H

#include "Course.h"
#include "Textbook.h"
#include "Chapter.h"
#include "Section.h"
#include "Term.h"
#include "Student.h"
#include "ShopUpdateControl.h"
#include "ShopInputControl.h"
#include <QDebug>
#include <QList>


class ShoppingManagementFacade
{
public:
    ShoppingManagementFacade();
    QList<Course*>              viewContent(Student*, Term*) throw(QString);
    QList<Term*>                getTermList() throw (QString);
    ShoppingCart*               viewShoppingCart(Student*) throw (QString);
    bool                        addContent(Student*, PurchasableItem*,int) throw (QString);
    bool                        emptyShoppingCart(Student*) throw (QString);
    PaymentInformation*         getPaymentInformation(Student*) throw(QString);

    bool                        updatePaymentInformation(Student*, PaymentInformation*) throw (QString);
    bool                        checkOutShoppingCart(Student *) throw(QString);


private:
    ShopUpdateControl           *shopUpdateControl;
    ShopInputControl            *shopInputControl;


};

#endif // SHOPPINGMANAGEMENTFACADE_H
