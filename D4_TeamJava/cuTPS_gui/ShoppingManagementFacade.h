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
#include <QDebug>
#include <QList>


class ShoppingManagementFacade
{
public:
    ShoppingManagementFacade();
    QList<Course*>              viewContent(Student *student, Term *term);
    QList<Term*>                getTermList();
    ShoppingCart*               viewShoppingCart(Student *student);
    void                        addContent(Student *student, PurchasableItem *item, int quantity);
    void                        emptyShoppingCart(Student *student);

private:
    ShopUpdateControl           *shopUpdateControl;


};

#endif // SHOPPINGMANAGEMENTFACADE_H
