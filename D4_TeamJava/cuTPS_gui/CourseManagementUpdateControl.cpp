#include "CourseManagementUpdateControl.h"

CourseManagementUpdateControl::CourseManagementUpdateControl()
{
    clientComm = ClientCommunicatorManagementControl::getInstance();
}

QList<Term*>* CourseManagementUpdateControl::retrieveAllTermList() throw (QString){
    return clientComm->retrieveAllTerms();
}

QList<Course*>* CourseManagementUpdateControl::retrieveCourseList(Term* term) throw (QString){
    return clientComm->retrieveCourseList(term);
}

QList<Student*>* CourseManagementUpdateControl::retrieveCourseStudents(Course* crs, Term* term) throw (QString){
    return clientComm->retrieveCourseStudents(crs, term);
}

QList<Student*>* CourseManagementUpdateControl::retrieveAllStudents() throw (QString){
    return clientComm->retrieveAllStudents();
}


QList<Textbook*>* CourseManagementUpdateControl::retrieveCourseTextbooks(Course* crs, Term* term) throw (QString){
    return clientComm->retrieveCourseTextbooks(crs, term);
}

QList<Textbook*>* CourseManagementUpdateControl::retrieveAllTextbooks() throw (QString){
    return clientComm->retrieveAllTextbooks();
}

bool CourseManagementUpdateControl::updateCourse(Course* crs, Term* term) throw (QString){
    return clientComm->updateCourse(crs, term);
}

bool CourseManagementUpdateControl::deleteCourse(Course* crs, Term* term) throw (QString){
    return clientComm->deleteCourse(crs,term);

}

bool CourseManagementUpdateControl::assignTextbookToCourse(Course* crs, Textbook* text, Term* term) throw (QString){
    return clientComm->assignTextbookToCourse(crs,text,term);
}
