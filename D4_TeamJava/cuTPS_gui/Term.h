/*Term header class
 *
 *Purpose of this class: An academic term, usually 4 months in length (Summer terms can be considered
 *to have 2 month sub-terms). A term will have a start and end date.
 *Will be used by Students to easily search for Textbooks for the registered courses they are in for a given term
 *
 *Traceability: EO-09
 */
#ifndef TERM_H
#define TERM_H

#include <QString>
#include <QDate>

#include "CUtpsDataObject.h"

using namespace std;





class Term : CUtpsDataObject{
public:
    Term(QDate = QDate::fromString("20140905","yyyyMMdd"),QDate = QDate::fromString("20141209","yyyyMMdd"), qint32 = -1, QString = "fall2014");
    ~Term();

    QDate           getStartDate() const;
    QDate           getEndDate() const;
    QString         getTermID() const;
    void            setStartDate(int,int,int);
    void            setEndDate(int,int,int);
    void            setTermID(QString);
    void            read(const QJsonObject &json);
    void            write(QJsonObject &json) const;

private:
    QDate           startDate;
    QDate           endDate;
    qint32          termID;
    QString         termName;
};



#endif // TERM_H
