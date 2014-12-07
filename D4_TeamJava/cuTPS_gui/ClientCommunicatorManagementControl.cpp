#include "ClientCommunicatorManagementControl.h"

ClientCommunicatorManagementControl::ClientCommunicatorManagementControl()
{
}

ClientCommunicatorManagementControl* ClientCommunicatorManagementControl::instance = 0;


//Part of Singleton DP, if the instance is 0, make a new instance of the
//ClientCommunicatorManagementControl, eitherway return that one instance.
ClientCommunicatorManagementControl*  ClientCommunicatorManagementControl::getInstance(){
    if (instance == 0){
        instance = new ClientCommunicatorManagementControl();
    }
    return instance;
}

QList<Term*>* ClientCommunicatorManagementControl::retrieveAllTerms(){
    QJsonObject api_server_call;
    //Set API call to initiate on serverside
    QString functionCall = "retrieveAllTerms()";
    api_server_call["Function:"] = functionCall;

    requestManager.send(api_server_call);
    QJsonDocument res;
    while (res.isEmpty()) {
        requestManager.getTcp()->waitForReadyRead();
        res = requestManager.getResult();
    }

    //Placeholder to when we read back from the server to get the list of textbooks
    QList<Term*>* result = new QList<Term*>();
    QJsonArray termArray = res.object()["terms:"].toArray();
    if(!termArray.isEmpty()){
        for (int termIndex = 0; termIndex<termArray.size();++termIndex){
            QJsonObject termObject = termArray[termIndex].toObject();
            Term* newTerm = new Term();
            newTerm->read(termObject);
            result->append(newTerm);
        }
    }
    requestManager.resetBuffer();
    return result;
}

QList<Course*>* ClientCommunicatorManagementControl::retrieveContent(Student *stu, Term *term){
    if(stu == 0 || term == 0){
        return 0;
    }
    QJsonObject api_server_call;
    QString functionCall = "retrieveContent()";
    api_server_call["Function:"] = functionCall;

    QJsonObject studentObject;
    stu->write(studentObject);
    api_server_call["Student"] = studentObject;

    QJsonObject termObject;
    term->write(termObject);
    api_server_call["Term"] = termObject;

    requestManager.send(api_server_call);
    QJsonDocument res;
    while (res.isEmpty()) {
        requestManager.getTcp()->waitForReadyRead();
        res = requestManager.getResult();
    }

    QList<Course*>* result = new QList<Course*>();
    QJsonArray courseArray = res.object()["courses:"].toArray();
    if(!courseArray.isEmpty()){
        for (int crsIndex = 0; crsIndex<courseArray.size();++crsIndex){
            QJsonObject crsObject = courseArray[crsIndex].toObject();
            Course* newCrs = new Course();
            newCrs->read(crsObject);
            result->append(newCrs);
        }
    }
    requestManager.resetBuffer();
    return result;
}

ShoppingCart* ClientCommunicatorManagementControl::retrieveShoppingCart(Student* stu){
    if(stu == 0){
        return 0;
    }
    QJsonObject api_server_call;
    QString functionCall = "retrieveShoppingCart()";
    api_server_call["Function:"] = functionCall;

    QJsonObject studentObject;
    stu->write(studentObject);
    api_server_call["student"] = studentObject;

    requestManager.send(api_server_call);
    QJsonDocument res;
    while (res.isEmpty()) {
        requestManager.getTcp()->waitForReadyRead();
        res = requestManager.getResult();
    }

    ShoppingCart* result = new ShoppingCart();
    result->read(res.object()["shoppingcart"].toObject());
    requestManager.resetBuffer();
    return result;
}

bool ClientCommunicatorManagementControl::updateShoppingCart(Student *stu, PurchasableItem *item, qint32 quantity){
    if(stu == 0 || item == 0){
        return false;
    }
    QJsonObject api_server_call;
    QString functionCall = "updateShoppingCart()";
    api_server_call["Function:"] = functionCall;

    QJsonObject studentObject;
    stu->write(studentObject);
    api_server_call["student"] = studentObject;

    QJsonObject itemObject;
    item->write(itemObject);
    api_server_call["purchasableItem"] = itemObject;

    api_server_call["quantity"] = quantity;

    requestManager.send(api_server_call);
    QJsonDocument res;
    while (res.isEmpty()) {
        requestManager.getTcp()->waitForReadyRead();
        res = requestManager.getResult();
    }

    bool result = res.object()["success"].toBool();
    requestManager.resetBuffer();
    return result;
}

bool ClientCommunicatorManagementControl::checkout(Student* stu,ShoppingCart* cart){
    if (stu == 0 || cart == 0){
        return false;
    }
    QJsonObject api_server_call;
    QString functionCall = "checkout()";
    api_server_call["Function:"] = functionCall;

    QJsonObject stuObject;
    stu->write(stuObject);
    api_server_call["student"] = stuObject;
    QJsonObject cartObject;
    cart->write(cartObject);
    api_server_call["cart"] = cartObject;

    requestManager.send(api_server_call);
    QJsonDocument res;
    while (res.isEmpty()) {
        requestManager.getTcp()->waitForReadyRead();
        res = requestManager.getResult();
    }
    bool result = res.object()["success"].toBool();
    requestManager.resetBuffer();
    return result;
}

