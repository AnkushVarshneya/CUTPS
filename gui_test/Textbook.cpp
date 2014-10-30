#include "Textbook.h"


Textbook::Textbook(QString t, QString a, QString e,
                   QString p, QString i, QString d,
                   qint32 id, float pr, bool avail) :

                   PurchasableItem(id,pr,avail),

                   title(t), author(a), edition(e),
                   publisher(p), isbn(i), description(d){}

//Textbook::Textbook(QString a, float b, bool c){}
Textbook::~Textbook(){

    QList<Chapter*>::iterator i;
    for (i = chapters.begin(); i != chapters.end(); i++) {
        free(*i);
    }

}


QString          Textbook::getAuthor()           {return author;}
QString          Textbook::getEdition()          {return edition;}
QString          Textbook::getPublisher()        {return publisher;}
QString          Textbook::getISBN()             {return isbn;}
QString          Textbook::getDesc()             {return description;}
QList<Chapter*>& Textbook::getChapterList()      {return chapters;}
QString          Textbook::getItemTitle()        {return title;}
QString          Textbook::getCoverImageLoc()    {return coverImageLoc;}

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


void Textbook::addChapter(Chapter* chapter){
    //chapters.insert(chapter->getChapterNumber() - 1, chapter);
    chapters.push_back(chapter);
    //check this
}

//Takes a QJsonobject, extracts information about it
//And set this textbook's attributes to it
void Textbook::read(const QJsonObject &json){
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
