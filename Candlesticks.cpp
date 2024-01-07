// ============================
// I wrote the following code
// ============================

#include "Candlesticks.h"

/* To initialize the Candlesticks object, we need to pass the following parameters by reference:
- product: the product to be analyzed
- orderType: the order type to be analyzed
- timestamp: the current timestamp
- orderBook: the entire order book
*/
Candlesticks::Candlesticks(const std::string &_product,
                           const std::string &_orderType,
                           const std::string &_timestamp,
                           const OrderBook &_orderBook) :
        product{_product},
        orderType{_orderType},
        timestamp{_timestamp},
        orderBook{_orderBook} {}


/** Compute trading statistics and store them in a vector of Candlestick objects.*/
void Candlesticks::compute() {
    // convert the order type from string to OrderBookType
    OrderBookType type{OrderBookEntry::stringToOrderBookType(orderType)};

    // store the current timestamp in a local variable
    std::string time{timestamp};

    // for the past 12 timestamps (60 seconds)
    for (int i = 0; i < 12; ++i) {
        // get the orders at the current timestamp
        std::vector<OrderBookEntry> currentEntries = orderBook.getOrders(type,
                                                                         product,
                                                                         time);

        // get the previous timestamp
        std::string previousTime = orderBook.getPreviousTime(time);

        // get the orders at the previous timestamp
        std::vector<OrderBookEntry> previousEntries = orderBook.getOrders(type,
                                                                          product,
                                                                          previousTime);

        // compute the trading statistics and push them as a Candlestick object to the candlesticks vector
        candlesticks.push_back({
                                       time.substr(11, 8),
                                       OrderBook::getAveragePrice(previousEntries),
                                       OrderBook::getHighPrice(currentEntries),
                                       OrderBook::getLowPrice(currentEntries),
                                       OrderBook::getAveragePrice(currentEntries),
                                       OrderBook::getVolume(currentEntries)}
        );

        // update the current timestamp to the previous timestamp
        time = previousTime;
    }
}


