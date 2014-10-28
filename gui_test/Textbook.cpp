#include "Textbook.h"





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

Chapter* Textbook::getChapter(QVariant num)
{
    return chapters.at(num.toInt());
}

QString Textbook::getItemTitle(){
    return getTextbookTitle();
}

void Textbook::addChapter(Chapter* chapter)
{

    chapters.insert(chapter->getChapterNumber().toInt(), chapter);
    //check this

}
