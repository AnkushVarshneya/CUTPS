#include "User.h"

User::User(QString userID, QString pass, QString fName, QString lName){
    setUserID(userID);
    setPass(pass);
    setFirstName(fName);
    setLastName(lName);
}

void User::setUserID(QString a)
{
    userID = a;
}

void User::setPass(QString a)
{
    password = a;
}

void User::setFirstName(QString a)
{
    firstName = a;
}

void User::setLastName(QString a)
{
    lastName = a;
}

