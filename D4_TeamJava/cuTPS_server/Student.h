/*Student class header file
 *Inherited from User class
 *
 *Description: A Student user will be a customer in CUTPS
 *A student potentially has saved payment info
 *A student has a list of courses he/she is registered in
 *A student has a shopping cart which is an inventory of added items by the student
 *
 *Traceability : EO-02
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
    Student(QString = "100848921", QString = "johndoe@cmail.carleton.ca", QString = "generic"
            , QString = "password", QString = "John Doe");
    ~Student();
    QString                 getStudentNum() const;
    QString                 getcMail() const;
    PaymentInformation      getpayInfo();
    QList<Course*>&         getRegisteredCourses();
    ShoppingCart            getShoppingCart();
    void                    setUsername(QString);
    void                    setStudentNum(QString);
    void                    setcMail(QString);
    void                    setPayInfo(const PaymentInformation&);

    void                    addCourse(Course *course);

    void                    read(const QJsonObject &json);
    void                    write(QJsonObject &json) const;

    //void                    addItemToShoppingCart(PurchasableItem*);

private:
    QString                 studentNum;
    QString                 cMail;
    PaymentInformation      payInfo;
    QList<Course*>          registeredCourses;
    ShoppingCart            shoppingCart;


};
#endif // STUDENT_H
