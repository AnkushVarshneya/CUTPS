#include "ServerStorageControl.h"
#include <QDebug>
//Default constructor
ServerStorageControl::ServerStorageControl() {}

/**
 * @brief ServerStorageControl::retrieveAllTerms
 *  Retrieves all of the terms that are persistently stored
 * @return
 */
QList<Term*>* ServerStorageControl::retrieveAllTerms(){
    QueryControl* q = new QueryControl();
    QList<Term*>* resultTermList = q->retrieveTermList();
    delete q;
    return resultTermList;
}

/**
 * @brief ServerStorageControl::retrieveContent
 *  Retrieves a list of courses with textbooks and sub-content for a given student and term
 * @param s
 *  Student argument
 * @param t
 *  Term argument
 * @return
 *  returns a list of Courses
 *      list will be empty if any params null
 */
QList<Course*>* ServerStorageControl::retrieveContent(Student* s, Term* t){
    //Check for null -> return empty list
    if(s == NULL || t == NULL){
        return new QList<Course*>();
    }

    QueryControl* q = new QueryControl();
    QList<Course*>* result;

    //Retrieves the list courses the student is registered for the given term
    result = q->retrieveStudentCourseList(s->getStudentNum(),t->getTermID());
    //For each Course in the student course list, retrieve the required textbooks
    for(int courseIndex = 0; courseIndex < result->size(); courseIndex++){
        QList<Textbook*>* textbookList = q->retrieveTextbookList((*result)[courseIndex],
                                                                 (*result)[courseIndex]->getTerm()->getTermID(),
                                                                 true);
        //And for each required textbook, retrieve the required Chapters, and for each Chapter,
        foreach (Textbook* t, *textbookList){
            QList<Chapter*>* cList =  q->retrieveChapterList(t->getISBN(),true);
            t->getChapterList() = *cList;
            delete cList;
            //Retrieve the required Chapter sections.
            foreach (Chapter* c, t->getChapterList()){
                QList<Section*>* sList = q->retrieveSectionList(c->getChapterNumber(),t->getISBN(),true);
                c->getChapterSections() = *sList;
                delete sList;
            }
        }
        (*result)[courseIndex]->getRequiredTextbooks() = *textbookList;
        delete textbookList;
    }
    delete q;
    return result;
}

/**
 * @brief ServerStorageControl::retrieveShoppingCart
 *  Retrieves the student shopping cart
 * @param stu
 *  Student argument
 * @return
 *  returns a Shopping cart pointer
 */
ShoppingCart* ServerStorageControl::retrieveShoppingCart(Student* stu){
    if (stu == NULL) {
        return NULL;
    }

    QueryControl* q = new QueryControl();
    QList< QPair<PurchasableItem*,qint32> >* itemResult;
    ShoppingCart* shoppingCartResult = new ShoppingCart();

    itemResult = q->getShoppingCartItemList(stu,true);
    shoppingCartResult->getItems() = *itemResult;
    delete q;
    itemResult->clear();
    return shoppingCartResult;
}

/**
 * @brief ServerStorageControl::updateShoppingCart
 *  Adds the specific purchasable item by the quantity argument to the student's shopping cart
 * @param student
 *  student argument
 * @param item
 *  The purchasable item to be added to the shopping cart of the student
 * @param quantity
 *  The number of times the purchasable item is to be added to the shopping cart
 * @return boolean
 *
 */
bool ServerStorageControl::updateShoppingCart(Student* student, PurchasableItem* item, qint32 quantity){
    //Check for null
    if(student == NULL || item == NULL){
        return false;
    }

    QueryControl* q = new QueryControl();
    bool noError = true;

    for (int i = 0; i < quantity; i++){
        noError = noError && q->addPurchasableItemToCart(item, student);
    }
    delete q;

    return noError;
}

/**
 * @brief ServerStorageControl::updateOrderContents
 *  go through all PurchasableItem(s) in ShoppingCart for a student and make a order log
 *  delete shooping cart on success
 * @param student
 *  student shopping cart belongs to
 * @param shoppingcart
 *  shopping carts contaning PurchasableItem to order
 * @return
 *  returns if orders were made successfully
 */
bool ServerStorageControl::updateOrderContents(Student *student, ShoppingCart *shoppingcart){
    //Check for null
    if(student == NULL){
        return false;
    }
    QueryControl* q = new QueryControl();
    bool noError = true;

    // make a order for each PurchasableItem in cart
    for(int i = 0; i<shoppingcart->getItems().length(); i++) {
        // fot the amount of quantity amount of times
        for(int j = 0; j<shoppingcart->getItems().at(i).second; j++ ) {
            noError = noError && q->updateOrderContents(shoppingcart->getItems().at(i).first, student);
        }
    }

    // if all orders processed empty shoppingcart
    if(noError){
        noError = noError && q->emptyShoppingCart(student);
    }

    return noError;
}

/**
 * @brief ServerStorageControl::updatePaymentInformation
 *  updates a students payment information
 * @param student
 *  student to save paymentinformation for
 * @param paymentInformation
 *  paymentinformation to save
 * @return
 *  if payment information was saved
 */
bool ServerStorageControl::updatePaymentInformation(Student *student, PaymentInformation *paymentInformation){
    //Check for null
    if(student == NULL || paymentInformation == NULL){
        return false;
    }

    QueryControl* q = new QueryControl();

    bool noError =  q->updatePaymentInformation(student, paymentInformation);

    delete q;

    return noError;
}

