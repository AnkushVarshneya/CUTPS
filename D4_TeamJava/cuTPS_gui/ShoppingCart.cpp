#include "ShoppingCart.h"
#include <iostream>
#include "Textbook.h"
#include "Chapter.h"
#include "Section.h"

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

//Read and write json concrete functions

void ShoppingCart::read(const QJsonObject &json){
    id = json["id"].toDouble();

    QJsonArray itemArray= json["items"].toArray();
    for(int i = 0; i < itemArray.size(); ++i){
        QJsonObject itemObject = itemArray[i].toObject();
        if(itemObject.contains("isbn")){
            Textbook* newTextbook = new Textbook();
            newTextbook->read(itemObject);
            items.append(newTextbook);
        }
        else if(itemObject.contains("chapterNumber")){
            Chapter* newChapter = new Chapter();
            newChapter->read(itemObject);
            items.append(newChapter);
        }
        else if(itemObject.contains("sectionNumber")){
            Section* newSection = new Section();
            newSection->read(itemObject);
            items.append(newSection);
        }
    }
}

void ShoppingCart::write(QJsonObject &json) const{
    json["id"] = id;

    QJsonArray itemArray;
    foreach(PurchasableItem* item, items){
        QJsonObject itemObject;
        item->write(itemObject);
        itemArray.append(itemObject);
    }
    json["items"] = itemArray;
}
