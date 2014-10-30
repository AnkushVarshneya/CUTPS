/*ShoppingCart header file
 *Date last modified: 10/24/2014
 *
 */
#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include "PurchasableItem.h"
#include <QMap>

class ShoppingCart{

public:
    ShoppingCart(qint32 = 0);
    ~ShoppingCart();
    QList<PurchasableItem*>&                  getItems();
    qint32                                    getShoppingCartID() const;
    void                                      setShoppingCartID(qint32);
    void                                      addItem(PurchasableItem*);
    void                                      emptyShoppingCart();

private:
    QList<PurchasableItem*>                   items;
    qint32                                    id;
};

#endif // SHOPPINGCART_H
