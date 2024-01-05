#include "Candlesticks.h"

Candlesticks::Candlesticks(const std::string &_product,
                           const OrderBookType &_orderType,
                           const std::string &_timestamp,
                           const OrderBook &_orderBook) :
        product{_product},
        orderType{_orderType},
        timestamp{_timestamp},
        orderBook{_orderBook} {}

void Candlesticks::compute() {
    std::string time = timestamp;
    for (int i = 0; i < 12; ++i) {
        std::vector<OrderBookEntry> currentEntries = orderBook.getOrders(orderType,
                                                                         product,
                                                                         time);
        time = orderBook.getPreviousTime(time);
        std::vector<OrderBookEntry> previousEntries = orderBook.getOrders(orderType,
                                                                          product,
                                                                          time);

        candlesticks.push_back({
                                       (orderBook.getNextTime(time)).substr(11, 8),
                                       OrderBook::getAveragePrice(previousEntries),
                                       OrderBook::getHighPrice(currentEntries),
                                       OrderBook::getLowPrice(currentEntries),
                                       OrderBook::getAveragePrice(currentEntries)});
    }

}


void Candlesticks::printTable() const {
    std::string type{};
    if (orderType == OrderBookType::ask) {
        type = "Ask";
    } else {
        type = "Bid";
    }

    std::cout << '\n'
              << std::setw(32) << std::right << "\033[1;51m  >>> " << type << "s on " << product << " <<<  \033[0m"
              << '\n'
              << '\n';

    std::cout << "Time" << std::setw(15)
              << "Open" << std::setw(15)
              << "High" << std::setw(15)
              << "Low" << std::setw(15)
              << "Close" << '\n';

    for (const auto &candlestick: std::ranges::reverse_view(candlesticks)) {
        if (candlestick.open < candlestick.close) {
            std::cout << "\033[32m";
        } else if (candlestick.open > candlestick.close) {
            std::cout << "\033[31m";
        } else {
            std::cout << "\033[33m";
        }

        std::cout << candlestick.time << std::setw(15)
                  << candlestick.open << std::setw(15)
                  << candlestick.high << std::setw(15)
                  << candlestick.low << std::setw(15)
                  << candlestick.close << '\n';
    }

    std::cout << "\033[0m" << '\n';
}

void Candlesticks::printPlot() const {
    int plotHeight = 20;
    double highest = getHighest(candlesticks);
    double lowest = getLowest(candlesticks);
    double interval = (highest - lowest) / plotHeight;

    // Draw the plot
    std::cout << '\n';
    for (int i = 0; i <= plotHeight; ++i) {

        double label = highest - i * interval;
        double labelBelow = highest - (i + 1) * interval;

        std::cout << std::setw(11) << std::setfill(' ') << std::right << label << " │ ";
        for (const auto &candlestick: std::ranges::reverse_view(candlesticks)) {
            if (candlestick.open < candlestick.close) {
                std::cout << "\033[32m";
            } else if (candlestick.open > candlestick.close) {
                std::cout << "\033[31m";
            } else {
                std::cout << "\033[33m";
            }

            if ((label >= candlestick.open && candlestick.close >= labelBelow) ||
                (label >= candlestick.close && candlestick.open >= labelBelow)) {
                std::cout << "   █████   ";
            } else if (candlestick.high >= label && label >= candlestick.low) {
                std::cout << "     ░     ";
            } else {
                std::cout << "           ";
            }

            std::cout << "\033[0m";
        }
        std::cout << '\n';
    }

    // Draw x-axis labels
    std::cout << std::setw(154) << std::setfill('=') << '\n';
    std::cout << std::setw(11) << std::setfill(' ') << std::right << "Time" << " │   ";
    for (const auto &candlestick: std::ranges::reverse_view(candlesticks)) {
        std::cout << std::setw(11) << std::left << candlestick.time;
    }
    std::cout << '\n' << '\n';
}

double Candlesticks::getHighest(const std::vector<Candlestick> &candlesticks) {
    double highest = candlesticks[0].high;
    for (const auto &candlestick: candlesticks) {
        if (candlestick.high > highest) {
            highest = candlestick.high;
        }
    }
    return highest;
}

double Candlesticks::getLowest(const std::vector<Candlestick> &candlesticks) {
    double lowest = candlesticks[0].low;
    for (const auto &candlestick: candlesticks) {
        if (candlestick.low < lowest) {
            lowest = candlestick.low;
        }
    }
    return lowest;
}