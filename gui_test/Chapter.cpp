#include "Chapter.h"

Chapter::Chapter(){}

//maybe delete later
QString Chapter::getChapterTitle()
{
    return title;
}

QList<Section*>& Chapter::getChapterSections()
{
    return sections;
}

qint32 Chapter::getChapterNumber()
{
    return chapterNumber;
}

//Section* Chapter::getSection(qint32 )

QString Chapter::getItemTitle(){
    return getChapterTitle();
}

void Chapter::setItemTitle(QString a){
    setChapterTitle(a);
}

void Chapter::setChapterTitle(QString a)
{
    title = a;
}
