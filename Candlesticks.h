// ============================
// I wrote the following code
// ============================

#pragma once

#include <string>
#include <ranges>
#include <iostream>
#include "OrderBook.h"

/** The Candlestick structure stores information about the opening, highest, lowest, and closing prices, along with the volume, of a specific timestamp (for one product and one order type). */
struct Candlestick {
    std::string time;
    double open;
    double high;
    double low;
    double close;
    double volume;
};

/**
 * Given a product and order type, the Candlesticks class computes its trading statistics in the past 60 seconds and prints them in a table, a candlestick chart, and a volume bar chart.
 * The trading statistics are stored in a vector of Candlestick objects.
 */
class Candlesticks {
public:
    /* To initialize the Candlesticks object, we need to pass the following parameters by reference:
     - product: the product to be analyzed
     - orderType: the order type to be analyzed
     - timestamp: the current timestamp
     - orderBook: the entire order book
     */
    Candlesticks(const std::string &_product,
                 const std::string &_orderType,
                 const std::string &_timestamp,
                 const OrderBook &_orderBook);


    /** Compute trading statistics and store them in a vector of Candlestick objects.*/
    void compute();

    /** Print the trading statistics in a table. */
    void printTable() const;

    /** Print the trading statistics in a candlestick chart. */
    void printCandlestickChart() const;

    /** Print the trading statistics in a volume bar chart. */
    void printVolumeBars() const;

private:
    /** The candlesticks vector stores the trading statistics of the past 12 timestamps for the given product and order type. */
    std::vector<Candlestick> candlesticks;

    // ========= Constant members to store the passed parameters ==========
    const std::string &product;
    const std::string &orderType;
    const std::string &timestamp;
    const OrderBook &orderBook;

    // ==================Helper functions====================
    /** Return the highest price of the given candlesticks */
    static double getHighestPrice(const std::vector<Candlestick> &candlesticks);

    /** Return the lowest price of the given candlesticks */
    static double getLowestPrice(const std::vector<Candlestick> &candlesticks);

    /** Return the highest volume of the given candlesticks */
    static double getHighestVolume(const std::vector<Candlestick> &candlesticks);

    /* Set the color of the candlestick based on the open and close price.
     - If the close price is higher than the open price, the candlestick is green.
     - If the close price is lower than the open price, the candlestick is red.
     - If the close price is equal to the open price, the candlestick is yellow.
     */
    static void setColor(const Candlestick &candlestick);

    /** reset the color to default */
    static void clearColor();

    /** Print the header row of the plot.
     * @param yAxisVariable: the variable name to be displayed on the y-axis
     */
    void drawHeaderRow(const std::string &yAxisVariable) const;

    /** Print the x-axis labels. The x-axis labels are the timestamps. */
    void drawXAxisLabels() const;
};

// ============================
//        End of my code
// ============================