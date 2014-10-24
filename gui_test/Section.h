#ifndef SECTION_H
#define SECTION_H

#include <string>

class Section : public PurchasableItem{
public:
    Section();
    string getSectionTitle();
    void setTitle(string);

private:
    string title;
};

#endif // SECTION_H
