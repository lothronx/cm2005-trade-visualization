#pragma once

#include <string>
#include <map>
#include "OrderBookEntry.h"
#include <iostream>

using namespace std;

class Wallet {
public:
    Wallet() = default;

    /** insert currency to the wallet */
    void insertCurrency(string type, double amount);

    /** remove currency from the wallet */
    bool removeCurrency(string type, double amount);

    /** check if the wallet contains this much currency or more */
    bool containsCurrency(string type, double amount);

    /** checks if the wallet can cope with this ask or bid.*/
    bool canFulfillOrder(OrderBookEntry order);

    /** update the contents of the wallet
     * assumes the order was made by the owner of the wallet
    */
    void processSale(OrderBookEntry &sale);

    /** generate a string representation of the wallet */
    string toString();

    friend ostream &operator<<(ostream &os, Wallet &wallet);

private:
    map<string, double> currencies;
};





