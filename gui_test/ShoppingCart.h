/*ShoppingCart header file
 *Date last modified: 10/24/2014
 *Contains  a list of purchasable item pointers
 */
#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include "PurchasableItem.h"

class ShoppingCart{

public:
    ShoppingCart();
    ~ShoppingCart();
    QList<PurchasableItem*>&    getItems();
    qint32                      getShoppingCartID();
    void                        setShoppingCartID(qint32);
    void                        addItem(PurchasableItem*);
    void                        emptyShoppingCart();
private:
    QList<PurchasableItem*>     items;
    qint32                      id;
};

#endif // SHOPPINGCART_H
