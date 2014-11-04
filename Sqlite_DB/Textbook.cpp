#include "Textbook.h"


//Constructor
Textbook::Textbook(QString textTitle, QString auth, QString ed,
                   QString pub, QString ISBN, QString desc,
                   qint32 id, float price, bool avail) :
                   PurchasableItem(id,price,avail),
                   title(textTitle), author(auth), edition(ed),
                   publisher(pub), isbn(ISBN), description(desc){}

//Destructor that also destroys the chapters it has
Textbook::~Textbook(){
    QList<Chapter*>::iterator i;
    for (i = chapters.begin(); i != chapters.end(); i++) {
        delete *i;
    }
}


QString          Textbook::getAuthor()          const        {return author;}
QString          Textbook::getEdition()         const        {return edition;}
QString          Textbook::getPublisher()       const        {return publisher;}
QString          Textbook::getISBN()            const        {return isbn;}
QString          Textbook::getDesc()            const        {return description;}
QList<Chapter*>& Textbook::getChapterList()                  {return chapters;}
QString          Textbook::getItemTitle()       const        {return title;}
QString          Textbook::getCoverImageLoc()   const        {return coverImageLoc;}

Chapter* Textbook::getChapter(qint32 num){
    QList<Chapter*>::iterator i;
    for (i = chapters.begin(); i != chapters.end(); i++) {
        if ((*i)->getChapterNumber() == num)
            return *i;
    }
    return NULL;
}


std::ostream& operator<< (std::ostream& o, Textbook & textbook){
    o << "Title: " + textbook.getItemTitle().toStdString() << endl
             << "Author: " + textbook.getAuthor().toStdString() << endl
             << "Edition: " + textbook.getEdition().toStdString() << endl
             << "Publisher: " + textbook.getPublisher().toStdString() << endl
             << "ISBN: " + textbook.getISBN().toStdString() << endl
             << "Description: " + textbook.getDesc().toStdString() << endl
             << "Chapter List: " << endl;
    //chapters
    QList<Chapter*>::iterator i;
    for (i = textbook.getChapterList().begin(); i != textbook.getChapterList().end(); i++) {
        //if (**i != NULL)
            o << "  " << **i /*<< endl*/;
    }
    return o;
}

//SETTERS

void Textbook::setItemTitle(QString a){title = a;}
void Textbook::setAuthor(QString a){author = a;}
void Textbook::setPublisher(QString a){publisher = a;}
void Textbook::setEdition(QString a){edition = a;}
void Textbook::setISBN(QString a){isbn = a;}
void Textbook::setDescription(QString a){description = a;}
void Textbook::setCoverImageLoc(QString a){coverImageLoc = a;}

void Textbook::addChapter(Chapter* chapter){
    //chapters.insert(chapter->getChapterNumber() - 1, chapter);
    chapters.push_back(chapter);
    //check this
}

//Takes a QJsonobject, extracts information about it
//And set this textbook's attributes to it
void Textbook::read(const QJsonObject &json){
    PurchasableItem::read(json);
    title = json["title"].toString();
    author = json["author"].toString();
    edition = json["edition"].toString();
    publisher = json["publisher"].toString();
    isbn = json["isbn"].toString();
    description = json["description"].toString();

    //TODO: Potential memory leak here:
    chapters.clear();
    QJsonArray chapterArray = json["chapters"].toArray();
    for(int chapterIndex = 0; chapterIndex < chapterArray.size(); ++chapterIndex){
        QJsonObject chapterObject = chapterArray[chapterIndex].toObject();
        Chapter* newChapter = new Chapter();
        newChapter->read(chapterObject);
        chapters.append(newChapter);
    }
    coverImageLoc = json["coverImageLoc"].toString();
}

//Writes to a QJsonobject this object's components
void Textbook::write(QJsonObject &json) const{
    PurchasableItem::write(json);
    json["title"] = title;
    json["author"] = author;
    json["edition"] = edition;
    json["publisher"] = publisher;
    json["isbn"] = isbn;
    json["description"] = description;

    QJsonArray chapterArray;
    foreach (const Chapter* chapter, chapters){
        QJsonObject chapterObject;
        chapter->write(chapterObject);
        chapterArray.append(chapterObject);
    }
    json["chapters"] = chapterArray;

}
