/*Student class header file
 *Inherited from User class
 *Date Last modified: 24/10/2014
 *
 */

#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include "PaymentInformation.h"
#include "Course.h"
#include "ShoppingCart.h"

class Course;

#include <QList>
class Student : public User {

public:
    Student();
    ~Student();
    QString                 getStudentNum();
    QString                 getcMail();
    PaymentInformation      getpayInfo();
    QList<Course*>&         getRegisteredCourses();
    void                    setStudentNum(QString);
    void                    setcMail(QString);
    void                    setPayInfo(const PaymentInformation&);


private:
    QString                 studentNum;
    QString                 cMail;
    PaymentInformation      payInfo;
    QList<Course*>          registeredCourses;
    ShoppingCart            shoppingCart;


};
#endif // STUDENT_H
