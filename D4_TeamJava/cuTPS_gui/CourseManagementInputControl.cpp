#include "CourseManagementInputControl.h"

CourseManagementInputControl::CourseManagementInputControl()
{
}

void CourseManagementInputControl::validateRetrieveCourseList(Term* term) throw(QString){
    if(term == NULL){
        throw QString("No Term");
    }
    if(term->getTermID() < 0){
        throw QString("Invalid termID: %1").arg(term->getTermID());
    }
}

void CourseManagementInputControl::validateRetrieveCourseStudents(Course* course, Term* term) throw(QString){
    if(course == NULL){
        throw QString("No Course");
    }
    if(course->getCourseCode() == NULL || course->getCourseCode().length()<1){
        throw QString("Invalid course code: %1").arg(course->getCourseCode());
    }
    if(course->getCourseSection() == NULL || course->getCourseSection().length()<1){
        throw QString("Invalid course section: %1").arg(course->getCourseSection());
    }

    if(term == NULL){
        throw QString("No Term");
    }
    if(term->getTermID() < 0){
        throw QString("Invalid termID: %1").arg(term->getTermID());
    }
}

void CourseManagementInputControl::validateRetrieveCourseTextbooks(Course* course, Term* term) throw(QString){
    if(course == NULL){
        throw QString("No Course");
    }
    if(course->getCourseCode() == NULL || course->getCourseCode().length()<1){
        throw QString("Invalid course code: %1").arg(course->getCourseCode());
    }
    if(course->getCourseSection() == NULL || course->getCourseSection().length()<1){
        throw QString("Invalid course section: %1").arg(course->getCourseSection());
    }

    if(term == NULL){
        throw QString("No Term");
    }
    if(term->getTermID() < 0){
        throw QString("Invalid termID: %1").arg(term->getTermID());
    }
}

void CourseManagementInputControl::validateUpdateCourse(Course* course, Term* term) throw(QString){
    if(course == NULL){
        throw QString("No Course");
    }
    if(course->getCourseCode() == NULL || course->getCourseCode().length()<1){
        throw QString("Invalid course code: %1").arg(course->getCourseCode());
    }
    if(course->getCourseSection() == NULL || course->getCourseSection().length()<1){
        throw QString("Invalid course section: %1").arg(course->getCourseSection());
    }

    if(course->getInstructor() == NULL || course->getInstructor().length()<1){
        throw QString("Invalid course instructor: %1").arg(course->getInstructor());
    }

    if(term == NULL){
        throw QString("No Term");
    }
    if(term->getTermID() < 0){
        throw QString("Invalid termID: %1").arg(term->getTermID());
    }
}

void CourseManagementInputControl::validateDeleteCourse(Course* course, Term* term) throw(QString){
    if(course == NULL){
        throw QString("No Course");
    }
    if(course->getCourseCode() == NULL || course->getCourseCode().length()<1){
        throw QString("Invalid course code: %1").arg(course->getCourseCode());
    }
    if(course->getCourseSection() == NULL || course->getCourseSection().length()<1){
        throw QString("Invalid course section: %1").arg(course->getCourseSection());
    }

    if(term == NULL){
        throw QString("No Term");
    }
    if(term->getTermID() < 0){
        throw QString("Invalid termID: %1").arg(term->getTermID());
    }
}

void CourseManagementInputControl::validateAssignTextbookToCourse(Course* course, Textbook* text, Term* term) throw(QString){
    if(course == NULL){
        throw QString("No Course");
    }
    if(course->getCourseCode() == NULL || course->getCourseCode().length()<1){
        throw QString("Invalid course code: %1").arg(course->getCourseCode());
    }
    if(course->getCourseSection() == NULL || course->getCourseSection().length()<1){
        throw QString("Invalid course section: %1").arg(course->getCourseSection());
    }

    if(text == NULL){
        throw QString("No Textbook");
    }

    if(text->getISBN() == NULL || text->getISBN().length()<1){
        throw QString("Invalid ISBN: %1").arg(text->getISBN());
    }

    if(term == NULL){
        throw QString("No Term");
    }
    if(term->getTermID() < 0){
        throw QString("Invalid termID: %1").arg(term->getTermID());
    }
}
