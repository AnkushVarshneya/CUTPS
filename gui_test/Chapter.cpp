#include "Chapter.h"

//Constructor
Chapter::Chapter(QString t,qint32 n,
                 qint32 id, float pr, bool avail) :
                 PurchasableItem(id,pr,avail),
                 title(t), chapterNumber(n){}


//Destructor
Chapter::~Chapter(){
    QList<Section*>::iterator i;
    for (i = sections.begin(); i != sections.end(); i++) {
        free(*i);
    }

}


/**************/


//GETTERS
QList<Section*>& Chapter::getChapterSections(){return sections;}
qint32 Chapter::getChapterNumber(){return chapterNumber;}
QString Chapter::getItemTitle(){return title;}


//SETTERS
void Chapter::setItemTitle(QString a){title = a;}
void Chapter::setChapterNumber(qint32 a){chapterNumber = a;}

void Chapter::addSection(Section* section){
    //sections.insert(section->getSectionNumber() - 1, section);
    sections.push_back(section);
    //check this
}

//Takes a QJson object, this object extracts info about it
//And sets its attributes to this extracted info
void Chapter::read(const QJsonObject &json){
    //TODO: Add read from a QJsonObject for Chapter here
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
    //TODO: Add write to a QJson object for a chapter here
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
