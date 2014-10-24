/*Billing Address header class
 *Date last modified: 10/24/2014
 *By: Rob
 *
 *Billing address is for use as part of the PaymentInformation class
 *that has this component
 *
 */
#ifndef BILLINGADDRESS_H
#define BILLINGADDRESS_H

#include <string>

class BillingAddress{
public:
    BillingAddress();
    ~BillingAddress();
    string getName();
    int getHouseNumber();
    string getStreetName();
    string getCity();
    string getProvince();
    string getPostalCode();

    void setAddress(string,int,string,string,string,string);
    void setAddress(const BillingAddress&);

private:
    string name;
    int houseNumber;
    string streetName;
    string city;
    string province;
    string postalCode;
};

#endif // BILLINGADDRESS_H
