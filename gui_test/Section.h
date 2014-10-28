/*Section header class
 *Date last modified: 24/10/2014
 */
#ifndef SECTION_H
#define SECTION_H

#include <QString>
#include "PurchasableItem.h"

class Section : public PurchasableItem{
public:
    Section();
    Section(QString);
    ~Section();

    QString     getSectionTitle();
    void        setTitle(QString);

private:
    QString     title;
};

#endif // SECTION_H
