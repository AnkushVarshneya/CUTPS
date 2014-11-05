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

private:
    QSqlDatabase db;
};

#endif // QUERYCONTROL_H
