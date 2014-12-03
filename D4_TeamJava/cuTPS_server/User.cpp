/* User class source file
 *
 * Inherited by ContentManager and Student
 *
 * Included functions:
 * - GETTERS: getUsername(), getFirstName(), getLastName()
 * - SETTERS: setPass(QString), setFirstName(QString), setLastName(QString)
 * - validatePass(QString)
 *
 * Traceability: EO-01 in Deliverable 1
 */
#include "User.h"

//Constructor
User::User(QString user, QString pass, QString fName)
    : username(user), password(pass), fullName(fName){}

//Destructor
User::~User(){};


//Getters
QString User::getUsername() const {return username;}
QString User::getFullName() const {return fullName;}

//Setters
void User::setPass(QString a) {password = a;}
void User::setFullName(QString n){fullName = n;}

//Input, a string argument,
//returns true if this password matches with the argument
bool User::validatePass(QString a) const{
    return (password == a);
}

//Read from JSON object attributes pertaining to User
//Used by derived classes to set these attributes
void User::read(const QJsonObject &json){
    username = json["username"].toString();
    password = json["password"].toString();
    fullName = json["fullName"].toString();
}

//Write to JSON object attributes pertaining to User
//used by derived classes to set base class attributes
void User::write(QJsonObject &json) const{
    json["username"] = username;
    json["password"] = password;
    json["fullName"] = fullName;
}


