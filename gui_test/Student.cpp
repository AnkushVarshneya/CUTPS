
#include "Student.h"


//Student::Student(){}
//Student::~Student(){}


QString                 Student::getStudentNum(){return studentNum;}
QString                 Student::getcMail(){return cMail;}
PaymentInformation      Student::getpayInfo(){return payInfo;}
QList<Course*>&         Student::getRegisteredCourses(){return registeredCourses;}


void                    Student::setStudentNum(QString n){studentNum = n;}
void                    Student::setcMail(QString m){cMail = m;}
void                    Student::setPayInfo(const PaymentInformation& p){payInfo = p;}

