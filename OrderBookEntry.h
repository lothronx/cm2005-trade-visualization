#pragma once

#include <string>

enum class OrderBookType {
    bid, ask, unknown, bidsale, asksale
};

class OrderBookEntry {
public:
    OrderBookEntry(double _price,
                   double _amount,
                   std::string _timestamp,
                   std::string _product,
                   OrderBookType _orderType,
                   std::string _username = {"dataset"});

    // ============================
    // I wrote the following code
    // ============================
    double getPrice() const;

    double getAmount() const;

    std::string getTimestamp() const;

    std::string getProduct() const;

    OrderBookType getOrderType() const;

    std::string getUsername() const;

    void setAmount(double _amount);

    void setOrderType(OrderBookType _orderType);

    void setUsername(std::string _username);
    // ============================
    //        End of my code
    // ============================

    static OrderBookType stringToOrderBookType(const std::string &s);

    static bool compareByTimestamp(const OrderBookEntry &e1, const OrderBookEntry &e2);

    static bool compareByPriceAsc(const OrderBookEntry &e1, const OrderBookEntry &e2);

    static bool compareByPriceDesc(const OrderBookEntry &e1, const OrderBookEntry &e2);

private:
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
    std::string username;
};
