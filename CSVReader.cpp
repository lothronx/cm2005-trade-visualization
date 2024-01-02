#include "CSVReader.h"

vector<OrderBookEntry> CSVReader::readCSV(const string &csvFilename) {
    vector<OrderBookEntry> entries;

    ifstream csvFile{csvFilename};
    string line;
    if (csvFile.is_open()) {
        while (getline(csvFile, line)) {
            try {
                OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
                entries.push_back(obe);
            } catch (const exception &e) {
                cout << "CSVReader::readCSV bad data" << endl;
            }
        }// end of while
    } else {
        cerr << "Cannot open file " << csvFilename << endl;
    }

    cout << "CSVReader::readCSV read " << entries.size() << " entries" << endl;
    return entries;
}

vector<string> CSVReader::tokenise(const string &csvLine, char separator) {
    vector<string> tokens;

    // I wrote the following code
    // turn csvLine into a stream
    stringstream ss(csvLine);
    // read tokens from the stream into a vector
    while (ss.good()) {
        string token;
        getline(ss, token, separator);
        tokens.push_back(token);
    }
    // end of my code

    return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(vector<string> tokens) {
    double price, amount;

    if (tokens.size() != 5) {
        cout << "Bad line " << endl;
        throw exception{};
    }

    try {
        price = stod(tokens[3]);
        amount = stod(tokens[4]);
    } catch (const exception &e) {
        cout << "CSVReader::stringsToOBE Bad float! " << tokens[3] << endl;
        cout << "CSVReader::stringsToOBE Bad float! " << tokens[4] << endl;
        throw;
    }

    OrderBookEntry obe{price,
                       amount,
                       tokens[0],
                       tokens[1],
                       OrderBookEntry::stringToOrderBookType(tokens[2])};

    return obe;
}


OrderBookEntry CSVReader::stringsToOBE(const string &priceString,
                                       const string &amountString,
                                       string timestamp,
                                       string product,
                                       OrderBookType orderType) {
    double price, amount;
    try {
        price = stod(priceString);
        amount = stod(amountString);
    } catch (const exception &e) {
        cout << "CSVReader::stringsToOBE Bad float! " << priceString << endl;
        cout << "CSVReader::stringsToOBE Bad float! " << amountString << endl;
        throw;
    }
    OrderBookEntry obe{price,
                       amount,
                       std::move(timestamp),
                       std::move(product),
                       orderType};

    return obe;
}
     