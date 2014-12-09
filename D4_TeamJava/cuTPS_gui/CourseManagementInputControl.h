/*
 *Traceability: SS-03-02 (Part of Course Management Subsystem)
 */

#ifndef COURSEMANAGEMENTINPUTCONTROL_H
#define COURSEMANAGEMENTINPUTCONTROL_H

#include "Term.h"
#include "Student.h"

class CourseManagementInputControl
{
public:
    CourseManagementInputControl();

    void validateRetrieveCourseList(Term*) throw(QString);
    void validateRetrieveCourseStudents(Course*, Term*) throw(QString);
    void validateRetrieveCourseTextbooks(Course*, Term*) throw(QString);
    void validateUpdateCourse(Course*, Term*) throw(QString);
    void validateDeleteCourse(Course*, Term*) throw(QString);
    void validateAssignTextbookToCourse(Course*, Textbook*, Term*) throw(QString);
};

#endif // COURSEMANAGEMENTINPUTCONTROL_H
