/*Student class header file
 *Inherited from User class
 *
 *
 */

/*Student header class
 *date last modified: 10/24/2014
 *Need Course and ShoppingCart classes defined to complete definition
 *
 */
#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include "PaymentInformation.h"

class Student : public User {

public:
    Student();
    string getStudentNum();
    string getcMail();
    PaymentInformation getpayInfo();
    void setStudentNum(string);
    void setcMail(string);
    void setPayInfo(PaymentInformation);


private:
    string studentNum;
    string cMail;
    PaymentInformation payInfo;
    //Course array composition here
    //ShoppingCart composition here

};
#endif // STUDENT_H
