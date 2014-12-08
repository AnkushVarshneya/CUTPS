#include "CourseManagementUpdateControl.h"

CourseManagementUpdateControl::CourseManagementUpdateControl()
{
    clientComm = ClientCommunicatorManagementControl::getInstance();
}



QList<Course*>* CourseManagementUpdateControl::retrieveCourseList(Term* term){
    return clientComm->retrieveCourseList(term);
}

QList<Textbook*>* CourseManagementUpdateControl::retrieveAllTextbooks(){
    return clientComm->retrieveAllTextbooks();
}

bool CourseManagementUpdateControl::updateCourse(Course* crs, Term* term){
    return clientComm->updateCourse(crs, term);
}

bool CourseManagementUpdateControl::deleteCourse(Course* crs, Term* term){
    return clientComm->deleteCourse(crs,term);

}

bool CourseManagementUpdateControl::registerStudentToCourse(Course* crs, Student* stu, Term* term){
    return clientComm->registerStudentToCourse(crs,stu,term);
}

bool CourseManagementUpdateControl::assignTextbookToCourse(Course* crs, Textbook* text, Term* term){
    return clientComm->assignTextbookToCourse(crs,text,term);
}
