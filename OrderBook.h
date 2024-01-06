#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <ranges>
#include "CSVReader.h"
#include "OrderBookEntry.h"

class OrderBook {
public:
    /** construct, reading a csv data file */
    explicit OrderBook(const std::string &filename);

    /** return vector of all know products in the dataset*/
    std::vector<std::string> getKnownProducts() const;

    /** return vector of Orders according to the sent filters*/
    std::vector<OrderBookEntry> getOrders(const OrderBookType &type,
                                          const std::string &product,
                                          const std::string &timestamp) const;


    /** returns the earliest time in the order book*/
    std::string getEarliestTime() const;

    /** returns the next time after the sent time in the order book
     * If there is no next timestamp, wraps around to the start
     * */
    std::string getNextTime(const std::string &timestamp) const;

    // ============================
    // I wrote the following code
    // ============================
    /** returns the previous time before the sent time in the order book
     * If there is no previous timestamp, wraps around to the start
     */
    std::string getPreviousTime(const std::string &timestamp) const;
    // ============================
    //        End of my code
    // ============================

    void insertOrder(const OrderBookEntry &order);

    std::vector<OrderBookEntry> matchAsksToBids(const std::string &product,
                                                const std::string &timestamp) const;

    static double getHighPrice(const std::vector<OrderBookEntry> &orders);

    static double getLowPrice(const std::vector<OrderBookEntry> &orders);

    // ============================
    // I wrote the following code
    // ============================
    /** returns the average price of the given orders */
    static double getAveragePrice(const std::vector<OrderBookEntry> &orders);

    /** returns the volume (sum of amount*price) of the given orders */
    static double getVolume(const std::vector<OrderBookEntry> &orders);
    // ============================
    //        End of my code
    // ============================




private:
    std::vector<OrderBookEntry> orders;
};
