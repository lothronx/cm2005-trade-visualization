#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include "CSVReader.h"
#include "OrderBookEntry.h"

using namespace std;

class OrderBook {
public:
    /** construct, reading a csv data file */
    explicit OrderBook(const string &filename);

    /** return vector of all know products in the dataset*/
    vector<string> getKnownProducts();

    /** return vector of Orders according to the sent filters*/
    vector<OrderBookEntry> getOrders(const OrderBookType &type,
                                     const string &product,
                                     const string &timestamp);


    static double getHighPrice(vector<OrderBookEntry> &orders);

    static double getLowPrice(vector<OrderBookEntry> &orders);

    static double getAveragePrice(vector<OrderBookEntry> &orders);

    /** returns the earliest time in the orderbook*/
    string getEarliestTime();

    /** returns the next time after the
     * sent time in the orderbook
     * If there is no next timestamp, wraps around to the start
     * */
    string getNextTime(const string &timestamp);

    string getPreviousTime(const string &timestamp);

    void insertOrder(const OrderBookEntry &order);

    vector<OrderBookEntry> matchAsksToBids(const string &product, const string &timestamp);

private:
    vector<OrderBookEntry> orders;
};
