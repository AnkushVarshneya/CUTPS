#ifndef PURCHASABLEITEM_H
#define PURCHASABLEITEM_H

#include <string>
#include <QList>

class PurchasableItem{
public:
    PurchasableItem();
private:
    string itemID;
    int price;
    bool availability;
};

#endif // PURCHASABLEITEM_H
