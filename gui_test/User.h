/*User class header file
 *Date last modified 10/23/2014
 *Inherited by Student and ContentManager classes
 *Author Rob
 */

#ifndef USER_H
#define USER_H

#include <QString>

class User {

public:
    User();
    QString getUserID();
    QString getFirstName();
    QString getLastName();
    virtual void setUserID(QString) = 0;
    void setFirstName(QString);
    void setLastName(QString);


protected:
    QString userID;
    QString password;
    QString firstName;
    QString lastName;

};

#endif // USER_H
