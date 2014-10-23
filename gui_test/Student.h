/*Student class header file
 *Inherited from User class
 *
 *
 */

#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"

class Student : public User {

public:
    Student();
    string getStudentNum();
    string getcMail();
    void setStudentNum(string);
    void setcMail(string);


private:
    string studentNum;
    string cMail;
    //PaymentInfo composition here
    //Course array composition here
    //ShoppingCart composition here

};
#endif // STUDENT_H
