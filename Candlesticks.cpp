#include "Candlesticks.h"

Candlesticks::Candlesticks(string _product,
                           OrderBookType _orderType,
                           string _timestamp) :
        product{_product},
        orderType{_orderType},
        timestamp{_timestamp} {}

vector<Candlestick> Candlesticks::compute() {
    vector<Candlestick> candlesticks{};
    for (int i = 0; i < 6; ++i) {
        candlesticks.push_back({"111", 1, 1, 1, 1});
    }
    return candlesticks;
};

void Candlesticks::printTable() {
    vector<Candlestick> candlesticks = compute();
    for (const Candlestick &candlestick: candlesticks) {
        cout << "Time: " << candlestick.time << endl
             << "Open: " << candlestick.open << endl
             << "High: " << candlestick.high << endl
             << "Low: " << candlestick.low << endl
             << "Close: " << candlestick.close << endl
             << "---------------" << endl;
    };
};

void Candlesticks::printPlot() {};