#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"


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

    int getUserOption();

    void processUserOption(int userOption);

    string currentTime;

    OrderBook orderBook{"../20200601.csv"};

    Wallet wallet;

};
