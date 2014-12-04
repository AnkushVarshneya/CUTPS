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
    qDebug() << res.toJson();

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
