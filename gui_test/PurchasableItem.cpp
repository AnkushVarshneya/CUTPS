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
PurchasableItem::PurchasableItem(QString iID, float price, bool available){

}

//Destructor
PurchasableItem::~PurchasableItem(){

}

//Get the itemID of this object returning as a QString type
QString PurchasableItem::getItemID(){
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
void PurchasableItem::setItemID(QString i){
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
