#include "Textbook.h"

Textbook::Textbook(){}

Textbook::~Textbook(){}


QString Textbook::getTextbookTitle()
{
    return title;
}

QString Textbook::getAuthor()
{
    return author;
}

QString Textbook::getEdition()
{
    return edition;
}

QString Textbook::getPublisher()
{
    return publisher;
}

QString Textbook::getISBN()
{
    return isbn;
}

QString Textbook::getDesc()
{
    return description;
}

QList<Chapter*>& Textbook::getChapterList()
{
    return chapters;
}

Chapter* Textbook::getChapter(qint32 num)
{
    return chapters.at(num);
}

QString Textbook::getItemTitle(){
    return getTextbookTitle();
}

void Textbook::setItemTitle(QString a){
    setTextbookTitle(a);
}

void Textbook::setTextbookTitle(QString a){
    title = a;
}

void Textbook::addChapter(Chapter* chapter)
{

    chapters.insert(chapter->getChapterNumber(), chapter);
    //check this

}
