/*Term header class
 *Date last modified: 24/10/2014
 *
 */
#ifndef TERM_H
#define TERM_H

#include <QString>
#include <QDate>
#include "Course.h"

class Term{
public:
    Term();
    Term(QDate,QDate);
    ~Term();
    QDate           getStartDate();
    QDate           getEndDate();
    QList<Course*>& getTermCourses();
    void            setStartDate(int,int,int);
    void            setEndDate(int,int,int);


private:
    QDate           startDate;
    QDate           endDate;
    QList<Course*>  courses;
};

#endif // TERM_H