bool ClientCommunicatorManagementControl::emptyShoppingCart(Student* stu){
    if(stu == 0){
        return false;
    }
    QJsonObject api_server_call;
    QString functionCall = "emptyShoppingCart()";
    api_server_call["Function:"] = functionCall;

    QJsonObject stuObject;
    stu->write(stuObject);
    api_server_call["student"] = stuObject;
    requestManager.send(api_server_call);
    QJsonDocument res;
    while (res.isEmpty()) {
        requestManager.getTcp()->waitForReadyRead();
        res = requestManager.getResult();
    }

    bool result = res.object()["success"].toBool();
    requestManager.resetBuffer();
    return result;
}

bool ClientCommunicatorManagementControl::updatePaymentInformation(Student* stu, PaymentInformation* payInfo){
    if(stu == 0 || payInfo == 0){
        return false;
    }
    QJsonObject api_server_call;
    QString functionCall = "updatePaymentInformation()";
    api_server_call["Function:"] = functionCall;

    QJsonObject stuObject;
    stu->write(stuObject);
    api_server_call["student"] = stuObject;

    QJsonObject payInfoObject;
    payInfo->write(payInfoObject);
    api_server_call["payInfo"] = payInfoObject;

    requestManager.send(api_server_call);
    QJsonDocument res;
    while (res.isEmpty()) {
        requestManager.getTcp()->waitForReadyRead();
        res = requestManager.getResult();
    }

    bool result = res.object()["success"].toBool();
    requestManager.resetBuffer();
    return result;
}

PaymentInformation* ClientCommunicatorManagementControl::retrieveStudentPaymentInformation(Student* stu){
    if (stu == 0){
        return 0;
    }
    QJsonObject api_server_call;
    QString functionCall = "retrievePaymentInformation()";
    api_server_call["Function:"] = functionCall;
    QJsonObject stuObject;
    stu->write(stuObject);
    api_server_call["student"] = stuObject;
    requestManager.send(api_server_call);
    QJsonDocument res;
    while (res.isEmpty()) {
        requestManager.getTcp()->waitForReadyRead();
        res = requestManager.getResult();
    }
    PaymentInformation* resultPayInfo = new PaymentInformation();
    resultPayInfo->read(res.object()["payInfo"].toObject());
    requestManager.resetBuffer();
    return resultPayInfo;
}

QList<Textbook*>* ClientCommunicatorManagementControl::retrieveAllContent(){
    QJsonObject api_server_call;
    QString functionCall = "retrieveAllContent()";
    api_server_call["Function:"] = functionCall;

    requestManager.send(api_server_call);
    QJsonDocument res;
    while (res.isEmpty()) {
        requestManager.getTcp()->waitForReadyRead();
        res = requestManager.getResult();
    }


    QList<Textbook*>* result = new QList<Textbook*>();
    QJsonArray contentArray = res.object()["allContent"].toArray();

    if(!contentArray.isEmpty()){

        for (int conIndex = 0; conIndex<contentArray.size();++conIndex){
            QJsonObject conObject = contentArray[conIndex].toObject();
            Textbook* newContent = new Textbook();
            newContent->read(conObject);
            result->append(newContent);
        }
    }

    requestManager.resetBuffer();
    return result;

}

bool ClientCommunicatorManagementControl::updateContent(Textbook* text){
    if(text == 0){
        return false;
    }
    QJsonObject api_server_call;
    QString functionCall = "updateContent()";
    api_server_call["Function:"] = functionCall;

    QJsonObject textObject;
    text->write(textObject);
    api_server_call["textbook"] = textObject;
    requestManager.send(api_server_call);

    QJsonDocument res;
    while (res.isEmpty()) {
        requestManager.getTcp()->waitForReadyRead();
        res = requestManager.getResult();
    }

    bool result = res.object()["success"].toBool();
    requestManager.resetBuffer();
    return result;

}

bool ClientCommunicatorManagementControl::deleteContent(PurchasableItem *item){
    if(item == 0){
        return false;
    }
    QJsonObject api_server_call;
    QString functionCall = "deleteContent()";
    api_server_call["Function:"] = functionCall;

    QJsonObject itemObject;
    item->write(itemObject);
    api_server_call["purchasableItem"] = itemObject;

    requestManager.send(api_server_call);
    QJsonDocument res;
    while (res.isEmpty()) {
        requestManager.getTcp()->waitForReadyRead();
        res = requestManager.getResult();
    }

    bool result = res.object()["success"].toBool();
    requestManager.resetBuffer();
    return result;
}

