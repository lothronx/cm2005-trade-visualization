#pragma once

#include <string>
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
    Candlesticks(string _product, OrderBookType _orderType);

    string product;
    OrderBookType orderType;
};