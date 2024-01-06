#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include<map>
#include <ranges>
#include <algorithm>
#include <regex>
#include "OrderBook.h"
#include "CSVReader.h"
#include "Wallet.h"
#include "Candlesticks.h"

class MerkelMain {
public:
    MerkelMain() = default;

    /** Call this to start the sim */
    void init();

private:
    void printMenu();

    // ============================
    // I wrote the following code
    // ============================
    /** Print an error message */
    void printError();
    // ============================
    //        End of my code
    // ============================

    void printHelp();

    void printMarketStats();

    void enterAsk();

    void enterBid();

    void printWallet();

    void gotoNextTimeframe();

    // ============================
    // I wrote the following code
    // ============================
    /** Print the trading data of the past 60 seconds for a product and order type */
    void printCandlesticks();
    // ============================
    //        End of my code
    // ============================

    int getUserOption();

    void processUserOption(const int &userOption);

    std::string currentTime;

    OrderBook orderBook{"20200601.csv"};

    Wallet wallet;

};
