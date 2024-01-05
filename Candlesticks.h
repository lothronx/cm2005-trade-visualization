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
    unsigned long volume;
};

class Candlesticks {
public:
    /** construct, each candlestick should have 5 parameters */
    Candlesticks(const std::string &_product,
                 const std::string &_orderType,
                 const std::string &_timestamp,
                 const OrderBook &_orderBook);

    void compute();

    void printTable() const;

    void printCandlestickChart() const;

    void printHistogram() const;

private:
    std::vector<Candlestick> candlesticks;
    const std::string &product;
    const std::string &orderType;
    const std::string &timestamp;
    const OrderBook &orderBook;

    static void setColor(const Candlestick &candlestick);

    static void clearColor();

    static double getHighestPrice(const std::vector<Candlestick> &candlesticks);

    static double getLowestPrice(const std::vector<Candlestick> &candlesticks);

    static unsigned long getHighestVolume(const std::vector<Candlestick> &candlesticks);

    void drawHeaderRow(const std::string &name) const;

    void drawXAxisLabels() const;
};