#include "Candlesticks.h"

Candlesticks::Candlesticks(const std::string &_product,
                           const std::string &_orderType,
                           const std::string &_timestamp,
                           const OrderBook &_orderBook) :
        product{_product},
        orderType{_orderType},
        timestamp{_timestamp},
        orderBook{_orderBook} {}

void Candlesticks::compute() {
    OrderBookType type{OrderBookEntry::stringToOrderBookType(orderType)};
    std::string time{timestamp};

    for (int i = 0; i < 12; ++i) {
        std::vector<OrderBookEntry> currentEntries = orderBook.getOrders(type,
                                                                         product,
                                                                         time);
        std::string previousTime = orderBook.getPreviousTime(time);

        std::vector<OrderBookEntry> previousEntries = orderBook.getOrders(type,
                                                                          product,
                                                                          previousTime);

        candlesticks.push_back({
                                       time.substr(11, 8),
                                       OrderBook::getAveragePrice(previousEntries),
                                       OrderBook::getHighPrice(currentEntries),
                                       OrderBook::getLowPrice(currentEntries),
                                       OrderBook::getAveragePrice(currentEntries),
                                       currentEntries.size()}
        );

        time = previousTime;
    }
}

void Candlesticks::printTable() const {
    std::cout << '\n'
              << std::setw(32) << std::setfill(' ') << std::right
              << "\033[1;51m  >>> " << orderType << "s on " << product << " <<<  \033[0m"
              << '\n'
              << '\n';

    std::cout << "Time" << std::setw(15)
              << "Open" << std::setw(15)
              << "High" << std::setw(15)
              << "Low" << std::setw(15)
              << "Close" << '\n';

    for (const auto &candlestick: std::ranges::reverse_view(candlesticks)) {
        setColor(candlestick);
        std::cout << candlestick.time << std::setw(15)
                  << candlestick.open << std::setw(15)
                  << candlestick.high << std::setw(15)
                  << candlestick.low << std::setw(15)
                  << candlestick.close << '\n';
        clearColor();
    }
    std::cout << '\n';
}

void Candlesticks::printCandlestickChart() const {

    Candlesticks::drawHeaderRow("Price");

    int plotHeight = 20;
    double highest = getHighestPrice(candlesticks);
    double lowest = getLowestPrice(candlesticks);
    double interval = (highest - lowest) / plotHeight;

    // Draw the chart
    for (int i = 0; i <= plotHeight; ++i) {

        double yAxisLabel = highest - i * interval;
        double yAxisLabelBelow = highest - (i + 1) * interval;

        std::cout << std::setw(11) << std::setfill(' ') << std::right << yAxisLabel << " │ ";

        for (const auto &candlestick: std::ranges::reverse_view(candlesticks)) {
            setColor(candlestick);
            if ((yAxisLabel >= candlestick.open && candlestick.close >= yAxisLabelBelow) ||
                (yAxisLabel >= candlestick.close && candlestick.open >= yAxisLabelBelow)) {
                std::cout << "   █████   ";
            } else if (candlestick.high >= yAxisLabel && yAxisLabel >= candlestick.low) {
                std::cout << "     ░     ";
            } else {
                std::cout << "           ";
            }
            clearColor();
        }
        std::cout << '\n';
    }

    drawXAxisLabels();
}

void Candlesticks::printHistogram() const {
    Candlesticks::drawHeaderRow("Volume");
    int plotHeight = 20;
    auto highest = static_cast<double>(getHighestVolume(candlesticks));
    double interval = highest / plotHeight;

    // Draw the chart
    for (int i = 0; i <= plotHeight; ++i) {

        double yAxisLabel = highest - i * interval;

        std::cout << std::setw(11) << std::setfill(' ') << std::right << yAxisLabel << " │ ";

        for (const auto &candlestick: std::ranges::reverse_view(candlesticks)) {
            (yAxisLabel > static_cast<double>(candlestick.volume)
             ? std::cout << "           "
             : std::cout << "   █████   ");
        }
        std::cout << '\n';
    }

    drawXAxisLabels();
}

void Candlesticks::setColor(const Candlestick &candlestick) {
    if (candlestick.open < candlestick.close) {
        std::cout << "\033[32m";
    } else if (candlestick.open > candlestick.close) {
        std::cout << "\033[31m";
    } else {
        std::cout << "\033[33m";
    }
}

void Candlesticks::clearColor() {
    std::cout << "\033[0m";
}

double Candlesticks::getHighestPrice(const std::vector<Candlestick> &candlesticks) {
    double highest = candlesticks[0].high;
    for (const auto &candlestick: candlesticks) {
        if (candlestick.high > highest) {
            highest = candlestick.high;
        }
    }
    return highest;
}

double Candlesticks::getLowestPrice(const std::vector<Candlestick> &candlesticks) {
    double lowest = candlesticks[0].low;
    for (const auto &candlestick: candlesticks) {
        if (candlestick.low < lowest) {
            lowest = candlestick.low;
        }
    }
    return lowest;
}

unsigned long Candlesticks::getHighestVolume(const std::vector<Candlestick> &candlesticks) {
    unsigned long highest = candlesticks[0].volume;
    for (const auto &candlestick: candlesticks) {
        if (candlestick.volume > highest) {
            highest = candlestick.volume;
        }
    }
    return highest;
}

void Candlesticks::drawHeaderRow(const std::string &yAxisVariable) const {
    std::cout << std::setw(15) << std::setfill('-') << std::right << "│" << std::setw(135) << '\n'
              << std::setw(11) << std::setfill(' ') << yAxisVariable << " │ "
              << std::setw(60) << "\033[1m  >>> " << orderType << "s on " << product << " <<<  \033[0m" << '\n'
              << std::setw(15) << std::setfill('-') << "│" << std::setw(135) << '\n';
}

void Candlesticks::drawXAxisLabels() const {
    std::cout << std::setw(15) << std::setfill('-') << std::right << "│" << std::setw(135) << '\n';

    std::cout << std::setw(11) << std::setfill(' ') << "Time" << " │   ";
    for (const auto &candlestick: std::ranges::reverse_view(candlesticks)) {
        std::cout << std::setw(11) << std::left << candlestick.time;
    }
    std::cout << '\n';

    std::cout << std::setw(15) << std::setfill('-') << std::right << "│" << std::setw(135) << '\n'
              << '\n';
}