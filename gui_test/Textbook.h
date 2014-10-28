/*Textbook header file
 *Date last modified: 10/24/2014
 *
 *
 */
#ifndef TEXTBOOK_H
#define TEXTBOOK_H

#include <QString>
#include "Chapter.h"

class Textbook : public PurchasableItem{
public:

    Textbook();
    ~Textbook();
    QString             getTitle();
    QString             getAuthor();
    QString             getEdition();
    QString             getPublisher();
    QString             getISBN();
    QString             getDesc();
    QList<Chapter*>&    getChapterList();


private:
    QString             title;
    QString             author;
    QString             edition;
    QString             publisher;
    QString             isbn;
    QString             description;
    QList<Chapter*>     chapters;
    //cover image id?

};

#endif // TEXTBOOK_H
