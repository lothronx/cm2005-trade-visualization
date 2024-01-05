#include "MerkelMain.h"

void MerkelMain::init() {
    int input;

    wallet.insertCurrency("BTC", 10);

    currentTime = orderBook.getEarliestTime();
    // because we offer users the option to print previous market trends, we can't start from the earliest timestamp--there will be no trends to print! Let's start from the 13th timestamp instead.
    for (int i = 0; i < 12; ++i) {
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
    std::cout << "1: Print help " << '\n'
              // 2 print exchange stats
              << "2: Print exchange stats" << '\n'
              // 3 make an offer
              << "3: Make an offer " << '\n'
              // 4 make a bid
              << "4: Make a bid " << '\n'
              // 5 print wallet
              << "5: Print wallet " << '\n'
              // 6 continue
              << "6: Continue " << '\n'

              << "7: Print candlesticks " << '\n'

              << "============== " << '\n'

              << "Current time is: " << currentTime << '\n';
}

void MerkelMain::printError() {
    std::cout << "Invalid choice. Choose 1-7" << '\n';
}

void MerkelMain::printHelp() {
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << '\n';
}

void MerkelMain::printMarketStats() {
    for (std::string const &p: orderBook.getKnownProducts()) {
        std::cout << "Product: " << p << '\n';
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
                                                                  p, currentTime);
        std::cout << "Asks seen: " << entries.size() << '\n';
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << '\n';
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << '\n';

    }
}

void MerkelMain::enterAsk() {
    std::cout << "Make an ask - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << '\n';
    std::string input;
    getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3) {
        std::cout << "MerkelMain::enterAsk Bad input! " << input << '\n';
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
                std::cout << "Wallet looks good. " << '\n';
                orderBook.insertOrder(obe);
            } else {
                std::cout << "Wallet has insufficient funds . " << '\n';
            }
        } catch (const std::exception &e) {
            std::cout << " MerkelMain::enterAsk Bad input " << '\n';
        }
    }
}

void MerkelMain::enterBid() {
    std::cout << "Make an bid - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << '\n';
    std::string input;
    getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3) {
        std::cout << "MerkelMain::enterBid Bad input! " << input << '\n';
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
                std::cout << "Wallet looks good. " << '\n';
                orderBook.insertOrder(obe);
            } else {
                std::cout << "Wallet has insufficient funds . " << '\n';
            }
        } catch (const std::exception &e) {
            std::cout << " MerkelMain::enterBid Bad input " << '\n';
        }
    }
}

void MerkelMain::printWallet() {
    std::cout << wallet.toString() << '\n';
}

void MerkelMain::gotoNextTimeframe() {
    std::cout << "Going to next time frame. " << '\n';
    for (const std::string &p: orderBook.getKnownProducts()) {
        std::cout << "matching " << p << '\n';
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << '\n';
        for (OrderBookEntry &sale: sales) {
            std::cout << "Sale price: " << sale.getPrice() << " amount " << sale.getAmount() << '\n';
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
    std::cout
            << "View market data of the past 60 seconds in table, candlestick chart, and volume bar graph.\nEnter: product,order type. E.g., BTC/USDT,bid\n";

    std::string input;
    getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

    std::vector<std::string> productList{orderBook.getKnownProducts()};

    if (tokens.size() != 2 ||
        find(productList.begin(), productList.end(), tokens[0]) == productList.end() ||
        (tokens[1] != "ask" && tokens[1] != "bid")) {
        std::cout << "MerkelMain::printCandlesticks Bad input! Please use the correct format. E.g., BTC/USDT,bid\n";
    } else {
        Candlesticks candlesticks{tokens[0],
                                  tokens[1],
                                  currentTime,
                                  orderBook};
        candlesticks.compute();
        candlesticks.printTable();
        candlesticks.printCandlestickChart();
        candlesticks.printHistogram();
    }
}
// end of my code

int MerkelMain::getUserOption() {
    int userOption = 0;
    std::string line;
    std::cout << "Type in 1-7" << '\n';
    getline(std::cin, line);
    try {
        userOption = stoi(line);
    } catch (const std::exception &e) {}
    std::cout << "You chose: " << userOption << '\n';
    return userOption;
}

void MerkelMain::processUserOption(const int &userOption) {

    // I wrote the following code
    // map integers (keys) to function pointers (values)
    std::map<int, void (MerkelMain::*)()> menu;
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
