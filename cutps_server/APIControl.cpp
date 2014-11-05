#include "APIControl.h"
#include "QueryControl.h"

APIControl::APIControl()
{

}

//API studentViewTextbooks() that takes in the json object
//Reads it, creates a query control to get the list of courses
//That the student is registered in, and sends back the result to the client
QJsonObject APIControl::studentViewTextbooks(QJsonObject json) {
    QString studentNumber = json["Student Number"].toString();
    Term term;
    term.read(json["Term"].toObject());
    QueryControl *query = new QueryControl();
    QList<Course*>& result = query->studentViewTextbooks("100853074", 1);
    delete query;
    QJsonArray resultArray;
    foreach(Course *crs, result){
        QJsonObject json;
        crs->write(json);
        resultArray.append(json);
    }

    QJsonObject r;
    r["courses:"] = resultArray;
    qDebug() << r;
    return r;
}
QJsonObject APIControl::getExistingPaymentInfo(QJsonObject json) {
    QString stuNum = json["Student Number"].toString();

    QString testNum = "100853074";

    QueryControl *query = new QueryControl();
    PaymentInformation p;
    p = query->getExistingBillingInfo(testNum);  //100853074
    delete query;
    QJsonObject payment;
    QJsonDocument result;
    p.write(payment);
    result = QJsonDocument(payment);
    qDebug() << result.toJson();

}

QJsonObject APIControl::createTextbook(QJsonObject json) {

}


QJsonObject APIControl::viewShoppingCart(QJsonObject json, QMap<QString, ShoppingCart> testStudentShoppingCart) {
    QJsonObject result;
    QString stuNum = json["Student Number"].toString();
    ShoppingCart *cart;
       if(testStudentShoppingCart.contains(stuNum)) {
       *cart = testStudentShoppingCart.value(stuNum);
       }
    cart->write(result);
    return result;
}

//QJsonObject APIControl::cManagerViewTextbooks(QJsonObject json) {

//    Term term;
//    term.read(json["Term"].toObject());
//    QueryControl *query = new QueryControl();
//    //
//    delete query;
//    QJsonArray resultArray;
//    foreach(Course *crs, result){
//        QJsonObject json;
//        crs->write(json);
//        resultArray.append(json);
//    }

//    QJsonObject r;
//    r["courses:"] = resultArray;
//    qDebug() << r;
//    return r;

//}
