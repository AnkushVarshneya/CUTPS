/*Student class header file
 *Inherited from User class
 *
 *
 */

/*Student header class
 *date last modified: 10/24/2014
 *Need Course and ShoppingCart classes defined to complete definition
 *Need to know implementation of QList for containing a list of registered courses
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
