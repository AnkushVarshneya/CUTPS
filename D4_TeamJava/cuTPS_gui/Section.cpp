#include "Section.h"
#include <iostream>
using namespace std;

//Constructor that takes in a string for section title:
//Integer for section number, Integer for its itemID,
//Float for price, and Boolean for availability
Section::Section(QString secTitle,qint32 secNo,
                 qint32 id, float price, bool avail) :
                 PurchasableItem(id,price,avail),
                 title(secTitle), sectionNumber(secNo){}

Section::~Section(){cout<<"in section destructor"<<endl;}

//GETTERS
QString Section::getItemTitle() const   {return title;}
qint32 Section::getSectionNumber()      {return sectionNumber;}

//SETTERS
void Section::setItemTitle(QString a){title = a;}
void Section::setSectionNumber(qint32 a){sectionNumber = a;}

bool Section::equals(Section* section){
    if(!(title == section->getItemTitle()
         && sectionNumber == section->getItemID()))
        return false;
    return true;
}

//Takes input argument QJsonObject and extracts information
//About it to set this object's components
void Section::read(const QJsonObject &json){
    PurchasableItem::read(json);
    title = json["title"].toString();
    sectionNumber = json["sectionNumber"].toDouble();
}

//Writes this section object's components to a QJsonObject
void Section::write(QJsonObject &json) const{
    PurchasableItem::write(json);
    json["title"] = title;
    json["sectionNumber"] = sectionNumber;
}

//PRINT
std::ostream& operator<<(std::ostream& o,  Section& section){
    return o << "Section " << section.getSectionNumber() << ": " << section.getItemTitle().toStdString();
}
