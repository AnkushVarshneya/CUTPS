
#include "Term.h"
#include <string>

Term::Term(string a,string b){
    startDate = a;
    endDate = b;
}

int Term::setStartDate(string a){
    startDate = a;
    return 0;
}
int Term::setEndDate(string a){
    endDate = a;
    return 0;
}
int Term::addCourse(Course* aCourse){
    courses << aCourse;
    return 0;
}
