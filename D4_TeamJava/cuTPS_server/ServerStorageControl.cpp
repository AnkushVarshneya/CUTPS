#include "ServerStorageControl.h"
#include <QDebug>
//Default constructor
ServerStorageControl::ServerStorageControl()
{
}



//Retrieves all of the terms that are persistently stored
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
 */
QList<Course*>* ServerStorageControl::retrieveContent(Student* s, Term* t){
    QueryControl* q = new QueryControl();
    QList<Course*>* result = new QList<Course*>();
    //Check for nulls
    if(s != 0 || t != 0){
        delete result;
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
        }
        delete q;
        return result;
    }
    else{
        delete q;
        return result;
    }
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

    QueryControl* q = new QueryControl();
    QList< QPair<PurchasableItem*,qint32> >* itemResult;
    ShoppingCart* shoppingCartResult = new ShoppingCart();
    if (stu != 0){
        itemResult = q->getShoppingCartItemList(stu,true);
        shoppingCartResult->getItems() = *itemResult;
        delete q;
        itemResult->clear();
        return shoppingCartResult;
    }
    else{
        delete q;
        return 0;
    }

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
    QueryControl* q = new QueryControl();
    if(student != 0 || item != 0){
        for (int i = 0; i < quantity; i++){
            if(!q->addPurchasableItemToCart(item, student)){
                delete q;
                return false;
            }
        }
        delete q;
        return true;
    }
    delete q;
    return false;
}

/**
 * @brief ServerStorageControl::retrieveAllContent()
 * Retrieves all of the content in the database in the form of a list of textbooks, with lists of chapters and chapter sections
 * in them
 *
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

    return noError;
}
