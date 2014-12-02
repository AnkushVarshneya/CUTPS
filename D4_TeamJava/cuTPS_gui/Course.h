/*Course class header file
 * Inherited from CUtpsDataObject
 *
 * Description: A course offering for a given term
 * Defined by its course code (8 characters, first 4 letters department, last 4 letters digits)
 * course section letter (A,B,C...)
 * Has an instructor, list of registered students and required textbook(s)
 *
 * Traceability: EO-08
 *
 */
#ifndef COURSE_H
#define COURSE_H

#include "Term.h"
#include <QString>
#include <QList>
#include "Student.h"
#include "Textbook.h"

#include "CUtpsDataObject.h"

class Term;
class Student;

class Course: CUtpsDataObject {
public:

    Course(QString = "COMP3004", QString = "B", QString = "Dr. Laurendeau");

    ~Course();


    //Getters
    QString             getCourseCode() const;
    QString             getCourseSection() const;
    Term*               getTerm() const;
    QString             getInstructor() const;
    QList<Student*>&    getRegisteredStudents();
    QList<Textbook*>&   getRequiredTextbooks();

    //Setters
    void                setCourseCode(QString);
    void                setCourseSection(QString);
    void                setTerm(Term*);
    void                setInstructor(QString);
    void                addStudent(Student*);
    void                addTextbook(Textbook*);

    //Read and write to json concrete functions
    void                read(const QJsonObject &json);
    void                write(QJsonObject &json) const;

private:
    QString             courseCode;
    QString             courseSection;
    Term*               term;
    QString             instructor;
    QList<Student*>     students;
    QList<Textbook*>    requiredTextbooks;

};

std::ostream& operator<<(std::ostream&,  Course&);

#endif // COURSE_H
