#ifndef TEXTBOOK_H
#define TEXTBOOK_H

#include <string>

class Textbook : public PurchasableItem{
public:
    Textbook();
private:
    string title;
    string author;
    string edition;
    string publisher;
    string isbn;
    string description;
    QList<Chapter> chapters;
    //cover image id?

};

#endif // TEXTBOOK_H
