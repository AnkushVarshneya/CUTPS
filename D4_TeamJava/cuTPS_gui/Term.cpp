
#include "Term.h"


Term::Term(QDate a, QDate b, qint32 id, QString name): startDate(a), endDate(b), termID(id), termName(name){}

Term::~Term(){
}

QDate Term::getStartDate() const{return startDate;}
QDate Term::getEndDate() const{return endDate;}

qint32 Term::getTermID() const{return termID;}
QString Term::getTermName() const {return termName;}

void Term::setStartDate(int year, int month, int day){
    startDate.setDate(year, month, day);
}
void Term::setEndDate(int year, int month, int day){
    endDate.setDate(year, month, day);
}
void Term::setTermID(qint32 a){termID = a;}

void Term::setTermName(QString s){termName = s;}



//JSON read and write functions

void Term::read(const QJsonObject &json){
    startDate = QDate::fromString(json["startDate"].toString(), "yyyyMMdd");
    endDate = QDate::fromString(json["endDate"].toString(), "yyyyMMdd");
    termID = json["termID"].toDouble();
    termName = json["termName"].toString();
}

void Term::write(QJsonObject &json) const{
    json["startDate"] = startDate.toString("yyyyMMdd");
    json["endDate"] = endDate.toString("yyyyMMdd");
    json["termID"] = termID;
    json["termName"] = termName;
}

