#include "ShoppingCart.h"
#include <iostream>
using namespace std;

//Constructor
ShoppingCart::ShoppingCart(qint32 i): id(i){cout<< "In Shopping cart constructor" <<endl;}

//Destructor
ShoppingCart::~ShoppingCart(){
    emptyShoppingCart();
    cout << "In Shopping cart destructor" <<endl;
}

//Getters
QMap<PurchasableItem*,qint32>& ShoppingCart::getItems(){return items;}
qint32 ShoppingCart::getShoppingCartID()const{return id;}

//Setters
void ShoppingCart::setShoppingCartID(qint32 i){id = i;}

//Append a PurchasableItem to the end of the items list
//TODO: Need to implement this properly
void ShoppingCart::addItem(PurchasableItem* item){

}

//TODO need to implement this properly
void ShoppingCart::addItemQuantity(PurchasableItem*,int){

}

//Empty shopping cart's contents
void ShoppingCart::emptyShoppingCart(){  
     items.clear();
}
