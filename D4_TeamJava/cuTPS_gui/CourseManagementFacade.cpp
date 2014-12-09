#include "CourseManagementFacade.h"

CourseManagementFacade::CourseManagementFacade()
{
}

QList<Term*>* CourseManagementFacade::retrieveAllTermList() throw (QString){
    return updateControl.retrieveAllTermList();
}

QList<Course*>* CourseManagementFacade::retrieveCourseList(Term* term) throw(QString){
    inputControl.validateRetrieveCourseList(term);
    return updateControl.retrieveCourseList(term);
}

QList<Student*>* CourseManagementFacade::retrieveCourseStudents(Course* course, Term* term) throw(QString){
    inputControl.validateRetrieveCourseStudents(course, term);
    return updateControl.retrieveCourseStudents(course, term);
}

QList<Student*>* CourseManagementFacade::retrieveAllStudents() throw (QString){
    return updateControl.retrieveAllStudents();
}

QList<Textbook*>* CourseManagementFacade::retrieveCourseTextbooks(Course* course, Term* term) throw(QString){
    inputControl.validateRetrieveCourseTextbooks(course, term);
    return updateControl.retrieveCourseTextbooks(course, term);
}

QList<Textbook*>* CourseManagementFacade::retrieveAllTextbooks() throw (QString){
    return updateControl.retrieveAllTextbooks();
}

bool CourseManagementFacade::updateCourse(Course* course, Term* term) throw(QString){
    inputControl.validateUpdateCourse(course, term);
    return updateControl.updateCourse(course, term);
}

bool CourseManagementFacade::deleteCourse(Course* course, Term* term) throw(QString){
    inputControl.validateDeleteCourse(course, term);
    return updateControl.deleteCourse(course, term);
}

bool CourseManagementFacade::assignTextbookToCourse(Course* course, Textbook* textbook, Term* term) throw(QString){
    inputControl.validateAssignTextbookToCourse(course, textbook, term);
    return updateControl.assignTextbookToCourse(course, textbook, term);
}
