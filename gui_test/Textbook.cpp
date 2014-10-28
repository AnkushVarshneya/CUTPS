#include "Textbook.h"

Textbook::Textbook()
{

}

Textbook::~Textbook()
{

}

QString Textbook::getTitle()
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
