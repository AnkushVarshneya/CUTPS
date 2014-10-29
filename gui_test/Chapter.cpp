#include "Chapter.h"

//Constructor
Chapter::Chapter(QString t,qint32 n,
                 QString id, float pr, bool avail) :

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
