/* Combines Classes of Serializer and ManagementControl in the Client Communicator Subsystem
 *This Class makes use of the Singleton design pattern, as potentially the client can be using
 *Both the Content management and Course management features, in which their management facades
 *Have an UpdateControl which has this class. To avoid potential problems in having
 *Multiple TCP connections with the server for one client, we use this singleton design pattern
 *Traceabilty: SS-05 (Part of Client Communicator Subsystem)
 */

#include "ClientCommunicatorRequestManager.h"

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
    QList<Term*>*       retrieveAllTerms() throw (QString);
    QList<Course*>*     retrieveContent(Student*, Term*) throw (QString);
    ShoppingCart*       retrieveShoppingCart(Student*) throw (QString);
    bool                updateShoppingCart(Student*, PurchasableItem*, qint32) throw (QString);
    bool                checkOutShoppingCart(Student*) throw (QString);
    bool                emptyShoppingCart(Student*) throw (QString);
    bool                updatePaymentInformation(Student*, PaymentInformation*) throw (QString);
    PaymentInformation* retrieveStudentPaymentInformation(Student*) throw (QString);
    QList<Textbook*>*   retrieveAllContent() throw (QString);
    bool                updateContent(Textbook*) throw (QString);
    bool                deleteContent(PurchasableItem*) throw (QString);
    QList<Course*>*     retrieveCourseList(Term*) throw (QString);
    QList<Student*>*    retrieveCourseStudents(Course*, Term*) throw (QString);
    QList<Student*>*    retrieveAllStudents() throw (QString);
    QList<Textbook*>*   retrieveCourseTextbooks(Course*, Term*) throw (QString);
    QList<Textbook*>*   retrieveAllTextbooks() throw (QString);
    bool                updateCourse(Course*, Term*) throw (QString);
    bool                deleteCourse(Course*, Term*) throw (QString);
    bool                registerStudentToCourse(Course*, Student*, Term*) throw (QString);
    bool                assignTextbookToCourse(Course*, Textbook*, Term*) throw (QString);
    void                setConnectToHost(QHostAddress, int);
private:
    ClientCommunicatorRequestManager            requestManager;
    static ClientCommunicatorManagementControl* instance;
};

#endif // CLIENTCOMMUNICATORMANAGEMENTCONTROL_H
