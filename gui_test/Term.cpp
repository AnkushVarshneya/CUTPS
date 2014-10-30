
#include "Term.h"

Term::Term(){}

Term::Term(QDate a, QDate b){
    startDate = a;
    endDate = b;
}

QDate Term::getStartDate(){return startDate;}
QDate Term::getEndDate(){return endDate;}
QList<Course*>& Term::getTermCourses(){
    return courses;
    //return &courses?
}
qint32 Term::getTermID(){return termID;}

void Term::setStartDate(int year, int month, int day){
    startDate.setDate(year, month, day);
}
void Term::setEndDate(int year, int month, int day){
    endDate.setDate(year, month, day);
}
void Term::setTermID(qint32 a){termID = a;}

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
