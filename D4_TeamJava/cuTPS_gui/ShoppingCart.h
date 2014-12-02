/*ShoppingCart header file
 *
 *Purpose of this class: A container or inventory of items much like a real-world shopping cart
 *This will be used by the Student to keep track of what items they want to buy.
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

class ShoppingCart : public CUtpsDataObject{

public:
    ShoppingCart(qint32 = 0);
    ~ShoppingCart();
    QList<PurchasableItem*>&                  getItems();
    qint32                                    getShoppingCartID() const;
    void                                      setShoppingCartID(qint32);
    void                                      addItem(PurchasableItem*);
    void                                      emptyShoppingCart();
    void                                      read(const QJsonObject &json);
    void                                      write(QJsonObject &json) const;

private:
    QList<PurchasableItem*>                   items;
    qint32                                    id;
};

#endif // SHOPPINGCART_H
