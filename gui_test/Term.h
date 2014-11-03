/*Term header class
 *
 *Purpose of this class: An academic term, usually 4 months in length (Summer terms can be considered
 *to have 2 month sub-terms). A term will have a start and end date and a list of courses offered.
 *Will be used by Students to easily search for Textbooks for the registered courses they are in for a given term
 *
 *Traceability: EO-09
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
    Term(QDate = QDate::fromString("20140905","yyyyMMdd"),QDate = QDate::fromString("20141209","yyyyMMdd"), qint32 = 0);
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
