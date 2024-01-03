#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include<map>
#include <ranges>
#include <algorithm>
#include "OrderBook.h"
#include "CSVReader.h"
#include "Wallet.h"
#include "Candlesticks.h"

using namespace std;

class MerkelMain {
public:
    MerkelMain() = default;

    /** Call this to start the sim */
    void init();

private:
    void printMenu();

    void printError();

    void printHelp();

    void printMarketStats();

    void enterAsk();

    void enterBid();

    void printWallet();

    void gotoNextTimeframe();

    void printCandlesticks();

    int getUserOption();

    void processUserOption(int userOption);

    string currentTime;

    // Because I'm using CLion to run the code, the relative path here is relative to the cmake-build-debug folder not the root folder. Thus, "../" is needed here.
    OrderBook orderBook{"../20200601.csv"};

    Wallet wallet;

};
