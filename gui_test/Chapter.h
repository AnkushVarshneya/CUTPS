/*Chapter header class
 *last modified : 10/24/2014
 *
 *Chapter has a chapter title and a list of sections (through reference pointers)
 */
#ifndef CHAPTER_H
#define CHAPTER_H

#include <QString>
#include "Section.h"
using namespace std;

class Chapter : public PurchasableItem{
public:

    Chapter(QString = "",qint32 = 0,
            qint32 = 0, float = 0, bool = false);

    ~Chapter();

    QList<Section*>&    getChapterSections();
    qint32              getChapterNumber();
    Section*            getSection(qint32);
    QString             getItemTitle();

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
