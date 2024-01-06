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
    double volume;
};

class Candlesticks {
public:
    Candlesticks(const std::string &_product,
                 const std::string &_orderType,
                 const std::string &_timestamp,
                 const OrderBook &_orderBook);

    void compute();

    void printTable() const;

    void printCandlestickChart() const;

    void printVolumeBars() const;

private:
    std::vector<Candlestick> candlesticks;

    // Parameters
    const std::string &product;
    const std::string &orderType;
    const std::string &timestamp;
    const OrderBook &orderBook;

    // Helper functions
    static double getHighestPrice(const std::vector<Candlestick> &candlesticks);

    static double getLowestPrice(const std::vector<Candlestick> &candlesticks);

    static double getHighestVolume(const std::vector<Candlestick> &candlesticks);

    static void setColor(const Candlestick &candlestick);

    static void clearColor();

    void drawHeaderRow(const std::string &yAxisVariable) const;

    void drawXAxisLabels() const;
};