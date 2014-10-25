#ifndef PURCHASABLEITEM_H
#define PURCHASABLEITEM_H

#include <QString>
#include <QList>

class PurchasableItem{

public:
    PurchasableItem();
private:
    QString itemID;
    int price;
    bool availability;
};

#endif // PURCHASABLEITEM_H