/** Print the trading statistics in a table. */
void Candlesticks::printTable() const {

    // print the title
    std::cout << '\n'
              << std::setw(32) << std::setfill(' ') << std::right
              << "\033[1;51m  >>> " << orderType << "s on " << product << " <<<  \033[0m"
              << '\n'
              << '\n';

    // print the header row
    std::cout << "Time" << std::setw(15)
              << "Open" << std::setw(15)
              << "High" << std::setw(15)
              << "Low" << std::setw(15)
              << "Close" << '\n';

    // print the trading statistics for each timestamp (from the oldest to the most recent)
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


/** Print the trading statistics in a candlestick chart. */
void Candlesticks::printCandlestickChart() const {
    // print the header row with "price" as the y-axis variable
    Candlesticks::drawHeaderRow("Price");

    // set the plot height to 20
    int plotHeight = 20;
    // the top of the plot is the highest price
    double highest = getHighestPrice(candlesticks);
    // the bottom of the plot is the lowest price
    double lowest = getLowestPrice(candlesticks);
    // calculate the interval between two adjacent y-axis labels based on the highest and lowest price
    double interval = (highest - lowest) / (plotHeight - 1);

    // For each row of the plot
    for (int i = 0; i < plotHeight; ++i) {
        // calculate the y-axis label
        double yAxisLabel = highest - i * interval;
        // calculate the y-axis label below the current one
        double yAxisLabelBelow = highest - (i + 1) * interval;

        // print the y-axis label
        std::cout << std::setw(15) << std::setfill(' ') << std::right << yAxisLabel << " │ ";

        // for each candlestick (from the oldest to the most recent)
        for (const auto &candlestick: std::ranges::reverse_view(candlesticks)) {
            // set the color of the candlestick
            setColor(candlestick);
            // if the "candle box" (with open price as the upper bound and close price as the lower bound, or vise versa) is within the range of the current label and the label below
            if ((yAxisLabel >= candlestick.open && candlestick.close >= yAxisLabelBelow) ||
                (yAxisLabel >= candlestick.close && candlestick.open >= yAxisLabelBelow)) {
                // print the "candle box"
                std::cout << "   █████   ";
                //else if the current label is within the range of the "candle stick" (with high price as the upper bound and low price as the lower bound)
            } else if (candlestick.high >= yAxisLabel && yAxisLabel >= candlestick.low) {
                // print the "candle stick"
                std::cout << "     ░     ";
                // else
            } else {
                // print blank space
                std::cout << "           ";
            }
            // reset the color to default
            clearColor();
        }
        std::cout << '\n';
    }

    // draw the x-axis labels
    drawXAxisLabels();
}


/** Print the trading statistics in a volume bar chart. */
void Candlesticks::printVolumeBars() const {
    // Print the header row with "volume" as the y-axis variable
    Candlesticks::drawHeaderRow("Volume");

    // Set the plot height to 20
    int plotHeight = 20;
    // The top of the plot is the highest volume. The bottom of the plot is 0.
    auto highest = getHighestVolume(candlesticks);
    // Calculate the interval between two adjacent y-axis labels based on the highest volume
    double interval = highest / (plotHeight - 1);

    // For each row of the plot
    for (int i = 0; i < plotHeight; ++i) {
        // Calculate the y-axis label
        double yAxisLabel = highest - i * interval;
        // Print the y-axis label
        std::cout << std::setw(15) << std::setfill(' ') << std::right << yAxisLabel << " │ ";

        // For each candlestick (from the oldest to the most recent)
        for (const auto &candlestick: std::ranges::reverse_view(candlesticks)) {
            // Set the color of the candlestick
            setColor(candlestick);
            // If the label is larger than the volume, print blank space. Else, print the volume bar.
            (yAxisLabel > candlestick.volume
             ? std::cout << "           "
             : std::cout << "   █████   ");
            // Reset the color to default
            clearColor();
        }
        std::cout << '\n';
    }

    // Print the x-axis labels
    drawXAxisLabels();
}


/** Print the header row of the plot.
* @param yAxisVariable: the variable name to be displayed on the y-axis
*/
void Candlesticks::drawHeaderRow(const std::string &yAxisVariable) const {
    std::cout << std::setw(19) << std::setfill('-') << std::right << "│" << std::setw(135) << '\n'
              << std::setw(15) << std::setfill(' ') << yAxisVariable << " │ "
              << std::setw(60) << "\033[1m  >>> " << orderType << "s on " << product << " <<<  \033[0m" << '\n'
              << std::setw(19) << std::setfill('-') << "│" << std::setw(135) << '\n';
}


/** Print the x-axis labels. The x-axis labels are the timestamps. */
void Candlesticks::drawXAxisLabels() const {
    std::cout << std::setw(19) << std::setfill('-') << std::right << "│" << std::setw(135) << '\n';

    // print the x-axis labels (from the oldest to the most recent)
    std::cout << std::setw(15) << std::setfill(' ') << "Time" << " │   ";
    for (const auto &candlestick: std::ranges::reverse_view(candlesticks)) {
        std::cout << std::setw(11) << std::left << candlestick.time;
    }
    std::cout << '\n';

    std::cout << std::setw(19) << std::setfill('-') << std::right << "│" << std::setw(135) << '\n'
              << '\n' << '\n';
}


/* Set the color of the candlestick based on the open and close price.
- If the open price is lower than the close price, the candlestick is green.
- If the open price is higher than the close price, the candlestick is red.
- If the open price is equal to the close price, the candlestick is yellow.
*/
void Candlesticks::setColor(const Candlestick &candlestick) {
    if (candlestick.open < candlestick.close) {
        std::cout << "\033[32m";
    } else if (candlestick.open > candlestick.close) {
        std::cout << "\033[31m";
    } else {
        std::cout << "\033[33m";
    }
}


/** reset the color to default */
void Candlesticks::clearColor() {
    std::cout << "\033[0m";
}


/** Return the highest price of the given candlesticks */
double Candlesticks::getHighestPrice(const std::vector<Candlestick> &candlesticks) {
    double highest = candlesticks[0].high;
    for (const auto &candlestick: candlesticks) {
        if (candlestick.high > highest) {
            highest = candlestick.high;
        }
    }
    return highest;
}


/** Return the lowest price of the given candlesticks */
double Candlesticks::getLowestPrice(const std::vector<Candlestick> &candlesticks) {
    double lowest = candlesticks[0].low;
    for (const auto &candlestick: candlesticks) {
        if (candlestick.low < lowest) {
            lowest = candlestick.low;
        }
    }
    return lowest;
}


/** Return the highest volume of the given candlesticks */
double Candlesticks::getHighestVolume(const std::vector<Candlestick> &candlesticks) {
    double highest = candlesticks[0].volume;
    for (const auto &candlestick: candlesticks) {
        if (candlestick.volume > highest) {
            highest = candlestick.volume;
        }
    }
    return highest;
}
// ============================
//        End of my code
// ============================