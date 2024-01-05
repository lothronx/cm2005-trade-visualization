#pragma once

#include <string>
#include <ranges>
#include <iostream>
#include "OrderBook.h"

struct Candlestick {
    std::string time;
    double open;
    double high;
    double low;
    double close;
};

class Candlesticks {
public:
    /** construct, each candlestick should have 5 parameters */
    Candlesticks(const std::string &_product,
                 const OrderBookType &_orderType,
                 const std::string &_timestamp,
                 const OrderBook &_orderBook);

    void compute();

    void printTable() const;

    void printPlot() const;

private:
    const std::string &product;
    const OrderBookType &orderType;
    const std::string &timestamp;
    const OrderBook &orderBook;
    std::vector<Candlestick> candlesticks;

    static double getHighest(const std::vector<Candlestick> &candlesticks);

    static double getLowest(const std::vector<Candlestick> &candlesticks);
};