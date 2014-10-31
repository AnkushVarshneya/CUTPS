/*Textbook header file
 *Date last modified: 10/29/2014
 * TODO: Add getters and setters for coverImageLoc
 *
 */
#ifndef TEXTBOOK_H
#define TEXTBOOK_H

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

    void                setItemTitle    (QString);
    void                setAuthor       (QString);
    void                setPublisher    (QString);
    void                setEdition      (QString);
    void                setISBN         (QString);
    void                setDescription  (QString);
    void                setCoverImageLoc(QString);
    void                addChapter(Chapter*);

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
