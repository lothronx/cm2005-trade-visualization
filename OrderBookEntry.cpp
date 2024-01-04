#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(double _price,
                               double _amount,
                               std::string _timestamp,
                               std::string _product,
                               OrderBookType _orderType,
                               std::string _username)
        : price{_price},
          amount{_amount},
          timestamp{std::move(_timestamp)},
          product{std::move(_product)},
          orderType{_orderType},
          username{std::move(_username)} {}

double OrderBookEntry::getPrice() const { return price; }

double OrderBookEntry::getAmount() const { return amount; }

std::string OrderBookEntry::getTimestamp() const { return timestamp; }

std::string OrderBookEntry::getProduct() const { return product; }

OrderBookType OrderBookEntry::getOrderType() const { return orderType; }

std::string OrderBookEntry::getUsername() const { return username; }

void OrderBookEntry::setAmount(double _amount) { amount = _amount; }

void OrderBookEntry::setOrderType(OrderBookType _orderType) { orderType = _orderType; }

void OrderBookEntry::setUsername(std::string _username) { username = std::move(_username); }

OrderBookType OrderBookEntry::stringToOrderBookType(const std::string &s) {
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