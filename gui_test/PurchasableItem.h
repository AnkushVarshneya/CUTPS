/*PurchasableItem class header
 *Date last modified: 28/10/2014
 *
 *Traceability: EO-10 of Entity Class DataDictionary in Deliverable 1
 *TODO: Must inherit QObject? Or create super super class CUTPSDataObject for serializing
 */

#ifndef PURCHASABLEITEM_H
#define PURCHASABLEITEM_H

#include <QList>
#include <QObject>
#include <QString>

class PurchasableItem{

public:
    PurchasableItem();
    PurchasableItem(QString, float, bool);
    ~PurchasableItem();

    QString             getItemID();
    float               getPrice();
    bool                isAvailable();
    void                setItemID(QString);
    void                setPrice(float);
    void                setAvailability(bool);
    virtual QString     getItemTitle() = 0;
    virtual void        setItemTitle(QString) = 0;

private:
    QString  itemID;
    float    price;
    bool     availability;
};

#endif // PURCHASABLEITEM_H
