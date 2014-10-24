/*Student class header file
 *Inherited from User class
 *
 *
 */

#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include "PaymentInformation.h"
#include "Course.h"
#include "ShoppingCart.h"

#include <QList>
class Student : public User {

public:
    Student();
    string getStudentNum();
    string getcMail();
    PaymentInformation getpayInfo();
    void setStudentNum(string);
    void setcMail(string);
    void setPayInfo(const PaymentInformation&);


private:
    string studentNum;
    string cMail;
    PaymentInformation payInfo;
    QList<Course*> registeredCourses;
    ShoppingCart shoppingCart;


};
#endif // STUDENT_H
