#ifndef TEXTBOOK_H
#define TEXTBOOK_H

#include <QString>

class Textbook : public PurchasableItem{
public:
    Textbook();
private:
    QString title;
    QString author;
    QString edition;
    QString publisher;
    QString isbn;
    QString description;
    QList<Chapter> chapters;
    //cover image id?

};

#endif // TEXTBOOK_H
