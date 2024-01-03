#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include "OrderBookEntry.h"

using namespace std;

class CSVReader {
public:
    CSVReader() = default;

    static vector<OrderBookEntry> readCSV(const string &csvFile);

    static vector<string> tokenise(const string &csvLine, char separator);

    static OrderBookEntry stringsToOBE(const string &price,
                                       const string &amount,
                                       const string &timestamp,
                                       const string &product,
                                       const OrderBookType &orderType);

private:
    static OrderBookEntry stringsToOBE(vector<string> strings);
};