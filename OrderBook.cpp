#include "OrderBook.h"

#include <ranges>

/** construct, reading a csv data file */
OrderBook::OrderBook(const std::string &filename)
        : orders{CSVReader::readCSV(filename)} {}

/** return vector of all know products in the dataset*/
std::vector<std::string> OrderBook::getKnownProducts() const {
    std::vector<std::string> products;

    std::map<std::string, bool> prodMap;

    for (const OrderBookEntry &e: orders) {
        prodMap[e.getProduct()] = true;
    }

    // now flatten the map to a vector of strings
    products.reserve(prodMap.size());
    for (const auto &e: prodMap) {
        products.push_back(e.first);
    }

    return products;
}

/** return vector of Orders according to the sent filters*/
std::vector<OrderBookEntry> OrderBook::getOrders(const OrderBookType &type,
                                                 const std::string &product,
                                                 const std::string &timestamp) const {
    std::vector<OrderBookEntry> orders_sub;
    for (const OrderBookEntry &e: orders) {
        if (e.getOrderType() == type &&
            e.getProduct() == product &&
            e.getTimestamp() == timestamp) {
            orders_sub.push_back(e);
        }
    }
    return orders_sub;
}

double OrderBook::getHighPrice(const std::vector<OrderBookEntry> &orders) {
    double max = orders[0].getPrice();
    for (const OrderBookEntry &e: orders) {
        if (e.getPrice() > max)max = e.getPrice();
    }
    return max;
}

double OrderBook::getLowPrice(const std::vector<OrderBookEntry> &orders) {
    double min = orders[0].getPrice();
    for (const OrderBookEntry &e: orders) {
        if (e.getPrice() < min)min = e.getPrice();
    }
    return min;
}

double OrderBook::getAveragePrice(const std::vector<OrderBookEntry> &orders) {
    double sum{};
    for (const OrderBookEntry &e: orders) {
        sum += e.getPrice();
    }
    double avg = sum / orders.size();
    return avg;
}

std::string OrderBook::getEarliestTime() const {
    return orders[0].getTimestamp();
}

std::string OrderBook::getNextTime(const std::string &timestamp) const {
    std::string next_timestamp{};
    for (const OrderBookEntry &e: orders) {
        if (e.getTimestamp() > timestamp) {
            next_timestamp = e.getTimestamp();
            break;
        }
    }
    if (next_timestamp.empty()) {
        next_timestamp = orders[0].getTimestamp();
    }
    return next_timestamp;
}

std::string OrderBook::getPreviousTime(const std::string &timestamp) const {
    std::string previous_timestamp{};
    for (const auto &order: std::ranges::reverse_view(orders)) {
        if (order.getTimestamp() < timestamp) {
            previous_timestamp = order.getTimestamp();
            break;
        }
    }
    if (previous_timestamp.empty()) {
        previous_timestamp = orders[0].getTimestamp();
    }
    return previous_timestamp;
}

void OrderBook::insertOrder(const OrderBookEntry &order) {
    orders.push_back(order);
    sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(const std::string &product, const std::string &timestamp) const {
// asks = orderbook.asks
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask,
                                                 product,
                                                 timestamp);
// bids = orderbook.bids
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid,
                                                 product,
                                                 timestamp);

    // sales = []
    std::vector<OrderBookEntry> sales;

    // I put in a little check to ensure we have bids and asks
    // to process.
    if (asks.empty() || bids.empty()) {
        std::cout << " OrderBook::matchAsksToBids no bids or asks" << '\n';
        return sales;
    }

    // sort asks lowest first
    sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    // sort bids highest first
    sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);
    // for ask in asks:
    std::cout << "max ask " << asks[asks.size() - 1].getPrice() << '\n';
    std::cout << "min ask " << asks[0].getPrice() << '\n';
    std::cout << "max bid " << bids[0].getPrice() << '\n';
    std::cout << "min bid " << bids[bids.size() - 1].getPrice() << '\n';

    for (OrderBookEntry &ask: asks) {
        //     for bid in bids:
        for (OrderBookEntry &bid: bids) {
            //         if bid.price >= ask.price # we have a match
            if (bid.getPrice() >= ask.getPrice()) {
                //             sale = new order()
                //             sale.price = ask.price
                OrderBookEntry sale{ask.getPrice(), 0, timestamp,
                                    product,
                                    OrderBookType::asksale};

                if (bid.getUsername() == "simuser") {
                    sale.setUsername("simuser");
                    sale.setOrderType(OrderBookType::bidsale);
                }
                if (ask.getUsername() == "simuser") {
                    sale.setUsername("simuser");
                    sale.setOrderType(OrderBookType::asksale);
                }

                //             # now work out how much was sold and
                //             # create new bids and asks covering
                //             # anything that was not sold
                //             if bid.amount == ask.amount: # bid completely clears ask
                if (bid.getAmount() == ask.getAmount()) {
                    //                 sale.amount = ask.amount
                    sale.setAmount(ask.getAmount());
                    //                 sales.append(sale)
                    sales.push_back(sale);
                    //                 bid.amount = 0 # make sure the bid is not processed again
                    bid.setAmount(0);
                    //                 # can do no more with this ask
                    //                 # go onto the next ask
                    //                 break
                    break;
                }
                //           if bid.amount > ask.amount:  # ask is completely gone slice the bid
                if (bid.getAmount() > ask.getAmount()) {
                    //                 sale.amount = ask.amount
                    sale.setAmount(ask.getAmount());
                    //                 sales.append(sale)
                    sales.push_back(sale);
                    //                 # we adjust the bid in place
                    //                 # so it can be used to process the next ask
                    //                 bid.amount = bid.amount - ask.amount
                    bid.setAmount(bid.getAmount() - ask.getAmount());
                    //                 # ask is completely gone, so go to next ask
                    //                 break
                    break;
                }


                //             if bid.amount < ask.amount # bid is completely gone, slice the ask
                if (bid.getAmount() < ask.getAmount() &&
                    bid.getAmount() > 0) {
                    //                 sale.amount = bid.amount
                    sale.setAmount(bid.getAmount());
                    //                 sales.append(sale)
                    sales.push_back(sale);
                    //                 # update the ask
                    //                 # and allow further bids to process the remaining amount
                    //                 ask.amount = ask.amount - bid.amount
                    ask.setAmount(ask.getAmount() - bid.getAmount());
                    //                 bid.amount = 0 # make sure the bid is not processed again
                    bid.setAmount(0);
                    //                 # some ask remains so go to the next bid
                    //                 continue
                    continue;
                }
            }
        }
    }
    return sales;
}
