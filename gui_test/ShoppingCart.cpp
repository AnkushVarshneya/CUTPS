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
QList<PurchasableItem*>& ShoppingCart::getItems(){return items;}
qint32 ShoppingCart::getShoppingCartID()const{return id;}

//Setters
void ShoppingCart::setShoppingCartID(qint32 i){id = i;}

//Append a PurchasableItem to the end of the items list
void ShoppingCart::addItem(PurchasableItem* item){
    items.push_back(item);
}


//Empty shopping cart's contents
void ShoppingCart::emptyShoppingCart(){  
     items.clear();
}
