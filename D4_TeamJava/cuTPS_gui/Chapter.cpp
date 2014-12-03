/*Chapter class source
 *
 *
 *
 *Traceability: EO-12
 *
 */

#include "Chapter.h"

//Constructor
Chapter::Chapter(QString chapTitle,qint32 chapNo,
                 qint32 id, float price, bool avail) :
                 PurchasableItem(id,price,avail),
                 title(chapTitle), chapterNumber(chapNo){}


//Destructor
Chapter::~Chapter(){
    QList<Section*>::iterator i;
    for (i = sections.begin(); i != sections.end(); i++) {
        delete *i;
    }
}



//GETTERS
QList<Section*>& Chapter::getChapterSections()        {return sections;}
qint32 Chapter::getChapterNumber()              const {return chapterNumber;}
QString Chapter::getItemTitle()                 const {return title;}

Section* Chapter::getSection(qint32 num){
    QList<Section*>::iterator i;
    for (i = sections.begin(); i != sections.end(); i++) {
        if ((*i)->getSectionNumber() == num)
            return *i;
    }
    return NULL;
}

//SETTERS
void Chapter::setItemTitle(QString a){title = a;}
void Chapter::setChapterNumber(qint32 a){chapterNumber = a;}

//Adds the argument Section* to the sections list
void Chapter::addSection(Section* section){
    sections.push_back(section);
}

bool Chapter::equals(Chapter* chapter){
    if( !(chapterNumber == chapter->getItemID()
        && title == chapter->getItemTitle()))
        return false;

    if(sections.size() != chapter->sections.size())
        return false;
    for(int i=0;i<sections.size();i++){
        if(!sections.at(i)->equals(chapter->getChapterSections().at(i)))
            return false;
    }
    return true;
}

//Takes a QJson object, this object extracts info about it
//And sets its attributes to this extracted info
void Chapter::read(const QJsonObject &json){
    PurchasableItem::read(json);
    sections.clear();
    title = json["title"].toString();
    chapterNumber = json["chapterNumber"].toDouble();

    QJsonArray sectionArray = json["sections"].toArray();
    for (int sectionIndex = 0; sectionIndex < sectionArray.size(); ++sectionIndex) {
           QJsonObject sectionObject = sectionArray[sectionIndex].toObject();
           Section* newSection = new Section();
           newSection->read(sectionObject);
           sections.append(newSection);
    }
}

//Writes to a QJsonobject this object's components
void Chapter::write(QJsonObject &json) const{
    PurchasableItem::write(json);
    QJsonArray sectionArray;
    json["title"] = title;
    json["chapterNumber"] = chapterNumber;
    foreach (const Section* section, sections) {
           QJsonObject sectionObject;
           section->write(sectionObject);
           sectionArray.append(sectionObject);
    }
    json["sections"] = sectionArray;
}

//PRINT
std::ostream& operator<< (std::ostream& o, Chapter & chapter)
{
    o << "Chapter " << chapter.getChapterNumber() << ": " + chapter.getItemTitle().toStdString() << endl;

    //sections

    QList<Section*>::iterator i;
    for (i = chapter.getChapterSections().begin(); i != chapter.getChapterSections().end(); i++) {
        o << "    " << **i << endl;
    }

    return o;
}
