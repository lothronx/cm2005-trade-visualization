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
                                       orderBook.getNextTime(time),
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
              << std::setw(32) << "\033[1;51m  >>> " << type << "s on " << product << " <<<  \033[0m"
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

        std::cout << (candlestick.time).substr(11, 8) << std::setw(15)
                  << candlestick.open << std::setw(15)
                  << candlestick.high << std::setw(15)
                  << candlestick.low << std::setw(15)
                  << candlestick.close << '\n';
    }

    std::cout << "\033[0m" << '\n';
}

void Candlesticks::printPlot() const {}