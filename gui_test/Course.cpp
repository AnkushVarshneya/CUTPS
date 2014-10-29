#include "Course.h"


//Constructor
Course::Course(QString c, QString s, QString i) :

    courseCode(c), section(s){}

//Students and Textbooks persist after a Course is deleted
Course::~Course(){}

//GETTERS
QString Course::getCourseCode(){return courseCode;}
QString Course::getCourseSection(){return courseSection;}
Term* Course::getTerm(){return term;}
QString Course::getInstructor(){return instructor;}
QList<Student*>& Course::getRegisteredStudents(){return students;}
QList<Textbook*>& Course::getRequiredTextbooks(){return requiredTextbooks;}

//SETTERS
void Course::setCourseCode(QString c){courseCode = c;}
void Course::setCourseSection(QString s){courseSection = s;}
void Course::setTerm(Term* t){term = t;}
void Course::setInstructor(QString i){instructor = i;}

//Adds a Student to the Course
void Course::addStudent(Student* student){
    students.push_back(student);
}

//Adds a Textbook to the Course
void Course::addTextbook(Textbook* textbook){
    requiredTextbooks.push_back(textbook);
}
