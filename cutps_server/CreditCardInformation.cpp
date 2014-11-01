
#include "CreditCardInformation.h"
#include <iostream>
using namespace std;

CreditCardInformation::CreditCardInformation(QString ccNo, QString cvv, QDate date, QString cType, QString name)
    : creditCardNo(ccNo), CVV(cvv), expDate(date), cardType(cType), nameOnCard(name){}

//CreditCardInformation::~CreditCardInformation(){ cout<< "In CreditCardInformation destructor"<<endl;}


//Getters
QString CreditCardInformation::getCreditCardNo(){return creditCardNo;}
QString CreditCardInformation::getCVV(){return CVV;}
QDate CreditCardInformation::getExpDate(){return expDate;}
QString CreditCardInformation::getCardType(){return cardType;}
QString CreditCardInformation::getNameOnCard(){return nameOnCard;}

//Setters
void CreditCardInformation::setCreditCardNo(QString n){creditCardNo = n;}
void CreditCardInformation::setCVV(QString c){CVV = c;}
void CreditCardInformation::setExpDate(int year,int month,int day){expDate.setDate(year,month,day);}
void CreditCardInformation::setCardType(QString type){cardType = type;}
void CreditCardInformation::setNameOnCard(QString name){nameOnCard = name;}

//JSON reader
void CreditCardInformation::read(const QJsonObject &json){
    creditCardNo = json["creditCardNo"].toString();
    CVV = json["CVV"].toString();
    expDate = QDate::fromString(json["expDate"].toString(), "yyyyMMdd");
    cardType = json["cardType"].toString();
    nameOnCard = json["nameOnCard"].toString();

}

//JSON writer
void CreditCardInformation::write(QJsonObject &json)const{
    json["creditCardNo"] = creditCardNo;
    json["CVV"] = CVV;
    json["expDate"] = expDate.toString("yyyyMMdd");
    json["cardType"] = cardType;
    json["nameOnCard"] = nameOnCard;

}


//ostream method for testing data purposes
//std::ostream& operator<<(std::ostream& o, CreditCardInformation& ccInfo){
//    o << "Credit Card Number: " + ccInfo.getCreditCardNo().toStdString() << endl
//      << "CVV: " + ccInfo.getCVV().toStdString() << endl
//      << "ExpDate: " + ccInfo.getExpDate().toString().toStdString() << endl
//      << "Card Type: " + ccInfo.getCardType().toStdString() << endl
//      << "Name On Card: " + ccInfo.getNameOnCard().toStdString() << endl;
//    return o;
//}
