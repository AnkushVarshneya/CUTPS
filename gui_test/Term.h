/*Term header class
 *Date last modified: 24/10/2014
 *
 */
#ifndef TERM_H
#define TERM_H

#include <QString>
#include <QDate>
#include "Course.h"
using namespace std;


class Course;
class Student;

class Term{
public:
    Term();
    Term(QDate,QDate);
    ~Term();
    QDate           getStartDate();
    QDate           getEndDate();
    QList<Course*>& getTermCourses();
    qint32          getTermID();

    void            setStartDate(int,int,int);
    void            setEndDate(int,int,int);
    void            setTermID(qint32);


private:
    QDate           startDate;
    QDate           endDate;
    QList<Course*>  courses;
    qint32          termID;
};

std::ostream& operator<<(std::ostream&,  Term&);

#endif // TERM_H
