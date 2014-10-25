/*Content Manager class
 *Date last modified: 10/24/2014
 *
 *ContentManager Has a list of all courses and textbooks
 *Can Create/Modify/Delete content
 *Inherits from User superclass
 */
#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include "User.h"
#include "Course.h"
#include "Textbook.h"

#include <QList>

class ContentManager : public User {

public:
    ContentManager();
    ~ContentManager();
    QList<Course*>& getMasterCourseList();
    QList<Textbook*>& getMasterTextbookList();

private:
    QList<Course*> masterCourseList;
    QList<Textbook*> masterTextbookList;


};
#endif // CONTENTMANAGER_H
