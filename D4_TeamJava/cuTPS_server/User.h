/*User class header file
 *
 *Inherits from CUtpsDataObject
 *Inherited by Student and ContentManager classes
 *
 *Description: basic User with a username, password, first and last name
 *Is an Abstract class
 *
 *Traceability: EO-01 in Deliverable 1
 */

#ifndef USER_H
#define USER_H

#include <QString>
#include "CUtpsDataObject.h"

class User : CUtpsDataObject{

public:
    User(QString = "generic" ,QString = "password",QString = "John Doe");
    ~User();
    QString         getUsername() const;
    QString         getFullName() const;
    virtual void    setUsername(QString) = 0;
    void            setPass(QString);
    void            setFullName(QString);
    bool            validatePass(QString) const;
    void            read(const QJsonObject &json);
    void            write(QJsonObject &json) const;


protected:
    QString         username;
    QString         password;
    QString         fullName;


};

#endif // USER_H
