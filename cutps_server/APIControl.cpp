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
    QList<Course*>& result = query->studentViewTextbooks(studentNumber, term.getTermID());
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

//API getExistingPaymentInfo() that takes in the json object,
//reads it, creates a query control to get existing payment information
//from the database, then returns a payment information object.
QJsonObject APIControl::getExistingPaymentInfo(QJsonObject json) {
    QString stuNum = json["Student Number"].toString();
    qDebug() << "testing billing info on student num: " << stuNum << "\n";


    QueryControl *query = new QueryControl();
    PaymentInformation *p;
    qDebug() << "Test break 1";
    p = query->getExistingBillingInfo(stuNum);
    qDebug() << "Test break 2";
    delete query;
    QJsonObject payment;
    if(p != NULL){
        p->write(payment);
    }
    else{
        qDebug() << "No payment info found";
    }
    return payment;


}


//Takes in the passed in Json argument and parses it
//Queries the database to insert into the table of textbooks
//Returns a JSON object containing a boolean dependent on
//Whether or not the insert was successful
QJsonObject APIControl::createTextbook(QJsonObject json) {
    Textbook* argText = new Textbook();
    argText->read(json["Textbook"].toObject());
    QueryControl *query = new QueryControl();
    bool result  = query->createTextbook(argText);
    delete argText;
    QJsonObject r;
    r["Boolean:"] = result;
    return r;
}


//Gets the passed in client's argument for student number
//And returns the cart contents as a JSON object
QJsonObject APIControl::viewShoppingCart(QJsonObject json, QMap<QString, ShoppingCart> testStudentShoppingCart) {
    QJsonObject result;
    QString stuNum = json["Student Number"].toString();
    ShoppingCart cart;
       if(testStudentShoppingCart.contains(stuNum)) {
       cart = testStudentShoppingCart.value(stuNum);
       }
    cart.write(result);
    return result;
}

/*Nonfunctional
QJsonObject APIControl::addContent(QJsonObject json, QMap<QString, ShoppingCart> testStudentShoppingCart){
    QJsonObject result;
    QString stuNum = json["Student Number"].toString();
    qint32 itemID = json["Item ID"].toDouble();
    qint32 quantity = json["Quantity"].toDouble();
    QueryControl query = new QueryControl();
    QList<
}
*/

//Gets the JSON object argument's student number field value
//And empties the shopping cart based on the key of the shopping cart map
QJsonObject APIControl::emptyShoppingCart(QJsonObject json, QMap<QString,ShoppingCart> testStudentShoppingCart ){
    QJsonObject result;
    QString stuNum = json["Student Number"].toString();
    ShoppingCart cart;
    if(testStudentShoppingCart.contains(stuNum)) {
        testStudentShoppingCart.insert(stuNum, cart);
        result["Boolean:"] = true;
    }
    else{
        result["Boolean:"] = false;
    }
    return result;
}


//Takes the Student Number and Payment Info fields and turns them into
//arguments to pass as a query to the database.
QJsonObject APIControl::savePaymentInfo(QJsonObject json){

    QString stuNum = json["Student Number"].toString();
    PaymentInformation *paymentInfo = new PaymentInformation;
    paymentInfo->read(json["Payment Info"].toObject());
    QueryControl *query = new QueryControl();
    bool result  = query->saveBillingInformation(stuNum,paymentInfo);
    QJsonObject r;
    r["Boolean:"] = result;
    return r;
}

//Takes the Course and TermID arguments and passes them into
//Querying the database
QJsonObject APIControl::createCourse(QJsonObject json){
    Course* argCourse = new Course();
    argCourse->read(json["Course"].toObject());
    qint32 termID = json["TermID"].toDouble();
    QueryControl *query = new QueryControl();
    bool result  = query->createCourse(argCourse,termID);
    delete argCourse;
    QJsonObject r;
    r["Boolean:"] = result;
    return r;
}

//Gets the Term argument by the passed in json object and
//Queries the database gettinga  list of all textbooks in that term
QJsonObject APIControl::cManagerViewTextbooks(QJsonObject json) {

    Term* term = new Term();
    term->read(json["Term"].toObject());

    QueryControl *query = new QueryControl();
    QList<Textbook*> result  = query->viewAllTextbooks(term->getTermID());
    delete term;
    delete query;
    QJsonArray resultArray;
    foreach(Textbook *txt, result){
        QJsonObject json;
        txt->write(json);
        resultArray.append(json);
    }

    QJsonObject r;
    r["textbooks:"] = resultArray;
    qDebug() << r;
    return r;

}

//Gets the Term argument by the passed in json object and
//Queries the database gettinga  list of all courses in that term
QJsonObject APIControl::cManagerViewCourses(QJsonObject json){
    Term* term = new Term();
    term->read(json["Term"].toObject());

    QueryControl *query = new QueryControl();
    QList<Course*> result  = query->viewCourses(term->getTermID());
    delete term;
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

//Takes the textbook and course arguments and queries the database to
//Assign a textbook to a course
QJsonObject APIControl::linkTextbook(QJsonObject json){
    Textbook* linkText = new Textbook();
    Course* linkCourse = new Course();
    qint32 termID = json["termID"].toDouble();
    linkText->read(json["Textbook"].toObject());
    linkCourse->read(json["Course"].toObject());
    QueryControl *query = new QueryControl();
    bool result = query->linkTextbook(linkText,linkCourse,termID);
    delete query, linkText, linkCourse;
    QJsonObject r;
    r["Boolean:"] = result;
    return r;
}
