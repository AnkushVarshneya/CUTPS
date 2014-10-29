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

    Textbook(QString = "", QString = "", QString = "",
             QString = "" ,QString = "" ,QString = "",
             QString = "", float = 0 , bool = false  );
    ~Textbook();
    QString             getAuthor           ();
    QString             getEdition          ();
    QString             getPublisher        ();
    QString             getISBN             ();
    QString             getDesc             ();
    QList<Chapter*>&    getChapterList      ();
    Chapter*            getChapter          (qint32);
    QString             getItemTitle        ();


    void                setItemTitle    (QString);
    void                setAuthor       (QString);
    void                setPublisher    (QString);
    void                setEdition      (QString);
    void                setISBN         (QString);
    void                setDescription  (QString);

    void                addChapter(Chapter*);


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
