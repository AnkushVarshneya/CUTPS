/*
 *The Server Controller responsible for using the QueryControl to query the database for persistently stored data
 *
 *Traceability: SS-06 (Part of Server Subsystem)
 *
 *
 */

#include "QueryControl.h"
#include "Course.h"
#include "ShoppingCart.h"
#include <QList>

#ifndef SERVERSTORAGECONTROL_H
#define SERVERSTORAGECONTROL_H

class ServerStorageControl
{
public:
    ServerStorageControl();

    //Student API
    QList<Term*>*       retrieveAllTerms();
    QList<Course*>*     retrieveContent(Student*, Term*);
    ShoppingCart*       retrieveShoppingCart(Student*);
    bool                updateShoppingCart(Student*, PurchasableItem*, qint32);
    bool                checkOutShoppingCart(Student*);
    bool                updatePaymentInformation(Student*, PaymentInformation*);
    PaymentInformation* retrievePaymentInformation(Student*);
    bool                emptyShoppingCart(Student*);

    //Content Manager API
    QList<Course*>*     retrieveCourseList(qint32);
    QList<Student*>*    retrieveStudentList(Course*, qint32);
    QList<Student*>*    retrieveAllStudentList();
    QList<Textbook*>*   retrieveTextbookList(Course*, qint32);
    QList<Textbook*>*   retrieveAllTextbookList();
    QList<Textbook*>*   retrieveAllContent();
    bool                updateContent(Textbook*);
    bool                deleteContent(PurchasableItem*);
    bool                updateCourse(Course*, qint32);
    bool                deleteCourse(Course*, qint32);
    bool                updateCourseStudentLink(Course*, qint32, Student*);
    bool                updateCourseTextbookLink(Course*, qint32, Textbook*);


private:

};

#endif // SERVERSTORAGECONTROL_H
