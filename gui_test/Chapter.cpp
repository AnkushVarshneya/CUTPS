#include "Chapter.h"

Chapter::Chapter()
{

}

Chapter::~Chapter()
{

}

QString Chapter::getChapterTitle()
{
    return title;
}

QList<Section*>& Chapter::getChapterSections()
{
    return sections;
}

void Chapter::setChapterTitle(QString a)
{
    title = a;
}
