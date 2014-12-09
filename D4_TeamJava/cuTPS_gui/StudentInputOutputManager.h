/*The input output mediator for the Student interface for all its boundary objects accross all windows and forms for the Student Interface
 *
 *Traceability: SS-01-01 (Part of Student Interface subsystem)
 *
 *
 */
#ifndef STUDENTINPUTOUTPUTMANAGER_H
#define STUDENTINPUTOUTPUTMANAGER_H

#include <QObject>
#include "TextbookDetailsWindow.h"
#include "StudentInterfaceWindow.h"
#include "ShoppingManagementFacade.h"
#include "OurStandardItem.h"
#include <QAbstractItemView>
#include <ShoppingCartWidget.h>
#include "CheckoutFormDialog.h"
#include "Course.h"
#include <QMessageBox>
#include <QDate>
#include "BillingAddress.h"
#include <QPair>
#include "MessageDialog.h"

class StudentInputOutputManager : public QObject
{
    Q_OBJECT
public:
    StudentInputOutputManager();

private:
    //user interface widgets
    StudentInterfaceWindow                       *studentInterface;
    ShoppingManagementFacade                     *shopFacade;
    TextbookDetailsWindow                        *textbookDetailsWindow;
    ShoppingCartWidget                           *cartWidget;
    CheckoutFormDialog                           *checkoutFormDialog;
    MessageDialog                                messageDialog;
    //important things
    ShoppingCart                                 *currentCart;
    QList<QPair <PurchasableItem*, qint32> >     currentItems;
    QList<Term*>                                  terms;
    QStringList                                  cardTypes;
    Textbook*                                     lastTextbookDetailsOpened;
    Student                                      *currentStudent;
    QList<Course*>                               coursesAndContent;

    PaymentInformation                           *paymentInfo;
    BillingAddress                               *billingInfo;
    CreditCardInformation                        *ccInfo;

    //models
    QStandardItemModel                           *courseAndTextbookModel;
    QStandardItemModel                           *chaptersAndSectionsModel;
    QStandardItemModel                           *cartModel;
    void                                         setStudentInterfaceViewModel(QAbstractItemView  *view, QStandardItemModel *model);
    void                                         buildCourseAndTextbookModel();
    void                                         buildTextbookAndChildrenModel();
    void                                          getTerms();



private slots:
    //boundary objects for student's shop view
    void    on_studentInterface_addTextbookOptionSelected();
    void    on_studentInterface_viewDetailsOptionSelected();
    void    on_studentInterface_viewCartOptionSelected();
    void    on_studentInterface_termSelected();

    //boundary objects for textbook detailed view window
    void    on_textbookDetailsWindow_addSelectedItemOptionSelected();
    void    on_textbookDetailsWindow_addCurrentTextbookOptionSelected();
    void    on_textbookDetailsWindow_closeOptionSelected();

    //boundary objects for shopping cart
    void    on_cartWidget_closeOptionSelected();
    void    on_cartWidget_checkoutOptionSelected();
    void    on_cartWidget_emptyCartOptionSelected();

    //boundary objects for checkout form dialog
    void    on_checkoutFormDialog_backOptionSelected();
    void    on_checkoutFormDialog_confirmOptionSelected();

};

#endif // STUDENTINPUTOUTPUTMANAGER_H
