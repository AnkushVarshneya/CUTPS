/*Course header file
 *date last modified: 10/24/2014
 *
 */
#ifndef COURSE_H
#define COURSE_H

#include <QString>
#include <QList>
#include "Student.h"
#include "Textbook.h"
#include "Term.h"

using namespace std;

class Course{
public:
    Course();
    ~Course();

    QString              getCourseCode();
    QString              getSection();
    Term                 getTerm();
    QString              getInstructor();
    QList<Student*>&     getRegisteredStudents();
    QList<Textbook*>&    getRequiredTextbooks();

private:
    QString              courseCode;
    QString              section;
    Term                 term;
    QString              instructor;
    QList<Student*>      students;
    QList<Textbook*>     requiredTextbooks;

};


#endif // COURSE_H
