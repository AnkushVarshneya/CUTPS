
/*
 *Traceability: SS-03-02 (Part of Course Management Subsystem)
 */

#include "ClientCommunicatorManagementControl.h"
#ifndef COURSEMANAGEMENTUPDATECONTROL_H
#define COURSEMANAGEMENTUPDATECONTROL_H

class CourseManagementUpdateControl
{
public:
    CourseManagementUpdateControl();
    QList<Term*>*       retrieveAllTermList();
    QList<Course*>*     retrieveCourseList(Term*);
    QList<Student*>*    retrieveCourseStudents(Course*, Term*);
    QList<Student*>*    retrieveAllStudents();
    QList<Textbook*>*   retrieveCourseTextbooks(Course*, Term*);
    QList<Textbook*>*   retrieveAllTextbooks();
    bool                updateCourse(Course*, Term*);
    bool                deleteCourse(Course*, Term*);
    bool                assignTextbookToCourse(Course*, Textbook*, Term*);
private:
    ClientCommunicatorManagementControl* clientComm;
};

#endif // COURSEMANAGEMENTUPDATECONTROL_H
