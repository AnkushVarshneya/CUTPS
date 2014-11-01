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
#include "CUtpsDataObject.h"

class PurchasableItem : public CUtpsDataObject{

public:
    PurchasableItem(qint32 = 1337, float = 13.37, bool = false);
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
