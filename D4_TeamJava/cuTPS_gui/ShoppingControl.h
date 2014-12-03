/*Class responsible for handling the rest of the application logic concerning a user's request as defined through the interface
 *Responsible for delegating functionality to the ShopUpdateControl which uses the Client Communicator subsystem to connect with the server to retrieve/update
 *persistent data information.
 *
 *Combines classes: AddContentControl, ViewShoppingCartControl, CancelOrderControl, ViewTextbooksControl, CheckoutControl into one Control class that handles
 *all operations with these individual ones
 *
 *Traceability: SS-01-02 (Part of ShoppingManagement Subsystem)
 *
 */

#ifndef SHOPPINGCONTROL_H
#define SHOPPINGCONTROL_H

class ShoppingControl
{
public:
    ShoppingControl();
};

#endif // SHOPPINGCONTROL_H
