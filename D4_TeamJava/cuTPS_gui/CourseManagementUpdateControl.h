
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
    QList<Course*>* retrieveCourseList(Term*);
    QList<Textbook*>* retrieveAllTextbooks();
    bool        updateCourse(Course*, Term*);
    bool        deleteCourse(Course*, Term*);
    bool        registerStudentToCourse(Course*, Student*, Term*);
    bool        assignTextbookToCourse(Course*, Textbook*, Term*);
private:
    ClientCommunicatorManagementControl* clientComm;
};

#endif // COURSEMANAGEMENTUPDATECONTROL_H
