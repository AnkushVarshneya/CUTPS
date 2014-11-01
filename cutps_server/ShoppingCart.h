/*ShoppingCart header file
 *Date last modified: 10/24/2014
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
