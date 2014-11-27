
#include "Term.h"


Term::Term(QDate a, QDate b, qint32 id): startDate(a), endDate(b), termID(id){}

Term::~Term(){
    QList<Course*>::iterator i;
    for (i = courses.begin(); i != courses.end(); i++) {
        delete *i;
    }
}

QDate Term::getStartDate() const{return startDate;}
QDate Term::getEndDate() const{return endDate;}
QList<Course*>& Term::getTermCourses(){
    return courses;
}
qint32 Term::getTermID() const{return termID;}

void Term::setStartDate(int year, int month, int day){
    startDate.setDate(year, month, day);
}
void Term::setEndDate(int year, int month, int day){
    endDate.setDate(year, month, day);
}
void Term::setTermID(qint32 a){termID = a;}


void Term::addCourse(Course* c){
    courses.push_back(c);
}

//JSON read and write functions

void Term::read(const QJsonObject &json){
    startDate = QDate::fromString(json["startDate"].toString(), "yyyyMMdd");
    endDate = QDate::fromString(json["endDate"].toString(), "yyyyMMdd");
    termID = json["termID"].toDouble();
    QJsonArray courseArray = json["courses"].toArray();
    for(int i = 0; i < courseArray.size(); ++i){
        QJsonObject courseObject = courseArray[i].toObject();
        Course* newCourse = new Course();
        newCourse->read(courseObject);
        courses.append(newCourse);
    }
}

void Term::write(QJsonObject &json) const{
    json["startDate"] = startDate.toString("yyyyMMdd");
    json["endDate"] = endDate.toString("yyyyMMdd");
    json["termID"] = termID;

    QJsonArray courseArray;
    foreach(Course* course, courses){
        QJsonObject courseObject;
        course->write(courseObject);
        courseArray.append(courseObject);
    }
    json["courses"] = courseArray;
}

std::ostream& operator<<(std::ostream& o,  Term& term){
    int* syear;
    int* smonth;
    int* sday;

    int* eyear;
    int* emonth;
    int* eday;

    term.getStartDate().getDate(syear,smonth,sday);
    term.getEndDate().getDate(eyear,emonth,eday);
    return o << "Term " << term.getTermID() << endl << "from " << *syear << " " << *smonth << " " << *sday << " to " << *eyear << " " << *emonth << " " << *eday << endl;
}

/*
                QDate           startDate;term.getStartDate() << " to " << term.getEndDate() <<
                QDate           endDate;
                QList<Course*>  courses;
                qint32          termID;

*/
