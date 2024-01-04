#include "CSVReader.h"

std::vector<OrderBookEntry> CSVReader::readCSV(const std::string &csvFilename) {
    std::vector<OrderBookEntry> entries;

    std::ifstream csvFile{csvFilename};
    std::string line;
    if (csvFile.is_open()) {
        while (getline(csvFile, line)) {
            try {
                OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
                entries.push_back(obe);
            } catch (const std::exception &e) {
                std::cout << "CSVReader::readCSV bad data" << '\n';
            }
        }
        csvFile.close();
    } else {
        std::cerr << "Cannot open file " << csvFilename << '\n';
    }

    std::cout << "CSVReader::readCSV read " << entries.size() << " entries" << '\n';
    return entries;
}

std::vector<std::string> CSVReader::tokenise(const std::string &csvLine, char separator) {
    std::vector<std::string> tokens;

    // I wrote the following code
    // turn csvLine into a stream
    std::stringstream ss(csvLine);
    // read tokens from the stream into a vector
    while (ss.good()) {
        std::string token;
        getline(ss, token, separator);
        tokens.push_back(token);
    }
    // end of my code

    return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(const std::vector<std::string> &tokens) {
    double price, amount;

    if (tokens.size() != 5) {
        std::cout << "Bad line " << '\n';
        throw std::exception{};
    }

    try {
        price = stod(tokens[3]);
        amount = stod(tokens[4]);
    } catch (const std::exception &e) {
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[3] << '\n';
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[4] << '\n';
        throw;
    }
    OrderBookType type{OrderBookEntry::stringToOrderBookType(tokens[2])};
    OrderBookEntry obe{price,
                       amount,
                       tokens[0],
                       tokens[1],
                       type};


    return obe;
}


OrderBookEntry CSVReader::stringsToOBE(const std::string &priceString,
                                       const std::string &amountString,
                                       const std::string &timestamp,
                                       const std::string &product,
                                       const OrderBookType &orderType) {
    double price, amount;
    try {
        price = stod(priceString);
        amount = stod(amountString);
    } catch (const std::exception &e) {
        std::cout << "CSVReader::stringsToOBE Bad float! " << priceString << '\n';
        std::cout << "CSVReader::stringsToOBE Bad float! " << amountString << '\n';
        throw;
    }
    OrderBookEntry obe{price,
                       amount,
                       timestamp,
                       product,
                       orderType};

    return obe;
}
     