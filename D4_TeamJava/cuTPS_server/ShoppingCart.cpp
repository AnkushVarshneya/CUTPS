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
QList< QPair<PurchasableItem*,qint32> >& ShoppingCart::getItems(){return items;}







//Empty shopping cart's contents
void ShoppingCart::emptyShoppingCart(){  
    items.clear();
}

//Read and write json concrete functions

void ShoppingCart::read(const QJsonObject &json){

    QJsonArray itemArray= json["items"].toArray();
    for(int i = 0; i<itemArray.size(); ++i){
        QJsonObject pairObject = itemArray[i].toObject();
        QJsonObject itemObject = pairObject["item"].toObject();
        QPair<PurchasableItem*,qint32> newPair;
        if(itemObject.contains("isbn")){
            Textbook* newTextbook = new Textbook();
            newTextbook->read(itemObject);
            newPair.first = newTextbook;
            newPair.second = pairObject["quantity"].toDouble();
            items.append(newPair);

        }
        else if (itemObject.contains("chapterNumber")){
            Chapter* newChapter = new Chapter();
            newChapter->read(itemObject);
            newPair.first = newChapter;
            newPair.second = pairObject["quantity"].toDouble();
            items.append(newPair);
        }
        else if(itemObject.contains("sectionNumber")){
            Section* newSection = new Section();
            newSection->read(itemObject);
            newPair.first = newSection;
            newPair.second = pairObject["quantity"].toDouble();
            items.append(newPair);
        }
    }
}

void ShoppingCart::write(QJsonObject &json) const{
    QJsonArray itemArray;
    for (int i = 0; i < items.size(); i++){
        QJsonObject pairObject;
        QJsonObject itemObject;
        items[i].first->write(itemObject);
        pairObject["item"] = itemObject;
        pairObject["quantity"] = items[i].second;
        itemArray.append(pairObject);
    }
    json["items"] = itemArray;
}
