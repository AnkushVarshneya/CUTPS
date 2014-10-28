#include "Chapter.h"


//maybe delete later
QString Chapter::getChapterTitle()
{
    return title;
}

QList<Section*>& Chapter::getChapterSections()
{
    return sections;
}

QVariant Chapter::getChapterNumber()
{
    return chapterNumber;
}

//Section* Chapter::getSection(QVariant )

QString Chapter::getItemTitle(){
    return getChapterTitle();
}

void Chapter::setChapterTitle(QString a)
{
    title = a;
}
