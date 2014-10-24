#ifndef CHAPTER_H
#define CHAPTER_H

#include <string>

class Chapter : public PurchasableItem{
public:
    Chapter();
private:
    string title;
    QList<Section> sections;
};

#endif // CHAPTER_H
