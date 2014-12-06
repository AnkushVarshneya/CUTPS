/*PurchasableItem class header
 *
 *Purpose: An abstract class in which the item is "purchasable" within CUtps
 *The purchasable content includes the textbooks, their chapters, and chapter sections
 *Has an itemID, a price, and an availability assigned to it
 *
 *Traceability: EO-10 of Entity Class DataDictionary in Deliverable 1
 */

#ifndef PURCHASABLEITEM_H
#define PURCHASABLEITEM_H

#include <QList>
#include <QObject>
#include <QString>
#include "CUtpsDataObject.h"

class PurchasableItem : public CUtpsDataObject{

public:
    PurchasableItem(qint32 = -1, float = 0, bool = false);
    ~PurchasableItem();

    qint32              getItemID() const;
    float               getPrice();
    bool                isAvailable();
    void                setItemID(qint32);
    void                setPrice(float);
    void                setAvailability(bool);
    virtual QString     getItemTitle() const = 0;
    virtual void        setItemTitle(QString) = 0;
    bool                operator==(const PurchasableItem&) const;
    void                read(const QJsonObject &json);
    void                write(QJsonObject &json) const;


private:
    qint32   itemID;
    float    price;
    bool     availability;
};

#endif // PURCHASABLEITEM_H
