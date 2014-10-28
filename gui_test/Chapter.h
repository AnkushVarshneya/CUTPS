/*Chapter header class
 *last modified : 10/24/2014
 *
 *Chapter has a chapter title and a list of sections (through reference pointers)
 */
#ifndef CHAPTER_H
#define CHAPTER_H

#include <QString>
#include "Section.h"

class Chapter : public PurchasableItem{
public:
    Chapter();
    ~Chapter();

    QString getChapterTitle();
    QList<Section*>& getChapterSections();
    qint32 getChapterNumber();
    Section* getSection(qint32);
    QString getItemTitle();

    void setItemTitle(QString);
    void setChapterTitle(QString);
    //void addSection(Section*);

private:
    QString title;
    QList<Section*> sections;
    qint32 chapterNumber;


};

#endif // CHAPTER_H
