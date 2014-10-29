
#include "CreditCardInformation.h"


CreditCardInformation::CreditCardInformation(QString ccNo, QString cvv, QString cType, QString name)
    : creditCardNo(ccNo), CVV(cvv), expDate(QDate()), cardType(cType), nameOnCard(name){}

CreditCardInformation::~CreditCardInformation(){ cout<< "In CreditCardInformation destructor"<<endl;}


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

}

//JSON writer
void CreditCardInformation::write(QJsonObject &json)const{

}


//ostream method for testing data purposes
std::ostream& operator<<(std::ostream& o, CreditCardInformation& ccInfo){
  /*  o << "Credit Card Number: " + ccInfo.getCreditCardNo.toStdString() << endl
         <<*/
}
