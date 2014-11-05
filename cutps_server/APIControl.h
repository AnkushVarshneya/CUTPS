#ifndef APICONTROL_H
#define APICONTROL_H
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Term.h"
#include "BillingAddress.h"
#include "Chapter.h"
#include "Course.h"
#include "CUtpsDataObject.h"
#include "PaymentInformation.h"
#include "PurchasableItem.h"
#include "Section.h"
#include "ShoppingCart.h"
#include "Student.h"
#include "Textbook.h"
#include "User.h"
#include <QtSql>


class APIControl
{
public:
    APIControl();
    QJsonObject studentViewTextbooks(QJsonObject json);

    QJsonObject viewShoppingCart(QJsonObject json, QMap<QString, ShoppingCart> testStudentShoppingCart);
//    QJsonObject addContent(QJsonObject json);
//    QJsonObject emptyShoppingCart(QJsonObject json);
    QJsonObject getExistingPaymentInfo(QJsonObject json);
//    QJsonObject savePaymentInfo(QJsonObject json);

    QJsonObject createTextbook(QJsonObject json);
//    QJsonObject createCourse(QJsonObject json);
//    QJsonObject linkTextbook(QJsonObject json);
//    QJsonObject cManagerViewTextbooks(QJsonObject json);
//    QJsonObject cManagerViewCourses(QJsonObject json);


};

#endif // APICONTROL_H
