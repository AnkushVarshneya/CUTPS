/*Chapter header class
 *last modified : 10/24/2014
 *
 *Chapter has a chapter title and a list of sections (through reference pointers)
 */
#ifndef CHAPTER_H
#define CHAPTER_H

#include <QString>
#include "Section.h"
#include <QVariant>

class Chapter : public PurchasableItem{
public:
    Chapter();
    ~Chapter();

    QString getChapterTitle();
    QList<Section*>& getChapterSections();
    QVariant getChapterNumber();
    Section* getSection(QVariant);
    QString getItemTitle();

    void setChapterTitle(QString);
    //void addSection(Section*);

private:
    QString title;
    QList<Section*> sections;
    QVariant chapterNumber;


};

#endif // CHAPTER_H
