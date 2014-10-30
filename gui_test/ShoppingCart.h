/*ShoppingCart header file
 *Date last modified: 10/24/2014
 *TODO:
 *Shopping cart has been modified to be a QMap PurchasableItem* key and quantity value
 *Need to implement properly addItem to accomodate QMap
 *Need to implement properly addItemQuantity(specify purchasableItem and the quantity to add)
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
    QMap<PurchasableItem*,qint32>&            getItems();
    qint32                                    getShoppingCartID() const;
    void                                      setShoppingCartID(qint32);
    void                                      addItem(PurchasableItem*);
    void                                      addItemQuantity(PurchasableItem*,int);
    void                                      emptyShoppingCart();
private:
    QMap<PurchasableItem*,qint32>             items;
    qint32                                    id;
};

#endif // SHOPPINGCART_H
