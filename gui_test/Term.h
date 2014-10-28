#ifndef TERM_H
#define TERM_H

#include <string>
#include "Course.h"

using namespace std;

class Term{
public:
    Term(string,string);
    int setStartDate(string);
    int setEndDate(string);
    int addCourse(Course*);

private:
    string startDate;
    string endDate;
    QList<Course*> courses;
};

#endif // TERM_H
