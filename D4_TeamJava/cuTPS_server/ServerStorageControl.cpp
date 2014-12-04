#include "ServerStorageControl.h"
#include <QDebug>
//Default constructor
ServerStorageControl::ServerStorageControl()
{
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
    QList<Course*>* result = new QList<Course*>;
    //Check for nulls
    if(s != 0 && t != 0){
        //Retrieves the list courses the student is registered for the given term
        result = q->retrieveStudentCourseList(s->getStudentNum(),t->getTermID());
        //For each Course in the student course list, retrieve the required textbooks
        //And for each required textbook, retrieve the required Chapters, and for each Chapter,
        //Retrieve the required Chapter sections.
        for(int courseIndex = 0; courseIndex < result->size(); courseIndex++){
            QList<Textbook*>* textbookList = q->retrieveTextbookList((*result)[courseIndex],
                                                                     (*result)[courseIndex]->getTerm()->getTermID(),
                                                                     true);
            foreach (Textbook* t, *textbookList){
                t->getChapterList() = *(q->retrieveChapterList(t->getISBN(),true));
                foreach (Chapter* c, t->getChapterList()){
                    c->getChapterSections() = *(q->retrieveSectionList(c->getChapterNumber(),t->getISBN(),true));
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
