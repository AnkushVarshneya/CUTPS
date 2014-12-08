#ifndef OURSTANDARDITEM_H
#define OURSTANDARDITEM_H

#include <QStandardItem>
#include "PurchasableItem.h"
#include "Textbook.h"
#include "Chapter.h"
#include "Section.h"
#include "Course.h"
#include <QDebug>

class OurStandardItem : public QStandardItem
{
    //Q_OBJECT
public:
    //explicit OurStandardItem(QObject *parent = 0);
    explicit OurStandardItem(PurchasableItem *item);
    explicit OurStandardItem(Textbook *textbook, bool makeItemsForChildren = true);
    explicit OurStandardItem(Course *course);
    OurStandardItem(PurchasableItem *item, qint32 quantity);
    OurStandardItem(Textbook *textbook, Course *course, bool makeItemsForChildren);
    OurStandardItem(Chapter *chapter, OurStandardItem *parent);
    OurStandardItem(Section *section, OurStandardItem *parent);


signals:

public slots:

};

#endif // OURSTANDARDITEM_H
