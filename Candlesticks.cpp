#include "Candlesticks.h"

Candlesticks::Candlesticks(const string &_product,
                           const OrderBookType &_orderType,
                           const string &_timestamp,
                           const OrderBook &_orderBook) :
        product{_product},
        orderType{_orderType},
        timestamp{_timestamp},
        orderBook{_orderBook} {}

void Candlesticks::compute() {
    string time = timestamp;
    for (int i = 0; i < 6; ++i) {
        vector<OrderBookEntry> currentEntries = orderBook.getOrders(orderType,
                                                                    product,
                                                                    time);
        time = orderBook.getPreviousTime(time);
        vector<OrderBookEntry> previousEntries = orderBook.getOrders(orderType,
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
    string type{};
    if (orderType == OrderBookType::ask) {
        type = "Ask";
    } else {
        type = "Bid";
    }

    cout << endl
         << setw(32) << "\033[1;51m  >>> " << type << "s on " << product << " <<<  \033[0m"
         << endl
         << endl;

    cout << "Time" << setw(15)
         << "Open" << setw(15)
         << "High" << setw(15)
         << "Low" << setw(15)
         << "Close" << endl;

    for (const auto &candlestick: ranges::reverse_view(candlesticks)) {
        if (candlestick.open < candlestick.close) {
            cout << "\033[32m";
        } else if (candlestick.open > candlestick.close) {
            cout << "\033[31m";
        } else {
            cout << "\033[33m";
        }

        cout << (candlestick.time).substr(11, 8) << setw(15)
             << candlestick.open << setw(15)
             << candlestick.high << setw(15)
             << candlestick.low << setw(15)
             << candlestick.close << endl;
    }

    cout << "\033[0m" << endl;
}

void Candlesticks::printPlot() const {}