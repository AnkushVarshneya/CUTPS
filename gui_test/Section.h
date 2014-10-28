/*Section header class
 *Date last modified: 24/10/2014
 */
#ifndef SECTION_H
#define SECTION_H

#include <QString>
#include <QVariant>
#include "PurchasableItem.h"

class Section : public PurchasableItem{
public:
    Section();
    ~Section();

    QString     getSectionTitle();
    QString     getItemTitle();

    void        setTitle(QString);

private:
    QString     title;
    QVariant    sectionNumber;
};

#endif // SECTION_H
