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
    /*
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
    */
}

void ShoppingCart::write(QJsonObject &json) const{

    /*
    QJsonArray itemArray;
    foreach(QPair<PurchasableItem*,qint32> item, items){
        QJsonObject pairObject;
        QJsonObject itemObject;

        itemObject["item"]
        item->write(itemObject);
        itemArray.append(itemObject);
    }
    json["items"] = itemArray;
    */

}
