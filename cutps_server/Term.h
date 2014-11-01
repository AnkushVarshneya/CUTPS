/*Term header class
 *Date last modified: 24/10/2014
 *
 */
#ifndef TERM_H
#define TERM_H

#include <QString>
#include <QDate>
#include "Course.h"
#include "CUtpsDataObject.h"
using namespace std;


class Course;


class Term : CUtpsDataObject{
public:
    Term();
    Term(QDate,QDate, qint32);
    ~Term();
    QDate           getStartDate() const;
    QDate           getEndDate() const;
    QList<Course*>& getTermCourses();
    qint32          getTermID() const;

    void            setStartDate(int,int,int);
    void            setEndDate(int,int,int);
    void            setTermID(qint32);

    void            read(const QJsonObject &json);
    void            write(QJsonObject &json) const;



private:
    QDate           startDate;
    QDate           endDate;
    QList<Course*>  courses;
    qint32          termID;
};

std::ostream& operator<<(std::ostream&,  Term&);

#endif // TERM_H
