#include "MerkelMain.h"

void MerkelMain::init() {
    int input;

    wallet.insertCurrency("BTC", 10);

    currentTime = orderBook.getEarliestTime();
    // because we offer users the option to print previous market trends, we can't start from the earliest timestamp--there will be no trends to print! Let's start from the 7th timestamp instead.
    for (int i = 0; i < 6; ++i) {
        currentTime = orderBook.getNextTime(currentTime);
    }

    while (true) {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::printMenu() {
    // 1 print help
    cout << "1: Print help " << endl
         // 2 print exchange stats
         << "2: Print exchange stats" << endl
         // 3 make an offer
         << "3: Make an offer " << endl
         // 4 make a bid
         << "4: Make a bid " << endl
         // 5 print wallet
         << "5: Print wallet " << endl
         // 6 continue
         << "6: Continue " << endl

         << "7: Print candlesticks " << endl

         << "============== " << endl

         << "Current time is: " << currentTime << endl;
}

void MerkelMain::printError() {
    cout << "Invalid choice. Choose 1-7" << endl;
}

void MerkelMain::printHelp() {
    cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << endl;
}

void MerkelMain::printMarketStats() {
    for (string const &p: orderBook.getKnownProducts()) {
        cout << "Product: " << p << endl;
        vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
                                                             p, currentTime);
        cout << "Asks seen: " << entries.size() << endl;
        cout << "Max ask: " << OrderBook::getHighPrice(entries) << endl;
        cout << "Min ask: " << OrderBook::getLowPrice(entries) << endl;

    }
}

void MerkelMain::enterAsk() {
    cout << "Make an ask - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << endl;
    string input;
    getline(cin, input);

    vector<string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3) {
        cout << "MerkelMain::enterAsk Bad input! " << input << endl;
    } else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                    tokens[1],
                    tokens[2],
                    currentTime,
                    tokens[0],
                    OrderBookType::ask
            );
            obe.setUsername("simuser");
            if (wallet.canFulfillOrder(obe)) {
                cout << "Wallet looks good. " << endl;
                orderBook.insertOrder(obe);
            } else {
                cout << "Wallet has insufficient funds . " << endl;
            }
        } catch (const exception &e) {
            cout << " MerkelMain::enterAsk Bad input " << endl;
        }
    }
}

void MerkelMain::enterBid() {
    cout << "Make an bid - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << endl;
    string input;
    getline(cin, input);

    vector<string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3) {
        cout << "MerkelMain::enterBid Bad input! " << input << endl;
    } else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                    tokens[1],
                    tokens[2],
                    currentTime,
                    tokens[0],
                    OrderBookType::bid
            );
            obe.setUsername("simuser");

            if (wallet.canFulfillOrder(obe)) {
                cout << "Wallet looks good. " << endl;
                orderBook.insertOrder(obe);
            } else {
                cout << "Wallet has insufficient funds . " << endl;
            }
        } catch (const exception &e) {
            cout << " MerkelMain::enterBid Bad input " << endl;
        }
    }
}

void MerkelMain::printWallet() {
    cout << wallet.toString() << endl;
}

void MerkelMain::gotoNextTimeframe() {
    cout << "Going to next time frame. " << endl;
    for (const string &p: orderBook.getKnownProducts()) {
        cout << "matching " << p << endl;
        vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        cout << "Sales: " << sales.size() << endl;
        for (OrderBookEntry &sale: sales) {
            cout << "Sale price: " << sale.getPrice() << " amount " << sale.getAmount() << endl;
            if (sale.getUsername() == "simuser") {
                // update the wallet
                wallet.processSale(sale);
            }
        }

    }

    currentTime = orderBook.getNextTime(currentTime);
}

// I wrote the following code
void MerkelMain::printCandlesticks() {

    cout << "View market trends in candlesticks - enter: product,order type. E.g., ETH/BTC,bid" << endl;

    string input;
    getline(cin, input);

    vector<string> tokens = CSVReader::tokenise(input, ',');

    vector<string> productList{orderBook.getKnownProducts()};

    if (tokens.size() != 2 ||
        find(productList.begin(), productList.end(), tokens[0]) == productList.end() ||
        (tokens[1] != "ask" && tokens[1] != "bid")) {
        cout << "MerkelMain::printCandlesticks Bad input! " << input << endl;
    } else {
        vector<Candlestick> candlesticks{};
        string time = currentTime;
        for (int i = 0; i < 6; ++i) {
            vector<OrderBookEntry> currentEntries = orderBook.getOrders(
                    OrderBookEntry::stringToOrderBookType(tokens[1]),
                    tokens[0],
                    time);
            time = orderBook.getPreviousTime(time);
            vector<OrderBookEntry> previousEntries = orderBook.getOrders(
                    OrderBookEntry::stringToOrderBookType(tokens[1]),
                    tokens[0],
                    time);
            candlesticks.push_back({
                                           orderBook.getNextTime(time),
                                           OrderBook::getAveragePrice(previousEntries),
                                           OrderBook::getHighPrice(currentEntries),
                                           OrderBook::getLowPrice(currentEntries),
                                           OrderBook::getAveragePrice(currentEntries)});
        }

        cout << endl
             << setw(30) << "\033[1;51m  >>> " << tokens[1] << "s on " << tokens[0] << " <<<  \033[0m"
             << endl << endl
             << "Time" << setw(15)
             << "Open" << setw(15)
             << "High" << setw(15)
             << "Low" << setw(15)
             << "Close" << endl;
        for (auto &candlestick: ranges::reverse_view(candlesticks)) {
            if (candlestick.open < candlestick.close) {
                cout << "\033[32m";
            } else if (candlestick.open > candlestick.close) {
                cout << "\033[31m";
            } else {
                cout << "\033[33m";
            }

            cout << (candlestick.time).substr(11, 8)
                 << setw(15) << candlestick.open
                 << setw(15) << candlestick.high
                 << setw(15) << candlestick.low
                 << setw(15) << candlestick.close
                 << endl;
        }
        cout << "\033[0m" << endl;
    }
}
// end of my code

int MerkelMain::getUserOption() {
    int userOption = 0;
    string line;
    cout << "Type in 1-7" << endl;
    getline(cin, line);
    try {
        userOption = stoi(line);
    } catch (const exception &e) {}
    cout << "You chose: " << userOption << endl;
    return userOption;
}

void MerkelMain::processUserOption(int userOption) {

    // I wrote the following code
    // map integers (keys) to function pointers (values)
    map<int, void (MerkelMain::*)()> menu;
    menu[0] = &MerkelMain::printError;
    menu[1] = &MerkelMain::printHelp;
    menu[2] = &MerkelMain::printMarketStats;
    menu[3] = &MerkelMain::enterAsk;
    menu[4] = &MerkelMain::enterBid;
    menu[5] = &MerkelMain::printWallet;
    menu[6] = &MerkelMain::gotoNextTimeframe;
    menu[7] = &MerkelMain::printCandlesticks;

    // check if the userOption is a valid key
    if (menu.find(userOption) != menu.end()) {
        // If valid, call the corresponding function
        (this->*menu[userOption])();
    } else {
        // otherwise, print the error message
        printError();
    }
    // end of my code
}
