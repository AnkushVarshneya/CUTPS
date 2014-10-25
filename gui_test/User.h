/*User class header file
 *Date last modified 10/24/2014
 *Inherited by Student and ContentManager classes
 *Author Rob
 */

#ifndef USER_H
#define USER_H

#include <QString>

class User {

public:
    User();
    ~User();
    QString         getUserID();
    QString         getFirstName();
    QString         getLastName();
    void            setUserID(QString);
    void            setFirstName(QString);
    void            setLastName(QString);


protected:
    QString         userID;
    QString         password;
    QString         firstName;
    QString         lastName;

};

#endif // USER_H
