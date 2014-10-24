#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <QList>

class Course{
public:

private:
    string courseCode;
    string section;
    string term;
    string instructor;
    QList<Student> students;
    QList<Textbook> textbooks;





};


#endif // COURSE_H
