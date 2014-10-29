
#include "Term.h"

Term::Term()
{

}

Term::Term(QDate a, QDate b)
{
    startDate = a;
    endDate = b;
}

QDate Term::getStartDate()
{
    return startDate;
}

QDate Term::getEndDate()
{
    return endDate;
}

QList<Course*>& Term::getTermCourses()
{
    return courses;
    //return &courses?
}

void Term::setStartDate(int year, int month, int day)
{
    startDate.setDate(year, month, day);
}

void Term::setEndDate(int year, int month, int day)
{
    endDate.setDate(year, month, day);
}
