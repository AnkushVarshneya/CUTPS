#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <QList>

using namespace std;

class Course{
public:

private:
    string courseCode;
    string section;
    QList<Term> terms;
    string instructor;
    QList<Student*> students;
    QList<Textbook*> requiredTextbooks;

};


#endif // COURSE_H
