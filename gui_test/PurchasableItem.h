/*PurchasableItem class header
 *Date last modified: 24/10/2014
 *
 *TODO: Must inherit QObject? Or create super super class CUTPSDataObject for serializing
 */

#ifndef PURCHASABLEITEM_H
#define PURCHASABLEITEM_H

#include <QList>
#include <QObject>

class PurchasableItem{

public:
    PurchasableItem();
    ~PurchasableItem();

    float    getPrice();
    bool     isAvailable();
    void     setPrice(float);
    void     setAvailability(bool);

private:
    float    price;
    bool     availability;
};

#endif // PURCHASABLEITEM_H
