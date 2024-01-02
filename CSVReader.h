#pragma once

#include "OrderBookEntry.h"
#include <vector>
#include <string>

using namespace std;

class CSVReader {
public:
    CSVReader() = default;

    static vector<OrderBookEntry> readCSV(const string &csvFile);

    static vector<string> tokenise(const string &csvLine, char separator);

    static OrderBookEntry stringsToOBE(const string &price,
                                       const string &amount,
                                       string timestamp,
                                       string product,
                                       OrderBookType OrderBookType);

private:
    static OrderBookEntry stringsToOBE(vector<string> strings);

};