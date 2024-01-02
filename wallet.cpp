#include "Wallet.h"
#include <iostream>
#include "CSVReader.h"

void Wallet::insertCurrency(string type, double amount) {
    double balance;
    if (amount < 0) {
        throw exception{};
    }
    if (currencies.count(type) == 0) // not there yet
    {
        balance = 0;
    } else { // is there
        balance = currencies[type];
    }
    balance += amount;
    currencies[type] = balance;
}

bool Wallet::removeCurrency(string type, double amount) {
    if (amount < 0) {
        return false;
    }
    if (currencies.count(type) == 0) // not there yet
    {
        //cout << "No currency for " << type << endl;
        return false;
    } else { // is there - do  we have enough
        if (containsCurrency(type, amount))// we have enough
        {
            //cout << "Removing " << type << ": " << amount << endl;
            currencies[type] -= amount;
            return true;
        } else // they have it but not enough.
            return false;
    }
}

bool Wallet::containsCurrency(string type, double amount) {
    if (currencies.count(type) == 0) // not there yet
        return false;
    else
        return currencies[type] >= amount;

}

string Wallet::toString() {
    string s;
    for (pair<string, double> pair: currencies) {
        string currency = pair.first;
        double amount = pair.second;
        s += currency + " : " + to_string(amount) + "\n";
    }
    return s;
}

bool Wallet::canFulfillOrder(OrderBookEntry order) {
    vector<string> currs = CSVReader::tokenise(order.getProduct(), '/');
    // ask
    if (order.getOrderType() == OrderBookType::ask) {
        double amount = order.getAmount();
        string currency = currs[0];
        cout << "Wallet::canFulfillOrder " << currency << " : " << amount << endl;

        return containsCurrency(currency, amount);
    }
    // bid
    if (order.getOrderType() == OrderBookType::bid) {
        double amount = order.getAmount() * order.getPrice();
        string currency = currs[1];
        cout << "Wallet::canFulfillOrder " << currency << " : " << amount << endl;
        return containsCurrency(currency, amount);
    }


    return false;
}


void Wallet::processSale(OrderBookEntry &sale) {
    vector<string> currs = CSVReader::tokenise(sale.getProduct(), '/');
    // ask
    if (sale.getOrderType() == OrderBookType::asksale) {
        double outgoingAmount = sale.getAmount();
        string outgoingCurrency = currs[0];
        double incomingAmount = sale.getAmount() * sale.getPrice();
        string incomingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;

    }
    // bid
    if (sale.getOrderType() == OrderBookType::bidsale) {
        double incomingAmount = sale.getAmount();
        string incomingCurrency = currs[0];
        double outgoingAmount = sale.getAmount() * sale.getPrice();
        string outgoingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
}

ostream &operator<<(ostream &os, Wallet &wallet) {
    os << wallet.toString();
    return os;
}

