/* Combines Classes of Serializer and ManagementControl in the Client Communicator Subsystem
 *This Class makes use of the Singleton design pattern, as potentially the client can be using
 *Both the Content management and Course management features, in which their management facades
 *Have an UpdateControl which has this class. To avoid potential problems in having
 *Multiple TCP connections with the server for one client, we use this singleton design pattern
 *Traceabilty: SS-05 (Part of Client Communicator Subsystem)
 */

#include "ClientCommunicatorRequestManager.h"
#include "ClientCommunicatorSerializer.h"
#include <QList>
#include "Term.h"
#include "Student.h"

#ifndef CLIENTCOMMUNICATORMANAGEMENTCONTROL_H
#define CLIENTCOMMUNICATORMANAGEMENTCONTROL_H

class ClientCommunicatorManagementControl
{
public:
    ClientCommunicatorManagementControl();
    static ClientCommunicatorManagementControl* getInstance();
    QList<Term*>* retrieveAllTerms();
    QList<Course*>* retrieveContent(Student*, Term*);
    ShoppingCart*   retrieveShoppingCart(Student*);
    bool            updateShoppingCart(Student*, PurchasableItem*, qint32);
    bool            checkout(Student*,ShoppingCart*);
    bool            emptyShoppingCart(Student*);
    bool            updatePaymentInformation(Student*, PaymentInformation*);
    PaymentInformation* retrieveStudentPaymentInformation(Student*);
    QList<Textbook*>* retrieveAllContent();
    bool        updateContent(Textbook*);
    bool        deleteContent(PurchasableItem*);
    QList<Course*>* retrieveCourseList(Term*);
    QList<Student*>*    retrieveCourseStudents(Course*, Term*);
    QList<Student*>*    retrieveAllStudents();
    QList<Textbook*>*   retrieveCourseTextbooks(Course*, Term*);
    QList<Textbook*>* retrieveAllTextbooks();
    bool        updateCourse(Course*, Term*);
    bool        deleteCourse(Course*, Term*);
    bool        registerStudentToCourse(Course*, Student*, Term*);
    bool        assignTextbookToCourse(Course*, Textbook*, Term*);
private:
    ClientCommunicatorRequestManager requestManager;
    ClientCommunicatorSerializer    serializer;
    static ClientCommunicatorManagementControl* instance;
};

#endif // CLIENTCOMMUNICATORMANAGEMENTCONTROL_H
