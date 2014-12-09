
/*
 *Traceability: SS-03-02 (Part of Course Management Subsystem)
 *
 */
#ifndef COURSEMANAGEMENTFACADE_H
#define COURSEMANAGEMENTFACADE_H
#include "CourseManagementInputControl.h"
#include "CourseManagementUpdateControl.h"

#include "Term.h"
#include "Student.h"

#include "CourseManagementUpdateControl.h"
#include "CourseManagementInputControl.h"

#include "Course.h"
#include "Term.h"
#include "Student.h"
#include "Textbook.h"

class CourseManagementFacade
{
public:
    CourseManagementFacade();
    QList<Term*>*       retrieveAllTermList();
    QList<Course*>*     retrieveCourseList(Term*) throw(QString);
    QList<Student*>*    retrieveCourseStudents(Course*, Term*) throw(QString);
    QList<Student*>*    retrieveAllStudents();
    QList<Textbook*>*   retrieveCourseTextbooks(Course*, Term*) throw(QString);
    QList<Textbook*>*   retrieveAllTextbooks();
    bool                updateCourse(Course*, Term*) throw(QString);
    bool                deleteCourse(Course*, Term*) throw(QString);
    bool                assignTextbookToCourse(Course*, Textbook*, Term*) throw(QString);

private:
    CourseManagementInputControl   inputControl;
    CourseManagementUpdateControl  updateControl;
};

#endif // COURSEMANAGEMENTFACADE_H
