/*ShoppingCart header file
 *
 *Purpose of this class: A container or inventory of items much like a real-world shopping cart
 *This will be used by the Student to keep track of what items they want to buy.
 *A Pair system is implemented in the shopping cart to keep track of the purchasble item
 *and its quantity currently in shopping cart
 *
 *Has a list of items, and an ID (for potential extensibility to persistantly store the shopping cart's contents
 *in the future)
 *
 *Traceability: EO-14
 *
 */
#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include "PurchasableItem.h"
#include <QList>
#include "CUtpsDataObject.h"
#include <QMap>
#include <QPair>

class ShoppingCart : public CUtpsDataObject{

public:
    ShoppingCart();
    ~ShoppingCart();
    QList<QPair<PurchasableItem*,qint32>>&    getItems();
    void                                      emptyShoppingCart();
    void                                      read(const QJsonObject &json);
    void                                      write(QJsonObject &json) const;

private:
    QPair<PurchasableItem*,qint32>            items;
};

#endif // SHOPPINGCART_H
