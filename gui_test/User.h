/*User class header file
 *Inherited by Student and ContentManager classes
 *Author Rob
 */

#ifndef USER_H
#define USER_H

#include <string>

class User {

public:
    User();
    string getUserID();
    string getFirstName();
    string getLastName();
    virtual void setUserID(string) = 0;
    void setFirstName(string);
    void setLastName(string);


protected:
    string userID;
    string password;
    string firstName;
    string lastName;

};

#endif // USER_H
