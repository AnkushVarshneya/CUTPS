#include "APIControl.h"
#include "QueryControl.h"

APIControl::APIControl()
{

}

//API studentViewTextbooks() that takes in the json object
//Reads it, creates a query control to get the list of courses
//That the student is registered in, and sends back the result to the client
QJsonObject& APIControl::studentViewTextbooks(QJsonObject json) {
    QString studentNumber = json["Student Number"].toString();
    Term term;
    term.read(json["Term"].toObject());
    QueryControl *query = new QueryControl();
    QList<Course*>& result = query->studentViewTextbooks(studentNumber, term.getTermID());
    delete query;
    QJsonArray resultArray;
    foreach(Course crs, result){
        QJsonObject json;
        crs.write(json);
        resultArray.append(json);
    }

    QJsonObject r;
    r["courses:"] = resultArray;
    qDebug << r;
    return temp;
}
