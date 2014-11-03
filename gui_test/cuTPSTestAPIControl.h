#ifndef CUTPSTESTAPICONTROL_H
#define CUTPSTESTAPICONTROL_H

#include "Textbook.h"
#include "Term.h"
#include "PaymentInformation.h"
#include "Course.h"

#include "connectionmanager.h"

#include <QString>
#include <QList>

class cuTPSTestAPIControl
{
public:

    cuTPSTestAPIControl();


    QList<Textbook*> studentViewTextbooks(QString,Term*);
    QList<PurchasableItem*> viewShoppingCart(QString);
    void addContent(QString,qint32,qint32);
    void emptyShoppingCart(QString);
    PaymentInformation* getExistingBillingInfo(QString);
    void savePaymentInformation(QString,PaymentInformation*);

    void createTextbook(Textbook*);
    bool createCourse(Course*);
    void linkTextbook(Textbook*,Course*);
    QList<Textbook*> cManagerViewTextbooks(Term*);
    QList<Course*> viewCourses(Term*);

private:
    ConnectionManager* connectionManager;

};

#endif // CUTPSTESTAPICONTROL_H
