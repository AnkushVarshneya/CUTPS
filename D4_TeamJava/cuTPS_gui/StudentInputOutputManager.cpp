#include "StudentInputOutputManager.h"

StudentInputOutputManager::StudentInputOutputManager()
{

    //initialize current student, models
    currentStudent = new Student();
    currentStudent->setStudentNum("100853074");

    courseAndTextbookModel = new QStandardItemModel(this);
    chaptersAndSectionsModel = new QStandardItemModel(this);

    cardTypes.append("MasterCard");
    cardTypes.append("Visa");

    cartModel = new QStandardItemModel(this);
    studentInterface = new StudentInterfaceWindow();
    studentInterface->show();

    //initialize the shopping management facade
    this->shopFacade = new ShoppingManagementFacade();
    shopFacade->emptyShoppingCart(currentStudent);
    this->getTerms();
    paymentInfo = shopFacade->getPaymentInformation(currentStudent);

//    *billingInfo = paymentInfo->getBillInfo();
//    if (billingInfo == NULL) { billingInfo = new BillingAddress() ; }

//    *ccInfo      = paymentInfo->getCreditCardInfo();
//    if (ccInfo == NULL) { ccInfo = new CreditCardInformation() ; }

    //connect signals from boundary options to slot functions on the student i/o manager
    connect(studentInterface->getAddTextbookOption(), SIGNAL( clicked() ), this, SLOT(on_studentInterface_addTextbookOptionSelected()));
    connect(studentInterface->getViewCartOption(), SIGNAL(clicked()), this, SLOT(on_studentInterface_viewCartOptionSelected()));
    connect(studentInterface->getViewDetailsOption(), SIGNAL(clicked()), this, SLOT(on_studentInterface_viewDetailsOptionSelected()));
    connect(studentInterface->getTermSelectOption(), SIGNAL(activated(QString)), this, SLOT(on_studentInterface_termSelected()));

    //connects for cart widget
    cartWidget = ShoppingCartWidget::getInstance();
    connect(cartWidget->getCheckoutOption(), SIGNAL(clicked()), this, SLOT(on_cartWidget_checkoutOptionSelected()));
    connect(cartWidget->getCloseOption(), SIGNAL(clicked()), this, SLOT(on_cartWidget_closeOptionSelected()));
    connect(cartWidget->getEmptyCartOption(), SIGNAL(clicked()), this, SLOT(on_cartWidget_emptyCartOptionSelected()));

    //connects for textbook details window
    textbookDetailsWindow = TextbookDetailsWindow::getInstance();
    connect(textbookDetailsWindow->getCloseOption(), SIGNAL(clicked()), this, SLOT(on_textbookDetailsWindow_closeOptionSelected()));
    connect(textbookDetailsWindow->getAddCurrentTextbookOption(), SIGNAL(clicked()),
                                                            this, SLOT(on_textbookDetailsWindow_addCurrentTextbookOptionSelected()));

    connect(textbookDetailsWindow->getAddSelectedItemOption(), SIGNAL(clicked()), this, SLOT(on_textbookDetailsWindow_addSelectedItemOptionSelected()));

    //connects for the checkout form dialog
    checkoutFormDialog = CheckoutFormDialog::getInstance();
    connect(checkoutFormDialog->getBackOption(), SIGNAL(clicked()), this, SLOT(on_checkoutFormDialog_backOptionSelected()));
    connect(checkoutFormDialog->getConfirmOption(), SIGNAL(clicked()), this, SLOT(on_checkoutFormDialog_confirmOptionSelected()));

}


void    StudentInputOutputManager::getTerms() {
    terms = shopFacade->getTermList();

    //populate the ui widget
    QList<Term*>::iterator i;
    for (i = terms.begin(); i != terms.end(); i++) {
        qDebug() << "iterating over term list";
        studentInterface->getTermSelectOption()->addItem((*i)->getTermName(), (*i)->getTermName() );
        studentInterface->getTermSelectOption()->setCurrentIndex(-1);
    }
    //todo: what if it fails etc
}


void StudentInputOutputManager::buildCourseAndTextbookModel()
{
    courseAndTextbookModel->clear();
    chaptersAndSectionsModel->clear();
    OurStandardItem *temp;
    QList<Course*>::iterator i;
    QList<Textbook*>::iterator j;
    for (i = coursesAndContent.begin(); i != coursesAndContent.end(); i++) {
        qDebug() << (*i)->getCourseCode();
        //temp = new OurStandardItem( *i );
        qDebug() << (*i);
        //courseAndTextbookModel->appendRow(temp);

        for(j = (*i)->getRequiredTextbooks().begin(); j != (*i)->getRequiredTextbooks().end(); j ++) {
            temp = new OurStandardItem(*j, *i, true);
            courseAndTextbookModel->appendRow(temp);
        }

    }
}

