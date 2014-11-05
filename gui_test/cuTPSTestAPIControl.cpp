#include "cuTPSTestAPIControl.h"

cuTPSTestAPIControl::cuTPSTestAPIControl()
{
}

void cuTPSTestAPIControl::setConnectionManager(ConnectionManager* c){
    conMan = c;
//    connect(this->conMan->getTcp(), SIGNAL(readyRead()), this, SLOT(readBytes()));
}


bool cuTPSTestAPIControl::linkTextbook(Textbook* textbook, Course* course){
    return true;
}

//API call studentViewTextbooks where a student number and a term are arguments
//To send over to the server in which the server will query the database
//For the necessary textbooks required for the registered courses
//Traceability: SD-01 (sequence diagram 1)
QList<Course*>& cuTPSTestAPIControl::studentViewTextbooks(QString stuNum, Term *term){

    QJsonObject api_server_call;
    //Set API call to initiate on serverside
    QString functionCall = "studentViewTextbooks()";
    api_server_call["Function:"] = functionCall;

    //Write the student number argument into the api_server_call object
    api_server_call["Student Number"] = stuNum;

    //Write the term argument into the api_server_call object
    QJsonObject termObject;
    term->write(termObject);
    api_server_call["Term"] = termObject;

    conMan->send(api_server_call);
    conMan->getTcp()->waitForReadyRead();
    QJsonDocument res = conMan->getResult();
    qDebug() << res.toJson();

    //Placeholder to when we read back from the server to get the list of textbooks
    QList<Course*> result;
    QJsonArray courseArray = res.object()["courses:"].toArray();
    for (int courseIndex = 0; courseIndex<courseArray.size();++courseIndex){
        QJsonObject courseObject = courseArray[courseIndex].toObject();
        Course* newCourse = new Course();
        newCourse->read(courseObject);
        result.append(newCourse);
    }
    qDebug() << result.front()->getRequiredTextbooks().front()->getItemTitle();
    return result;

}

//API call to view a student's shopping cart
//This function makes a QJsonObject to send over to the server
//Which includes the API function call to execute server-side
//And what student is relevant (given student number)
//Returns a list of purchasable items
QList<PurchasableItem*>& cuTPSTestAPIControl::viewShoppingCart(QString stuNum){
    QJsonObject api_server_call;
    QString functionCall = "viewShoppingCart()";
    api_server_call["Function:"] = functionCall;
    api_server_call["Student Number"] = stuNum;
    conMan->send(api_server_call);
    QList<PurchasableItem*> temp;
    return temp;
}

//API call to add some content to the student's shopping cart
//This function makes a QJsonObject to send over to the server
//Which includes the function name and the arguments to be passed
bool cuTPSTestAPIControl::addContent(QString stuNum, qint32 itemID, qint32 quantity){
    QJsonObject api_server_call;
    QString functionCall = "addContent()";
    api_server_call["Function:"] = functionCall;
    api_server_call["Student Number"] = stuNum;
    api_server_call["Item ID"] = itemID;
    api_server_call["Quantity"] = quantity;
    conMan->send(api_server_call);
    return true;
}

//Empty the student's shopping cart, given the student's student number
bool cuTPSTestAPIControl::emptyShoppingCart(QString stuNum){
    QJsonObject api_server_call;
    QString functionCall = "emptyShoppingCart()";
    api_server_call["Function:"] = functionCall;
    api_server_call["Student Number"] = stuNum;
    conMan->send(api_server_call);
    return true;
}

//Get the existing payment info for a given student
PaymentInformation* cuTPSTestAPIControl::getExistingPaymentInfo(QString stuNum){
    PaymentInformation* paymentInfo = new PaymentInformation();
    QJsonObject api_server_call;
    QString functionCall = "getExistingBillingInfo()";
    api_server_call["Function:"] = functionCall;
    api_server_call["Student Number"] = stuNum;
    conMan->send(api_server_call);
    conMan->getTcp()->waitForReadyRead();


    if(conMan->getResult().isEmpty()){
        return NULL;
    }
    else{
        QJsonObject a = conMan->getResult().object();
        paymentInfo->read(a);
        return paymentInfo;
    }



}

//Save the payment info for a student
bool cuTPSTestAPIControl::savePaymentInfo(QString stuNum, PaymentInformation* payInfo){
    QJsonObject api_server_call;
    QString functionCall = "saveExistingPaymentInfo()";
    api_server_call["Function:"] = functionCall;
    api_server_call["Student Number"] = stuNum;
    QJsonObject payInfoObject;
    payInfo->write(payInfoObject);
    api_server_call["Payment Info"] = payInfoObject;
    conMan->send(api_server_call);
    conMan->getTcp()->waitForReadyRead();

    return conMan->getResult().object()["Boolean:"].toBool();

}

//Create a textbook
bool cuTPSTestAPIControl::createTextbook(Textbook *aTextbook){
    QJsonObject api_server_call;
    QString functionCall = "createTextbook()";
    api_server_call["Function:"] = functionCall;
    QJsonObject textbookObject;
    aTextbook->write(textbookObject);
    api_server_call["Textbook"] = textbookObject;
    conMan->send(api_server_call);
    conMan->getTcp()->waitForReadyRead();
    return conMan->getResult().object()["Boolean:"].toBool();
}

//Create a course
bool cuTPSTestAPIControl::createCourse(Course *aCourse, qint32 termID){
    QJsonObject api_server_call;
    QString functionCall = "createCourse()";
    api_server_call["Function:"] = functionCall;
    QJsonObject courseObject;
    aCourse->write(courseObject);
    api_server_call["Course"] = courseObject;
    api_server_call["TermID"] = termID;
    conMan->send(api_server_call);
    conMan->getTcp()->waitForReadyRead();

    return conMan->getResult().object()["Boolean:"].toBool();
}

//Content Manager View textbooks
QList<Textbook*>& cuTPSTestAPIControl::cManagerViewTextbooks(Term *aTerm){
    QList<Textbook*> textbooks;
    QJsonObject api_server_call;
    QString functionCall = "cManagerViewTextbooks()";
    api_server_call["Function:"] = functionCall;
    QJsonObject termObject;
    aTerm->write(termObject);
    api_server_call["Term"] = termObject;
    conMan->send(api_server_call);
    conMan->getTcp()->waitForReadyRead();
    return textbooks;
}

//Content Manager View Courses
QList<Course*>& cuTPSTestAPIControl::cManagerViewCourses(Term *aTerm){
    QList<Course*> courses;
    QJsonObject api_server_call;
    QString functionCall = "cManagerViewCourses()";
    api_server_call["Function:"] = functionCall;
    QJsonObject termObject;
    aTerm->write(termObject);
    api_server_call["Term"] = termObject;
    conMan->send(api_server_call);
    conMan->getTcp()->waitForReadyRead();

    return courses;
}
