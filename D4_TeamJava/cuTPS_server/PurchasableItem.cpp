/*PurchasableItem source file
 *
 *
 *Traceability: EO-10 of Entity Class DataDictionary in Deliverable 1
 *
 */
#include "PurchasableItem.h"


//Constructor taking in a QString itemID, float-type for price, and boolean
//type for availability
PurchasableItem::PurchasableItem(qint32 iID, float p, bool a): itemID(iID), price(p), availability(a){}

//Destructor
PurchasableItem::~PurchasableItem(){}


//Getters
qint32 PurchasableItem::getItemID() const{return itemID;}
float PurchasableItem::getPrice(){return price;}
bool PurchasableItem::isAvailable(){return availability;}

//Setters
void PurchasableItem::setItemID(qint32 i){itemID = i;}
void PurchasableItem::setPrice(float p){price = p;}
void PurchasableItem::setAvailability(bool a){availability = a;}


//Checks to see if two purchasable items are equal by itemID
bool PurchasableItem::operator==(const PurchasableItem& item) const{return this->getItemID() == item.getItemID();}

//Read from JSON object for abstract class purchasable item
//Will be used by derived classes to get their itemID, price and, availability
void PurchasableItem::read(const QJsonObject &json){
    itemID = json["itemID"].toDouble();
    price = json["price"].toDouble();
    availability = json["availability"].isBool();
}

//Write to JSON object which will be used by derived classes to write
//Their itemID, price, and availability
void PurchasableItem::write(QJsonObject &json) const{
    json["itemID"] = itemID;
    json["price"] = price;
    json["availability"] = availability;
}
