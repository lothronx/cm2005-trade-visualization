#include <iostream>
#include<map>

using namespace std;

void printMenu() {
  // 1 print help
  cout << "1: Print help " << endl
       // 2 print exchange stats
       << "2: Print exchange stats" << endl
       // 3 make an offer
       << "3: Make an offer " << endl
       // 4 make a bid
       << "4: Make a bid " << endl
       // 5 print wallet
       << "5: Print wallet " << endl
       // 6 continue
       << "6: Continue " << endl

       << "============== " << endl;

// cout << "Current time is: " << currentTime << endl;
}

void printError() {
  cout << "Invalid choice. Choose 1-6" << endl;
}

void printHelp() {
  cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << endl;
}

void printMarketStats() {
//  for (string const& p : orderBook.getKnownProducts())
//  {
//    cout << "Product: " << p << endl;
//    vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
//                                                              p, currentTime);
//    cout << "Asks seen: " << entries.size() << endl;
//    cout << "Max ask: " << OrderBook::getHighPrice(entries) << endl;
//    cout << "Min ask: " << OrderBook::getLowPrice(entries) << endl;

}

void enterAsk() {
//  cout << "Make an ask - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << endl;
//  string input;
//  getline(cin, input);
//
//  vector<string> tokens = CSVReader::tokenise(input, ',');
//  if (tokens.size() != 3)
//  {
//    cout << "MerkelMain::enterAsk Bad input! " << input << endl;
//  }
//  else {
//    try {
//      OrderBookEntry obe = CSVReader::stringsToOBE(
//          tokens[1],
//          tokens[2],
//          currentTime,
//          tokens[0],
//          OrderBookType::ask
//      );
//      obe.username = "simuser";
//      if (wallet.canFulfillOrder(obe))
//      {
//        cout << "Wallet looks good. " << endl;
//        orderBook.insertOrder(obe);
//      }
//      else {
//        cout << "Wallet has insufficient funds . " << endl;
//      }
//    }catch (const exception& e)
//    {
//      cout << " MerkelMain::enterAsk Bad input " << endl;
//    }
//  }
}

void enterBid() {
//  cout << "Make an bid - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << endl;
//  string input;
//  getline(cin, input);
//
//  vector<string> tokens = CSVReader::tokenise(input, ',');
//  if (tokens.size() != 3)
//  {
//    cout << "MerkelMain::enterBid Bad input! " << input << endl;
//  }
//  else {
//    try {
//      OrderBookEntry obe = CSVReader::stringsToOBE(
//          tokens[1],
//          tokens[2],
//          currentTime,
//          tokens[0],
//          OrderBookType::bid
//      );
//      obe.username = "simuser";
//
//      if (wallet.canFulfillOrder(obe))
//      {
//        cout << "Wallet looks good. " << endl;
//        orderBook.insertOrder(obe);
//      }
//      else {
//        cout << "Wallet has insufficient funds . " << endl;
//      }
//    }catch (const exception& e)
//    {
//      cout << " MerkelMain::enterBid Bad input " << endl;
//    }
//  }
}

void printWallet() {
  //cout << wallet.toString() << endl;
}

void gotoNextTimeframe() {
//  cout << "Going to next time frame. " << endl;
//  for (string p: orderBook.getKnownProducts()) {
//    cout << "matching " << p << endl;
//    vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
//    cout << "Sales: " << sales.size() << endl;
//    for (OrderBookEntry &sale: sales) {
//      cout << "Sale price: " << sale.price << " amount " << sale.amount << endl;
//      if (sale.username == "simuser") {
//        // update the wallet
//        wallet.processSale(sale);
//      }
//    }
//
//  }
//
//  currentTime = orderBook.getNextTime(currentTime);
}

int getUserOption() {
  int userOption = 0;
  string line;
  cout << "Type in 1-6" << endl;
  getline(cin, line);
  try {
    userOption = stoi(line);
  } catch (const exception &e) {

  }
  cout << "You chose: " << userOption << endl;
  return userOption;
}

void processUserOption(int userOption) {
  // I wrote the following code
  // use function pointers to map integers to functions
  map<int, void (*)()> menu;
  menu[0] = printError;
  menu[1] = printHelp;
  menu[2] = printMarketStats;
  menu[3] = enterAsk;
  menu[4] = enterBid;
  menu[5] = printWallet;
  menu[6] = gotoNextTimeframe;
  // call the corresponding function
  menu[userOption]();
  // end of my code
}


int main() {

  int input;
  while (true) {
    printMenu();
    input = getUserOption();
    processUserOption(input);
  }
  return 0;
}