/**
 * @brief ServerStorageControl::retrievePaymentInformation
 *  retrirves a students payment information
 * @param student
 *  student to retrieve payment information for
 * @return
 *  payment information
 */
PaymentInformation* ServerStorageControl::retrievePaymentInformation(Student *student){
    //Check for null
    if (student == NULL) {
        return NULL;
    }

    QueryControl* q = new QueryControl();

    PaymentInformation *result  = q->retrievePaymentInformation(student);

    delete q;

    return result;
}

/**
 * @brief ServerStorageControl::emptyShoppingCart
 *  empties a ShoppingCart for a given Student
 * @param student
 *  Student to the ShoppingCard belongs to
 * @return
 *  if ShoppingCart was emptied
 */
bool ServerStorageControl::emptyShoppingCart(Student *student){
    //Check for null
    if (student == NULL) {
        return false;
    }

    QueryControl* q = new QueryControl();

    bool noError = q->emptyShoppingCart(student);

    delete q;

    return noError;
}

/**
 * @brief ServerStorageControl::retrieveAllContent()
 * Retrieves all of the content in the database in the form of a list of textbooks, with lists of chapters and chapter sections
 * in them
 * @return QList<Textbook*>*
 *
 */
QList<Textbook*>* ServerStorageControl::retrieveAllContent(){
    QueryControl* q = new QueryControl();
    QList<Textbook*>* result = q->retrieveAllTextbookList();
    foreach (Textbook* text, *result){
        QList<Chapter*>* cList =  q->retrieveChapterList(text->getISBN(),false);
        text->getChapterList() = *cList;
        delete cList;
        foreach(Chapter* chap, text->getChapterList()){
            QList<Section*>* sList = q->retrieveSectionList(chap->getChapterNumber(),text->getISBN(),false);
            chap->getChapterSections() = *sList;
            delete sList;
        }
    }

    delete q;

    return result;
}

/**
 * @brief ServerStorageControl::updateContent()
 * Update all of the content in the database by updating textbook,
 * then all chapters in it, then all sections in those sections
 * @param t
 * textbook to update
 * @return if update was successful
 */
bool ServerStorageControl::updateContent(Textbook *t){
    //Check for nulls
    if(t == NULL){
        return false;
    }

    QueryControl* q = new QueryControl();
    bool noError = true;

    // update textbook
    noError = noError && q->updateTextbook(t);
    foreach (Chapter *c, t->getChapterList()){
        // update chapter
        noError = noError && q->updateChapter(c, t->getISBN());
        foreach (Section *s, c->getChapterSections()) {
            // update section
            noError = noError && q->updateSection(s, c->getChapterNumber(), t->getISBN());
        }
    }

    delete q;

    return noError;
}

/**
 * @brief ServerStorageControl::deleteContent
 *  delete content
 *  note: this will delete any content under this content
 * @param pi
 *  PurchasableItem to delete
 * @return
 *  returns it deleted
 */
bool ServerStorageControl::deleteContent(PurchasableItem *pi){
    //Check for nulls
    if(pi == NULL){
        return false;
    }

    QueryControl* q = new QueryControl();

    bool noError = q->deletePurchasableItem(pi);

    delete q;

    return noError;
}

/**
 * @brief ServerStorageControl::updateCourse
 *  updates a couse for a given term
 * @param course
 *  course to update
 * @param termID
 *  term course is under
 * @return
 *  if course updated
 */
bool ServerStorageControl::updateCourse(Course *course, qint32 termID){
    //Check for nulls
    if(course == NULL || termID < 0){
        return false;
    }

    QueryControl* q = new QueryControl();

    bool noError = q->updateCourse(course, termID);

    delete q;

    return noError;
}

/**
 * @brief ServerStorageControl::deleteCourse
 *  delete a couse for a given term
 * @param course
 *  course to delete
 * @param termID
 *  term course is under
 * @return
 *  if course deleted
 */
bool ServerStorageControl::deleteCourse(Course *course, qint32 termID){
    //Check for nulls
    if(course == NULL || termID < 0){
        return false;
    }

    QueryControl* q = new QueryControl();

    bool noError = q->deleteCourse(course, termID);

    delete q;

    return noError;
}

/**
 * @brief ServerStorageControl::updateCourseStudentLink
 *  link a student to a course for a given term
 * @param course
 *  course to links to
 * @param termID
 *  term course is under
 * @param student
 *  student to link
 * @return
 *  if student linked to course
 */
bool ServerStorageControl::updateCourseStudentLink(Course *course, qint32 termID, Student *student){
    //Check for nulls
    if(course == NULL || termID < 0|| student == NULL){
        return false;
    }

    QueryControl* q = new QueryControl();

    bool noError = q->updateCourseStudentLink(course, termID, student);

    delete q;

    return noError;
}

/**
 * @brief ServerStorageControl::updateCourseTextbookLink
 *  link a textbook to a course for a given term
 * @param course
 *  course to links to
 * @param termID
 *  term course is under
 * @param textbook
 *  textbook to link
 * @return
 *  if textbook linked to course
 */
bool ServerStorageControl::updateCourseTextbookLink(Course *course, qint32 termID, Textbook *textbook){
    //Check for nulls
    if(course == NULL || termID < 0|| textbook == NULL){
        return false;
    }

    QueryControl* q = new QueryControl();

    bool noError = q->updateCourseTextbookLink(course, termID, textbook);

    delete q;

    return noError;
}
