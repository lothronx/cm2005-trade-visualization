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

    void setAmount(double _amount);

    string getTimestamp() const;

    string getProduct() const;

    OrderBookType getOrderType() const;

    void setOrderType(OrderBookType _orderType);

    string getUsername() const;

    void setUsername(string _username);

    static OrderBookType stringToOrderBookType(string s);

    static bool compareByTimestamp(OrderBookEntry &e1, OrderBookEntry &e2);

    static bool compareByPriceAsc(OrderBookEntry &e1, OrderBookEntry &e2);

    static bool compareByPriceDesc(OrderBookEntry &e1, OrderBookEntry &e2);

private:
    double price;
    double amount;
    string timestamp;
    string product;
    OrderBookType orderType;
    string username;
};
