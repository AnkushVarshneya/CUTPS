#ifndef CUTPSTESTAPICONTROL_H
#define CUTPSTESTAPICONTROL_H

#include "Textbook.h"
#include "Term.h"
#include "PaymentInformation.h"
#include "Course.h"

#include "connectionmanager.h"

#include <QString>
#include <QList>

class cuTPSTestAPIControl : public QObject
{
public:

    cuTPSTestAPIControl();


    QList<Course*>& studentViewTextbooks(QString,Term*);
    QList<PurchasableItem*>& viewShoppingCart(QString);
    bool addContent(QString,qint32,qint32);
    bool emptyShoppingCart(QString);
    PaymentInformation* getExistingPaymentInfo(QString);
    bool savePaymentInfo(QString,PaymentInformation*);

    bool createTextbook(Textbook*);
    bool createCourse(Course*,qint32);
    bool linkTextbook(Textbook*,Course*);
    QList<Textbook*>& cManagerViewTextbooks(Term*);
    QList<Course*>& cManagerViewCourses(Term*);

    void setConnectionManager(ConnectionManager*);

private:
    ConnectionManager* conMan;

private slots:
    void readBytes();

};

#endif // CUTPSTESTAPICONTROL_H
