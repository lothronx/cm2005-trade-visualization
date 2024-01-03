#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(double _price,
                               double _amount,
                               string _timestamp,
                               string _product,
                               OrderBookType _orderType,
                               string _username)
        : price{_price},
          amount{_amount},
          timestamp{_timestamp},
          product{_product},
          orderType{_orderType},
          username{_username} {}

double OrderBookEntry::getPrice() const { return price; }

double OrderBookEntry::getAmount() const { return amount; }

void OrderBookEntry::setAmount(double _amount) { amount = _amount; }

string OrderBookEntry::getTimestamp() const { return timestamp; }

string OrderBookEntry::getProduct() const { return product; }

OrderBookType OrderBookEntry::getOrderType() const { return orderType; }

void OrderBookEntry::setOrderType(OrderBookType _orderType) { orderType = _orderType; }

string OrderBookEntry::getUsername() const { return username; }

void OrderBookEntry::setUsername(string _username) { username = _username; }

OrderBookType OrderBookEntry::stringToOrderBookType(const string &s) {
    if (s == "ask") {
        return OrderBookType::ask;
    }
    if (s == "bid") {
        return OrderBookType::bid;
    }
    return OrderBookType::unknown;
}

bool OrderBookEntry::compareByTimestamp(const OrderBookEntry &e1, const OrderBookEntry &e2) {
    return e1.timestamp < e2.timestamp;
}

bool OrderBookEntry::compareByPriceAsc(const OrderBookEntry &e1, const OrderBookEntry &e2) {
    return e1.price < e2.price;
}

bool OrderBookEntry::compareByPriceDesc(const OrderBookEntry &e1, const OrderBookEntry &e2) {
    return e1.price > e2.price;
}