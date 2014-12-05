#include "ShoppingCart.h"
#include <iostream>
#include "Textbook.h"
#include "Chapter.h"
#include "Section.h"



//Constructor
ShoppingCart::ShoppingCart(){}

//Destructor
ShoppingCart::~ShoppingCart(){emptyShoppingCart();}

//Getters
QMap<PurchasableItem*,qint32>& ShoppingCart::getItems(){return items;}
qint32 ShoppingCart::getShoppingCartID()const{return id;}






//Empty shopping cart's contents
void ShoppingCart::emptyShoppingCart(){  
    qDeleteAll(items.begin(), items.end());
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
