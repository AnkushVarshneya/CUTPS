/*PurchasableItem source file
 *
 *Contains implementations of functions:
 *- PurchasableItem(QString, float, bool) <--- Constructor
 *- ~PurchasableItem() <--- Destructor
 *- getPrice()
 *- isAvailable()
 *- setPrice(float)
 *- setAvailability(bool)
 *
 *Traceability: EO-10 of Entity Class DataDictionary in Deliverable 1
 *
 */
#include "PurchasableItem.h"


//Constructor taking in a QString itemID, float-type for price, and boolean
//type for availability
PurchasableItem::PurchasableItem(qint32 iID, float p, bool a): itemID(iID), price(p), availability(a){}

//Destructor
PurchasableItem::~PurchasableItem(){

}

//Get the itemID of this object returning as a qint32 type
qint32 PurchasableItem::getItemID() const{
    return itemID;
}

//Get the price of this object returning as a float type
float PurchasableItem::getPrice(){
    return price;
}

//Get the availability of this object returning bool type
bool PurchasableItem::isAvailable(){
    return availability;
}

//Input a QString argument, and set this object's itemID to the argument
void PurchasableItem::setItemID(qint32 i){
    itemID = i;
}

//Input a float argument, and set this object's price to the argument
void PurchasableItem::setPrice(float p){
    price = p;
}

//Input a bool argument, and set this object's availability to this argument
void PurchasableItem::setAvailability(bool a){
    availability = a;
}


//Checks to see if two purchasable items are equal by itemID
bool PurchasableItem::operator==(const PurchasableItem& item) const{
    return this->getItemID() == item.getItemID();
}

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
