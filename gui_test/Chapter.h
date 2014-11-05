/*Chapter class header
 *
 *Inherits from PurchasableItem class
 *
 *Purpose of class: A chapter is a purchasable item that is part of some textbook.
 *Chapters can also be sub-divided into chapter sections (see Section header class)
 *
 *Data members:
 *title (the chapter title)
 *sections(A List of chapter sections)
 *chapterNumber (the chapter number of the chapter)
 *
 *Member functions:
 *getChapterSections() <- Returns the chapter's sections as a QList address
 *getChapterNumber() <- Gets the chapter's chapter number as a 32-bit integer
 *getSection(qint32) <- gets the section for the specified section number argument
 *getItemTitle() <- inherited from PurchasableItem, a concrete definition for getting the chapter's title
 *setItemTitle(QString) <- inherited from PurchasableItem, a concrete definition for setting the chapter's title
 *read(&json) <- reads from a QJsonObject and sets the data members as the values of the corresponding fields
 *write(&json) <- write the data members as values to a json object
 *operator<< <- an overloaded operator for printing out the chapter's attributes to std output
 *
 *
 *
 *
 *Traceability: EO-12
 */
#ifndef CHAPTER_H
#define CHAPTER_H

#include <QString>
#include "Section.h"
using namespace std;

class Chapter : public PurchasableItem{
public:

    Chapter(QString = "A chapter title",qint32 = 1,
            qint32 = 42, float = 15.0, bool = false);

    ~Chapter();

    QList<Section*>&    getChapterSections();
    qint32              getChapterNumber() const;
    Section*            getSection(qint32);
    QString             getItemTitle() const;
    bool                equals(Chapter*);

    void                setItemTitle(QString);
    void                setChapterNumber(qint32);
    void                addSection(Section*);
    void                read(const QJsonObject &json);
    void                write(QJsonObject &json) const;


private:
    QString             title;
    QList<Section*>     sections;
    qint32              chapterNumber;


};

std::ostream& operator<<(std::ostream&,  Chapter&);

#endif // CHAPTER_H
