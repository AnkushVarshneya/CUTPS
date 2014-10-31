/*Student class source file
 *
 *Contains functions:
 *GETTERS: getStudentNum(), getcMail(), getpayInfo(), getRegisteredCourses(), getShoppingCart()
 *SETTERS: setStudentNum(), setcMail(), setPayInfo()
 *
 *Also has concrete JSON read and write functions
 *
 *Traceability: EO-02
 */
#include "Student.h"

//Default Constructor
Student::Student(QString stuNum, QString cm, QString userName, QString pass,
                 QString fName, QString lName)
    : studentNum(stuNum), cMail(cm), User(userName,pass,fName,lName){}

//Getters
QString                 Student::getStudentNum() const {return studentNum;}
QString                 Student::getcMail()      const {return cMail;}
PaymentInformation      Student::getpayInfo()          {return payInfo;}
QList<Course*>&         Student::getRegisteredCourses(){return registeredCourses;}
ShoppingCart            Student::getShoppingCart()     {return shoppingCart;}
//Setters
void                    Student::setUsername(QString un){username = un;}
void                    Student::setStudentNum(QString n){studentNum = n;}
void                    Student::setcMail(QString m){cMail = m;}
void                    Student::setPayInfo(const PaymentInformation& p){payInfo = p;}


//JSON read and write concrete functions

//Reads a QJsonObject and sets the Student's components
//To match the extracted info
void Student::read(const QJsonObject &json){
    //Setting base class attributes
    User::read(json);

    //Setting primitive class attributes
    studentNum = json["studentNum"].toString();
    cMail = json["cMail"].toString();
    payInfo.read(json["payInfo"].toObject());

    //Empty the registered courses array TODO: delete allocated memory to prevent memory leak
    registeredCourses.clear();

    //Make a JSONArray from "registeredCourses" key
    QJsonArray regCourseArray = json["registeredCourses"].toArray();

    //For each index in the course array, allocate memory for a new course
    //Make it read the current index's values, and append that course pointer to
    //The list of registered courses
    for (int courseIndex = 0; courseIndex < regCourseArray.size(); ++courseIndex){
        QJsonObject courseObject = regCourseArray[courseIndex].toObject();
        Course* newCourse = new Course();
        newCourse->read(courseObject);
        registeredCourses.append(newCourse);
    }

    shoppingCart.read(json["shoppingCart"].toObject());
}

//Write function for a Student object to a JSON object
void Student::write(QJsonObject &json) const{
    //Writing primitive base class attributes
    User::write(json);

    //Writing primitive types
    json["studentNum"] = studentNum;
    json["cMail"] = cMail;

    //Writing a JSON object for payment information
    QJsonObject paymentInformation;
    payInfo.write(paymentInformation);
    json["payInfo"] = paymentInformation;

    //Writing a JSON array for registered courses
    QJsonArray regCourseArray;
    foreach (const Course* course, registeredCourses){
        QJsonObject courseObject;
        course->write(courseObject);
        regCourseArray.append(courseObject);
    }
    json["registeredCourses"] = regCourseArray;

    //Writing a JSON object for shoppingCart
    QJsonObject cart;
    shoppingCart.write(cart);
    json["shoppingCart"] = cart;




}

