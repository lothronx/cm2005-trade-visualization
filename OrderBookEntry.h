#pragma once

#include <string>

using namespace std;

enum class OrderBookType {
  bid, ask, unknown
};

class OrderBookEntry {
public:
  OrderBookEntry(double _price,
                 double _amount,
                 string _timestamp,
                 string _product,
                 OrderBookType _orderType,
                 string _username = "dataset");

  double getPrice() const { return price; }

  double getAmount() const { return amount; }

  string getTimestamp() const { return timestamp; }

  string getProduct() const { return product; }

  OrderBookType getOrderType() const { return orderType; }

  static OrderBookType stringToOrderBookType(string s);

  static bool compareByTimestamp(OrderBookEntry &e1, OrderBookEntry &e2) {
    return e1.timestamp < e2.timestamp;
  }

  static bool compareByPriceAsc(OrderBookEntry &e1, OrderBookEntry &e2) {
    return e1.price < e2.price;
  }

  static bool compareByPriceDesc(OrderBookEntry &e1, OrderBookEntry &e2) {
    return e1.price > e2.price;
  }

private:
  double price;
  double amount;
  string timestamp;
  string product;
  OrderBookType orderType;
  string username;
};
