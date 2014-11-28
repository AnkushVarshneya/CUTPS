#ifndef QUERYCONTROL_H
#define QUERYCONTROL_H

#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "Course.h"
#include "PaymentInformation.h"
#include "Term.h"
#include "Textbook.h"
#include "Chapter.h"

class QueryControl
{

public:
    QueryControl();

    bool addPurchasableItemTO();
    QList<Course*>& studentViewTextbooks(QString, qint32) const;
    PaymentInformation& getExistingBillingInfo(QString) const;
    bool saveBillingInformation(const QString, PaymentInformation*);

    bool createTextbook(Textbook*);
    bool createCourse(Course*, qint32);
    bool linkTextbook(Textbook*, Course*, qint32);
    QList<Textbook*>& viewAllTextbooks(qint32);
    QList<Course*>& viewCourses(qint32);
    QList<Term*>& viewAllTerm();

    bool resetDatabase();

    private:
};

#endif
