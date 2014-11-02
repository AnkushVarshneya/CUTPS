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
User::User(QString user, QString pass, QString fName, QString lName)
    : username(user), password(pass), firstName(fName), lastName(lName){}

//Destructor
User::~User() { } ;


//Getters
QString User::getUsername() const {return username;}
QString User::getFirstName() const {return firstName;}
QString User::getLastName() const {return lastName;}

//Setters
void User::setPass(QString a) {password = a;}
void User::setFirstName(QString a){firstName = a;}
void User::setLastName(QString a){lastName = a;}

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
    firstName = json["firstName"].toString();
    lastName = json["lastName"].toString();
}

//Write to JSON object attributes pertaining to User
//used by derived classes to set base class attributes
void User::write(QJsonObject &json) const{
    json["username"] = username;
    json["password"] = password;
    json["firstName"] = firstName;
    json["lastName"] = lastName;
}


