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

class Term;

class Course{
public:

    Course(QString = "", QString = "", QString = "");

    ~Course();

    QString              getCourseCode();
    QString              getCourseSection();
    Term*                getTerm();
    QString              getInstructor();
    QList<Student*>&     getRegisteredStudents();
    QList<Textbook*>&    getRequiredTextbooks();

    void setCourseCode(QString);
    void setCourseSection(QString);
    void setTerm(Term*);
    void setInstructor(QString);
    void addStudent(Student*);
    void addTextbook(Textbook*);

private:
    QString              courseCode;
    QString              courseSection;
    Term*                term;
    QString              instructor;
    QList<Student*>      students;
    QList<Textbook*>     requiredTextbooks;

};


#endif // COURSE_H
