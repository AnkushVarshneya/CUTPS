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

private:
    QSqlDatabase db;
};

#endif // QUERYCONTROL_H
