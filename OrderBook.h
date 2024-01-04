#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
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


    static double getHighPrice(const std::vector<OrderBookEntry> &orders);

    static double getLowPrice(const std::vector<OrderBookEntry> &orders);

    static double getAveragePrice(const std::vector<OrderBookEntry> &orders);

    /** returns the earliest time in the orderbook*/
    std::string getEarliestTime() const;

    /** returns the next time after the
     * sent time in the orderbook
     * If there is no next timestamp, wraps around to the start
     * */
    std::string getNextTime(const std::string &timestamp) const;

    std::string getPreviousTime(const std::string &timestamp) const;

    void insertOrder(const OrderBookEntry &order);

    std::vector<OrderBookEntry> matchAsksToBids(const std::string &product,
                                                const std::string &timestamp) const;

private:
    std::vector<OrderBookEntry> orders;
};