void StudentInputOutputManager::setStudentInterfaceViewModel(QAbstractItemView *view, QStandardItemModel *model) {
view->setModel(model);
}

void StudentInputOutputManager::on_studentInterface_addTextbookOptionSelected() {
    if( studentInterface->getCourseView()->currentIndex().isValid() ) {
        QVariant item_id = courseAndTextbookModel->itemFromIndex(studentInterface->getCourseView()->currentIndex())->data();
        Textbook *item = new Textbook();
        item->setItemID( item_id.toInt() );
        shopFacade->addContent(currentStudent, (PurchasableItem*) item, studentInterface->getQuantityOption()->value());
    }
    else studentInterface->statusBar()->showMessage("No textbook selected!", 3000 );


//    QVariant  an_id = chaptersAndSectionsModel->itemFromIndex(textbookDetailsWindow->getChaptersAndSectionsView()->currentIndex())->data();
//    Section *item =  new Section();
//    item->setItemID(  an_id.toInt() );

//    shopFacade->addContent(currentStudent, (PurchasableItem*) item, 1  );
//    currentCart = shopFacade->viewShoppingCart(currentStudent);
}

void StudentInputOutputManager::on_studentInterface_viewCartOptionSelected() {
    cartModel->clear();
    OurStandardItem *temp;
    float orderTotal = 0;
    try{
        currentCart = shopFacade->viewShoppingCart(currentStudent);
        currentItems = currentCart->getItems();

        QList<QPair<PurchasableItem*, qint32> >::iterator it;

        for (it = currentItems.begin(); it != currentItems.end(); it ++ )
        {
            temp = new OurStandardItem((*it).first,(*it).second);
            cartModel->appendRow(temp);
            orderTotal = orderTotal + ( (*it).first->getPrice() *
                                        (*it).second);
        }

            cartWidget->setCartViewModel(cartModel );
            cartWidget->setOrderTotalText( QString::number(orderTotal) );
           // cartWidget->setUserCartLabelText( currentStudent->getFirstName())
            connect(cartWidget->getCloseOption(),SIGNAL(clicked()), this, SLOT(on_cartWidget_closeOptionSelected()));
            connect(cartWidget->getCheckoutOption(), SIGNAL(clicked()), this, SLOT(on_cartWidget_checkoutOptionSelected()));
            cartWidget->show();

    }
    catch (QString error){
        messageDialog.getMessageTextBox()->setText(error);
        messageDialog.show();
    }

}

void StudentInputOutputManager::on_studentInterface_viewDetailsOptionSelected()
{

    QList<Course*>::iterator it;
    QList<Textbook*>::iterator at;

    chaptersAndSectionsModel->clear();
    //chaptersAndSectionsModel->appendRow( courseAndTextbookModel->itemFromIndex( studentInterface->getCourseView()->currentIndex() )->child(0));

    if( studentInterface->getCourseView()->currentIndex().isValid() ) {
    QVariant item_id = courseAndTextbookModel->itemFromIndex(studentInterface->getCourseView()->currentIndex())->data();

    qDebug() << "variant item id: " << item_id;
    if (item_id != NULL)
    {
        for(it = coursesAndContent.begin(); it != coursesAndContent.end(); it ++)
        {
            for (at = (*it)->getRequiredTextbooks().begin(); at != (*it)->getRequiredTextbooks().end(); at++)
            {

                if ((*at)->getItemID() == item_id)
                {

                    lastTextbookDetailsOpened = (*at);
                    textbookDetailsWindow = TextbookDetailsWindow::getInstance();
                    textbookDetailsWindow->setTextbookAndModel(*(*at), studentInterface->getCourseView()->currentIndex(), chaptersAndSectionsModel);
                    qDebug() << "textbook window constructed";
                    textbookDetailsWindow->show();
                }
            }
        }
    }
}
}

void StudentInputOutputManager::on_studentInterface_termSelected()
{
    qDebug() << "a term has been selected";
    qDebug() << terms.value( studentInterface->getTermSelectOption()->currentIndex() )->getTermName();
    try{
        coursesAndContent = shopFacade->viewContent(currentStudent,
                                terms.at( studentInterface->getTermSelectOption()->currentIndex() ));

        buildCourseAndTextbookModel();
        this->setStudentInterfaceViewModel(studentInterface->getCourseView(), courseAndTextbookModel);
    }
    catch (QString error){
        messageDialog.getMessageTextBox()->setText(error);
        messageDialog.show();
    }

}

void StudentInputOutputManager::on_textbookDetailsWindow_closeOptionSelected()
{
    textbookDetailsWindow->hide();
    //delete textbookDetailsWindow;
}

