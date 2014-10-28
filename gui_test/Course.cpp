#include "Course.h"

Course::Course()
{

}

Course::~Course()
{

}

QString Course::getCourseCode()
{
    return courseCode;
}

QString Course::getSection()
{
    return section;
}

Term* Course::getTerm()
{
    return term;
}

QString Course::getInstructor()
{
    return instructor;
}

QList<Student*>& Course::getRegisteredStudents()
{
    return students;
}

QList<Textbook*>& Course::getRequiredTextbooks()
{
    return requiredTextbooks;
}
