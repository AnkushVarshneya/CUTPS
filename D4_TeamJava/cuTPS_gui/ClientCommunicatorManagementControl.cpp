#include "ClientCommunicatorManagementControl.h"

ClientCommunicatorManagementControl::ClientCommunicatorManagementControl()
{
}

QList<Term*>* ClientCommunicatorManagementControl::retrieveAllTerms(){
    QJsonObject api_server_call;
    //Set API call to initiate on serverside
    QString functionCall = "retrieveAllTerms()";
    api_server_call["Function:"] = functionCall;

    requestManager.send(api_server_call);
    requestManager.getTcp()->waitForReadyRead();
    QJsonDocument res = requestManager.getResult();

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
    return result;
}

QList<Course*>* ClientCommunicatorManagementControl::retrieveContent(Student *stu, Term *term){
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
    requestManager.getTcp()->waitForReadyRead();
    QJsonDocument res = requestManager.getResult();

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
    return result;
}

ShoppingCart* ClientCommunicatorManagementControl::retrieveShoppingCart(Student* stu){
    QJsonObject api_server_call;
    QString functionCall = "retrieveShoppingCart()";
    api_server_call["Function:"] = functionCall;

    QJsonObject studentObject;
    stu->write(studentObject);
    api_server_call["student"] = studentObject;

    requestManager.send(api_server_call);
    requestManager.getTcp()->waitForReadyRead();
    QJsonDocument res = requestManager.getResult();

    ShoppingCart* result = new ShoppingCart();
    result->read(res.object()["shoppingcart"].toObject());
    return result;
}

bool ClientCommunicatorManagementControl::updateShoppingCart(Student *stu, PurchasableItem *item, qint32 quantity){
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
    requestManager.getTcp()->waitForReadyRead();
    QJsonDocument res = requestManager.getResult();

    bool result = res.object()["success"].toBool();
    return result;
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
    requestManager.resetResult();
    if(!contentArray.isEmpty()){

        for (int conIndex = 0; conIndex<contentArray.size();++conIndex){
            QJsonObject conObject = contentArray[conIndex].toObject();
            Textbook* newContent = new Textbook();
            newContent->read(conObject);
            result->append(newContent);
        }
    }


    return result;

}
