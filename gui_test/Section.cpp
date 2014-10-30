
#include "Section.h"

Section::Section(QString t,qint32 n,
                 qint32 id, float pr, bool avail) :

                 PurchasableItem(id,pr,avail),

                 title(t), sectionNumber(n){}

Section::~Section(){}

//GETTERS
QString Section::getItemTitle(){return title;}
qint32 Section::getSectionNumber(){return sectionNumber;}

//SETTERS
void Section::setItemTitle(QString a){title = a;}
void Section::setSectionNumber(qint32 a){sectionNumber = a;}

//Takes input argument QJsonObject and extracts information
//About it to set this object's components
void Section::read(const QJsonObject &json){
    //TODO: Add read from a QJsonObject for a section here
}

//Writes this section object's components to a QJsonObject
void Section::write(QJsonObject &json) const{
    //TODO: Add write to a QJsonObject for a section object here
}

//PRINT
std::ostream& operator<<(std::ostream& o,  Section& section){
    return o << "Section " << section.getSectionNumber() << ": " << section.getItemTitle().toStdString();
}
