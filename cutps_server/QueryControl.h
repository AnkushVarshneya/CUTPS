/*Query Control class header
 *
 *Purpose: This class is used to query the database relevant to the
 *functionality and features involved in Student features and Content Features
 *No server-API functions relevant to AddContent, ViewShoppingCart, and EmptyShoppingCart
 *are to be queried as the ShoppingCart is not stored between sessions
 *
 *Each time the Query is finished, the database resets to keep the test cases
 *expected outcomes
 *
 *NR-22
 *
 */

#ifndef QUERYCONTROL_H
#define QUERYCONTROL_H

#include <QList>
#include "Course.h"
#include "Term.h"
#include <QtSql>
class QueryControl
{
public:
    QueryControl();
    ~QueryControl();
    QList<Course*>& studentViewTextbooks(QString studentNumber, qint32 termID) const;
    PaymentInformation* getExistingBillingInfo(QString studentNumber) const;
    bool saveBillingInformation(const QString, PaymentInformation*);
    bool createCourse(Course*, qint32);
    bool createTextbook(Textbook*);
    QList<Textbook*>& viewAllTextbooks(qint32);
    QList<Course*>& viewCourses(qint32);
    bool linkTextbook(Textbook*, Course*, qint32);
    bool resetDatabase();
private:
    QSqlDatabase db;
};

#endif // QUERYCONTROL_H
