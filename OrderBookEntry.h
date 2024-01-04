#pragma once

#include <string>

using namespace std;

enum class OrderBookType {
    bid, ask, unknown, bidsale, asksale
};

class OrderBookEntry {
public:
    OrderBookEntry(double _price,
                   double _amount,
                   string _timestamp,
                   string _product,
                   OrderBookType _orderType,
                   string _username = "dataset");

    double getPrice() const;

    double getAmount() const;

    string getTimestamp() const;

    string getProduct() const;

    OrderBookType getOrderType() const;

    string getUsername() const;

    void setAmount(double _amount);

    void setOrderType(OrderBookType _orderType);

    void setUsername(string _username);

    static OrderBookType stringToOrderBookType(const string &s);

    static bool compareByTimestamp(const OrderBookEntry &e1, const OrderBookEntry &e2);

    static bool compareByPriceAsc(const OrderBookEntry &e1, const OrderBookEntry &e2);

    static bool compareByPriceDesc(const OrderBookEntry &e1, const OrderBookEntry &e2);

private:
    double price;
    double amount;
    string timestamp;
    string product;
    OrderBookType orderType;
    string username;
};
