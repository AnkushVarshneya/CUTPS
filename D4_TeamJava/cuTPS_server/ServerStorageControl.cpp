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
    if(s != 0 && t != 0){
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
    QList<PurchasableItem*>* itemResult;
    ShoppingCart* shoppingCartResult = new ShoppingCart();
    if (stu != 0){
        itemResult = q->getShoppingCartItemList(stu,true);
        shoppingCartResult->getItems() = *itemResult;
        delete q;
        qDeleteAll(itemResult->begin(),itemResult->end());
        return shoppingCartResult;
    }
    else{
        delete q;
        return 0;
    }
}

bool ServerStorageControl::updateShoppingCart(Student* student, PurchasableItem* item, qint32 quantity){

}