QList<Course*>* ClientCommunicatorManagementControl::retrieveCourseList(Term* term){
    if(term == 0){
        return 0;
    }
    QJsonObject api_server_call;
    QString functionCall = "retrieveCourseList()";
    api_server_call["Function:"] = functionCall;

    QJsonObject termObject;
    term->write(termObject);
    api_server_call["term"] = termObject;

    requestManager.send(api_server_call);
    QJsonDocument res;
    while (res.isEmpty()) {
        requestManager.getTcp()->waitForReadyRead();
        res = requestManager.getResult();
    }

    QList<Course*>* result = new QList<Course*>();
    QJsonArray courseArray = res.object()["courses:"].toArray();
    if(!courseArray.isEmpty()){
        for (int crsIndex = 0; crsIndex<courseArray.size();++crsIndex){
            QJsonObject crsObject = courseArray[crsIndex].toObject();
            Course* newCrs = new Course();
            newCrs->read(crsObject);
            result->append(newCrs);
        }
    }
    requestManager.resetBuffer();
    return result;


}

QList<Textbook*>* ClientCommunicatorManagementControl::retrieveAllTextbooks(){
    QJsonObject api_server_call;
    QString functionCall = "retrieveAllTextbooks()";
    api_server_call["Function:"] = functionCall;

    requestManager.send(api_server_call);
    QJsonDocument res;
    while (res.isEmpty()) {
        requestManager.getTcp()->waitForReadyRead();
        res = requestManager.getResult();
    }

    QList<Textbook*>* result = new QList<Textbook*>();
    QJsonArray textArray = res.object()["textbooks:"].toArray();
    if(!textArray.isEmpty()){
        for (int tIndex = 0; tIndex<textArray.size();++tIndex){
            QJsonObject tObject = textArray[tIndex].toObject();
            Textbook* newText = new Textbook();
            newText->read(tObject);
            result->append(newText);
        }
    }
    requestManager.resetBuffer();
    return result;
}

bool ClientCommunicatorManagementControl::updateCourse(Course* crs, Term* term){
    if(crs == 0 || term == 0){
        return false;
    }
    QJsonObject api_server_call;
    QString functionCall = "updateCourse()";
    api_server_call["Function:"] = functionCall;

    QJsonObject courseObject;
    crs->write(courseObject);
    api_server_call["course"] = courseObject;

    QJsonObject termObject;
    term->write(termObject);
    api_server_call["term"] = termObject;

    requestManager.send(api_server_call);
    QJsonDocument res;
    while (res.isEmpty()) {
        requestManager.getTcp()->waitForReadyRead();
        res = requestManager.getResult();
    }

    bool result = res.object()["success"].toBool();
    requestManager.resetBuffer();
    return result;

}

bool ClientCommunicatorManagementControl::deleteCourse(Course* crs, Term* term){
    if(crs == 0 || term == 0){
        return false;
    }

    QJsonObject api_server_call;
    QString functionCall = "deleteCourse()";
    api_server_call["Function:"] = functionCall;

    QJsonObject courseObject;
    crs->write(courseObject);
    api_server_call["course"] = courseObject;

    QJsonObject termObject;
    term->write(termObject);
    api_server_call["term"] = termObject;

    requestManager.send(api_server_call);
    QJsonDocument res;
    while (res.isEmpty()) {
        requestManager.getTcp()->waitForReadyRead();
        res = requestManager.getResult();
    }

    bool result = res.object()["success"].toBool();
    requestManager.resetBuffer();
    return result;
}

bool ClientCommunicatorManagementControl::registerStudentToCourse(Course* crs, Student* stu, Term* term){
    if (crs == 0|| stu == 0 || term == 0){
        return false;
    }

    QJsonObject api_server_call;
    QString functionCall = "updateCourseStudentLink()";
    api_server_call["Function:"] = functionCall;

    QJsonObject courseObject;
    crs->write(courseObject);
    api_server_call["course"] = courseObject;

    QJsonObject stuObject;
    stu->write(stuObject);
    api_server_call["student"] = stuObject;

    QJsonObject termObject;
    term->write(termObject);
    api_server_call["term"] = termObject;

    requestManager.send(api_server_call);
    QJsonDocument res;
    while (res.isEmpty()) {
        requestManager.getTcp()->waitForReadyRead();
        res = requestManager.getResult();
    }

    bool result = res.object()["success"].toBool();
    requestManager.resetBuffer();
    return result;
}

bool ClientCommunicatorManagementControl::assignTextbookToCourse(Course* crs, Textbook* text, Term* term){
    if (crs == 0|| text == 0 || term == 0){
        return false;
    }

    QJsonObject api_server_call;
    QString functionCall = "updateCourseTextbookLink()";
    api_server_call["Function:"] = functionCall;

    QJsonObject courseObject;
    crs->write(courseObject);
    api_server_call["course"] = courseObject;

    QJsonObject textObject;
    text->write(textObject);
    api_server_call["textbook"] = textObject;

    QJsonObject termObject;
    term->write(termObject);
    api_server_call["term"] = termObject;

    requestManager.send(api_server_call);
    QJsonDocument res;
    while (res.isEmpty()) {
        requestManager.getTcp()->waitForReadyRead();
        res = requestManager.getResult();
    }

    bool result = res.object()["success"].toBool();
    requestManager.resetBuffer();
    return result;
}
