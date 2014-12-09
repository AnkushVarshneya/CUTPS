
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
    QList<Term*>*       retrieveAllTermList() throw (QString);
    QList<Course*>*     retrieveCourseList(Term*) throw (QString);
    QList<Student*>*    retrieveCourseStudents(Course*, Term*) throw (QString);
    QList<Student*>*    retrieveAllStudents() throw (QString);
    QList<Textbook*>*   retrieveCourseTextbooks(Course*, Term*) throw (QString);
    QList<Textbook*>*   retrieveAllTextbooks() throw (QString);
    bool                updateCourse(Course*, Term*) throw (QString);
    bool                deleteCourse(Course*, Term*) throw (QString);
    bool                assignTextbookToCourse(Course*, Textbook*, Term*) throw (QString);
private:
    ClientCommunicatorManagementControl* clientComm;
};

#endif // COURSEMANAGEMENTUPDATECONTROL_H
