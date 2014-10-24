/*Billing Address header class
 *Date last modified: 10/24/2014
 *By: Rob
 *
 */
#ifndef BILLINGADDRESS_H
#define BILLINGADDRESS_H

#include <string>

class BillingAddress{
public:
    string getName();
    int getHouseNumber();
    string getStreetName();
    string getCity();
    string getProvince();
    string getPostalCode();

    void setAddress(string,int,string,string,string,string);
    void setAddress(BillingAddress&);

private:
    string name;
    int houseNumber;
    string streetName;
    string city;
    string province;
    string postalCode;
};

#endif // BILLINGADDRESS_H
