#ifndef SECTION_H
#define SECTION_H

#include <QString>

class Section : public PurchasableItem{
public:
    Section();
    QString getSectionTitle();
    void setTitle(QString);

private:
    QString title;
};

#endif // SECTION_H
