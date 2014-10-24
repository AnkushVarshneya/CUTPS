/*Chapter header class
 *last modified : 10/24/2014
 *
 *Chapter has a chapter title and a list of sections (through reference pointers)
 */
#ifndef CHAPTER_H
#define CHAPTER_H

#include <string>

class Chapter : public PurchasableItem{
public:
    Chapter();
    ~Chapter();

    string getChapterTitle();
    QList<Section*>& getChapterSections();

    void setChapterTitle(string);

private:
    string title;
    QList<Section*> sections;


};

#endif // CHAPTER_H