void StudentInputOutputManager::on_textbookDetailsWindow_addCurrentTextbookOptionSelected()
{
    try{
        qDebug() << "add current textbook attempted";
        shopFacade->addContent(currentStudent, (PurchasableItem*) lastTextbookDetailsOpened, 1);
        currentCart = shopFacade->viewShoppingCart(currentStudent);
    }
    catch (QString error){
        messageDialog.getMessageTextBox()->setText(error);
        messageDialog.show();
    }

}

void StudentInputOutputManager::on_textbookDetailsWindow_addSelectedItemOptionSelected() {

    try{
        if ( textbookDetailsWindow->getChaptersAndSectionsView()->currentIndex().isValid() ) {
            QVariant item_id = chaptersAndSectionsModel->itemFromIndex( textbookDetailsWindow->getChaptersAndSectionsView()->currentIndex() )->data();
            Textbook *item = new Textbook(); //doesnt matter, casting to purchasableitem anyway no matter what it is.
            item->setItemID( item_id.toInt() );
            shopFacade->addContent(currentStudent, (PurchasableItem*) item, textbookDetailsWindow->getQuantityOption()->value());
        }
        else studentInterface->statusBar()->showMessage("No item selected!", 3000 );
        currentCart = shopFacade->viewShoppingCart(currentStudent);
    }
    catch (QString error){
        messageDialog.getMessageTextBox()->setText(error);
        messageDialog.show();
    }

}

void StudentInputOutputManager::on_cartWidget_closeOptionSelected()
{
    cartWidget->hide();
}

void StudentInputOutputManager::on_cartWidget_checkoutOptionSelected()
{
    cartWidget->hide();
    if(paymentInfo != NULL)
    {

        checkoutFormDialog->getNameLineEdit()->setText( paymentInfo->getBillInfo().getName() ) ;
        checkoutFormDialog->getCardholderNameLineEdit()->setText( paymentInfo->getCreditCardInfo().getNameOnCard() );
        checkoutFormDialog->getStreetNameLineEdit()->setText(paymentInfo->getBillInfo().getStreetName() );
        checkoutFormDialog->getUnitNumberLineEdit()->setText( QString::number( paymentInfo->getBillInfo().getHouseNumber() ));
        checkoutFormDialog->getCityLineEdit()->setText(paymentInfo->getBillInfo().getCity() );
        checkoutFormDialog->getPostalCodeLineEdit()->setText(paymentInfo->getBillInfo().getPostalCode() );
        checkoutFormDialog->getProvinceLineEdit()->setText(paymentInfo->getBillInfo().getProvince());

        checkoutFormDialog->getCreditCardNumberLineEdit()->setText(  paymentInfo->getCreditCardInfo().getCreditCardNo()  );
        checkoutFormDialog->getCvvLineEdit()->setText( paymentInfo->getCreditCardInfo().getCVV() );

//        checkoutFormDialog->getExpYearLineEdit()->setText( QString::number( paymentInfo->getCreditCardInfo().getExpDate().currentDate().year()   ));
//        checkoutFormDialog->getExpMonthLineEdit()->setText( QString::number( paymentInfo->getCreditCardInfo().getExpDate().currentDate().month() ));
         checkoutFormDialog->getExpYearLineEdit()->setText( QString::number( paymentInfo->getCreditCardInfo().getExpDate().year()   ));
         checkoutFormDialog->getExpMonthLineEdit()->setText( QString::number( paymentInfo->getCreditCardInfo().getExpDate().month() ));
         checkoutFormDialog->getCardTypeEdit()->setCurrentText( paymentInfo->getCreditCardInfo().getCardType()  );
        qDebug() << paymentInfo->getCreditCardInfo().getExpDate();

    }
   // *paymentInfo = currentStudent->getpayInfo();
    checkoutFormDialog->getNameLineEdit()->setText(paymentInfo->getBillInfo().getName());
    checkoutFormDialog->show();
}

void StudentInputOutputManager::on_checkoutFormDialog_backOptionSelected()
{
    checkoutFormDialog->hide();
    this->on_studentInterface_viewCartOptionSelected();
}

void StudentInputOutputManager::on_cartWidget_emptyCartOptionSelected() {
    shopFacade->emptyShoppingCart(currentStudent);
    this->on_studentInterface_viewCartOptionSelected();
}


void StudentInputOutputManager::on_checkoutFormDialog_confirmOptionSelected()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(checkoutFormDialog, "Proceed?", "Are you sure you wish to checkout?", QMessageBox::Yes|QMessageBox::No );

      if (reply == QMessageBox::Yes) {
        checkoutFormDialog->hide();
        studentInterface->show();
      } else {
        checkoutFormDialog->hide();
        cartWidget->show();
      }

}
