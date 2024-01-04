#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include "OrderBookEntry.h"

class CSVReader {
public:
    CSVReader() = default;

    static std::vector<OrderBookEntry> readCSV(const std::string &csvFile);

    static std::vector<std::string> tokenise(const std::string &csvLine, char separator);

    static OrderBookEntry stringsToOBE(const std::string &price,
                                       const std::string &amount,
                                       const std::string &timestamp,
                                       const std::string &product,
                                       const OrderBookType &orderType);

private:
    static OrderBookEntry stringsToOBE(const std::vector<std::string> &strings);
};