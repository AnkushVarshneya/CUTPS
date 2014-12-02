/*Textbook header file
 *
 *Purpose: A textbook is the academic text that is used in courses. In CUTPS,
 *it will be a purchasable item as a whole if it is linked to any course in CUTPS
 *Textbooks can be subdivided into chapters which will also be purchasasble in CUTPS given
 *That it is made available by the Content Manager
 *
 *Traceability: EO-11
 *
 */
#ifndef TEXTBOOK_H
#define TEXTBOOK_H

#include <QStringList>
#include <QStringListModel>
#include <QString>
#include "Chapter.h"
using namespace std;

class Textbook : public PurchasableItem{
public:

    Textbook(QString = "Generic Title", QString = "Generic Author", QString = "1st ed",
             QString = "A Publisher" ,QString = "978-3-16-148410-0" ,QString = "A generic description",
             qint32 = 555, float = 80.50 , bool = false  );
    ~Textbook();
    QString             getAuthor           () const;
    QString             getEdition          () const;
    QString             getPublisher        () const;
    QString             getISBN             () const;
    QString             getDesc             () const;
    QList<Chapter*>&    getChapterList      ();
    Chapter*            getChapter          (qint32);
    QString             getItemTitle        () const;
    QString             getCoverImageLoc    () const;

    //NEW!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    QStringList         getTextbookStringList() const;
    //END NEW

    void                setItemTitle    (QString);
    void                setAuthor       (QString);
    void                setPublisher    (QString);
    void                setEdition      (QString);
    void                setISBN         (QString);
    void                setDescription  (QString);
    void                setCoverImageLoc(QString);
    void                addChapter      (Chapter*);
    bool                equals          (Textbook*);

    void                read(const QJsonObject &json);
    void                write(QJsonObject &json) const;



private:
    QString             title;
    QString             author;
    QString             edition;
    QString             publisher;
    QString             isbn;
    QString             description;
    QList<Chapter*>     chapters;
    QString             coverImageLoc;
};

std::ostream& operator<<(std::ostream&,  Textbook&);

#endif // TEXTBOOK_H
