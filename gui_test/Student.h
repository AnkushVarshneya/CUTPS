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
    QString getStudentNum();
    QString getcMail();
    PaymentInformation getpayInfo();
    void setStudentNum(QString);
    void setcMail(QString);
    void setPayInfo(const PaymentInformation&);


private:
    QString studentNum;
    QString cMail;
    PaymentInformation payInfo;
    QList<Course*> registeredCourses;
    ShoppingCart shoppingCart;


};
#endif // STUDENT_H
