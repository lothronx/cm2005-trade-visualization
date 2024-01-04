#pragma once

#include <string>
#include <ranges>
#include "OrderBook.h"

using namespace std;

struct Candlestick {
    string time;
    double open;
    double high;
    double low;
    double close;
};

class Candlesticks {
public:
    /** construct, each candlestick should have 5 parameters */
    Candlesticks(string &_product,
                 OrderBookType &_orderType,
                 string &_timestamp,
                 const OrderBook &_orderBook);

    void printTable();

    void printPlot();

private:
    string &product;
    OrderBookType &orderType;
    string &timestamp;
    const OrderBook &orderBook;

    vector<Candlestick> compute();
};