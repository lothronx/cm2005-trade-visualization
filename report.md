# CM2005 Object Oriented Programming Midterm Report

Name: Yue Wu

Student Number: 210312838

My goal for the midterm assignment is to enable users to view market data of the past 60 seconds in table, candlestick chart, and volume bar graph. The user can choose to view the data of a product and order type of their choice by type in the product name and order type in this format: `productName,orderType`, for example, `BTC/USDT,bid`. To achieve this goal, I performed the three following tasks. I also made some additional changes to the source code to make the program more clean and efficient.

## TASK 1: Structure the program, compute the data, and print the table

For task 1, my goal is that, given a product and order type, the program can compute its trading statistics of the past 60 seconds and print the results in a table. To do so, following the object oriented programming principle, I created a new class `Candlesticks` as well as made changes to the `OrderBook` class and `MerkelMain` class.

### 1.1 Change the program start time

First, I examined the source code and noticed that the program begins with the earliest timestamp. The program then moves to the subsequent timestamp whenever the user inputs "6" and triggers the `gotoNextTimeframe` function.

The midterm instructions require students to visualize trading statistics. It would be strange to visualize statistics for "the future" since they haven't occurred yet. Therefore, I set my objective to display trading statistics from the past 60 seconds.

However, if the program started from the very first timestamp, there would be no trading history to analyze and display at all. To address this, I decided to have my program start from the 13th timestamp, which is 65 seconds after the earliest timestamp. (The gap between each timestamp is 5 seconds.)

In the `MerkelMain` class, I made the program start from the 13th timestamp by amending the `init` function and looping the `currentTime` member variable 12 times in the `getNextTime` function before everything else.

### 1.2 Expand the menu

In the source code, the menu has 6 options. The trading statistic visualization functionality will be the 7th option. I decided to call it `printCandlesticks`. In the `MerkelMain` class, I amended the `printMenu`, `getUserOption`, and `processUserOption` functions accordingly to include the new option.

### 1.3 Create the `printCandlesticks` function

Next, I implemented the `printCandlesticks` function in the `MerkelMain` class. The structure of the `printCandlesticks` function is similar to the `enterAsk` function in the source code.

- First, it prints the instructions.
- Then, it takes user input and tokenises it into tokens. Here, I also used regex functions to trim the leading and trailing whitespace from the tokens. This makes my program more user friendly.
- Next, I validate whether the user input is valid by checking whether the number of tokens is 2, whether the first token is a valid product name, and whether the second token is a valid order type.
- If the tokens are invalid, the program will print an error message.
- Otherwise, the program will pass the tokens along with other necessary information to initialize a `Candlesticks` object and leave the rest of the work to the `Candlesticks` class.

Encapsulating all the internal computation and visualization details in the `Candlesticks` class is a good practice of object oriented programming.

### 1.4 Code the `Candlesticks` class

For task 1, the main job of the `Candlesticks` class is to take necessary information from the outside world, calculate the trading statistics, and print the results in a table.

My considerations and decisions are as follows:

#### 1.4.1 Member variables

What outside information does the `Candlesticks` class need to perform the computation? The `Candlesticks` class needs the product name and order type to be sure. It also need to know the current time. Moreover, in order to analyze the orders of the past 60 seconds, it needs to have access to the order book. Thus, the `Candlesticks` class needs 4 constructor parameters in total: `product`, `orderType`, `timestamp`, and `orderBook`. They should all be passed by reference to avoid unnecessary copying.

How should the `Candlesticks` class store the computed data? My decision is to use a vector of `Candlestick` objects. Each `Candlestick` object should store the open, close, high, and low prices of one timestamp. Since the content of `Candlestick` is simple, I decided to define it as a c++ structure instead of a class:

```C++
struct Candlestick {
    std::string time;
    double open;
    double high;
    double low;
    double close;
};
```

Hence, the `Candlesticks` class should have 5 member variables in total. They should all be private.

```C++
std::vector<Candlestick> candlesticks;
const std::string &product;
const std::string &orderType;
const std::string &timestamp;
const OrderBook &orderBook;
```

#### 1.4.2 Member functions

Now we defined all the member variables, what member functions should the `Candlesticks` class have? Other than the constructor, it should have at least 2 public member functions: `compute` and `printTable`, so the outside world can call them to perform the computation and print the results respectively.

The `compute` function should loop 12 times back in time and eventually store 12 `Candlestick` objects (representing 12 timestamps, aka 60 seconds) in the candlesticks vector.

To loop back in time, I created a new helper function in the `OrderBook` class called `getPreviousTime`. It takes in a timestamp and returns the timestamp preceding it. The implementation is very similar to the `getNextTime` function in the source code. The only difference is that the `getPreviousTime` function loops through the orders vector in reverse order.

```C++
for (const auto &order: std::ranges::reverse_view(orders)) {
       // ...
    }
```

The implementation of the `compute` function is as follows:

```
- convert orderType from string to OrderBookType

- store the current time in a local variable (because we don't want to mess the timestamp outside the `Candlesticks` class!)

- for each loop

    - get all the orders of the current timestamp

    - get the previous timestamp

    - get all the orders of the previous timestamp

    - calculate the open, high, low, and close prices based on the orders of the current timestamp and the previous timestamp

    - push the current time as well as all the calculated results (bundled as a `Candlestick` object) to the candlesticks vector

    - update the current time to the previous time
```

For the calculation, the source code already provided us with the `getHighPrice` and `getLowPrice` helper functions in the `OrderBook` class. I just need to code a `getAveragePrice` helper function following the same logic. The `getAveragePrice` function is stored in the `OrderBook` class next to its peers.

The `printTable` function should print the candlesticks vector in a table. The implementation is as follows:

```
- print the table title

- print the header row

- for each candlestick in the candlesticks vector

    - set the color of the text based on whether the close price is higher than the open price

    - print the time, open, high, low, and close prices in a row

    - reset the color to default
```

The set color and reset color features will be used again later in task 2 and task 3, thus I separated them into private member functions called `setColor` and `clearColor`. Such separation of concerns follows the DRY principle and is a good practice in object-oriented programming.

Another important detail to note is that, considering users' habits, I iterated through the candlesticks vector in reverse order. This ensures that the table displays the oldest timestamp at the top and the most recent timestamp at the bottom. I will do the same in task 2 and task 3.

### 1.5 Call the `Candlesticks` class and its member functions

Now that we have coded the `Candlesticks` class, we can instantiate a `Candlesticks` object and call its `compute` and `printTable` methods in the `printCandlesticks` function in the `MerkelMain` class. Now, when the user enters "7" in the menu, the program will print the trading statistics of the past 60 seconds in a table.

## TASK 2: Visualize the data in a candlestick chart

For task 2, my goal is to visualize the previously computed trading data in a candlestick chart. To do so, I added a new public method `printCandlestickChart` to the `Candlesticks` class.

Considering that text is displayed row by row in the console, we can break down a candlestick chart into three sections: the header at the top, the main plot (featuring y-axis labels on the left and the candlesticks on the right), and the x-axis labels at the bottom.

### 2.1 Print the header row

Since the header row will be needed again for task 3, it's better to divide it into a separate private helper function called `drawHeaderRow` and call it within the `printCandlestickChart` function. To distinguish the header rows between task 2 and task 3, I also included the y axis variable name as a parameter in the `drawHeaderRow` function and have it printed above the y-axis.

### 2.2 Print the main body

To print the main plot, I first created 4 local variables to set up its basic structure:

- `plotHeight`: the number of rows in the main body
- `highest`: maximum value on the y-axis
- `lowest`: minimum value on the y-axis
- `interval`: the interval between each row

The maximum value on the y-axis should be the highest price of all prices within the candlesticks vector. I created a helper function called `getHighestPrice` to calculate this value. Similarly, the minimum value on the y-axis should be the lowest price of all prices. I created another helper function called `getLowestPrice` to do the calculation. The interval between each row should be the difference between the maximum and minimum values divided by the plot height minus one, since, for example, there will be only 19 intervals between 20 rows.

Now that I have set up the basic structure of the plot, I can start to print the y-axis labels. Looping through the plot height, I created a local variable called `yAxisLabel`. The value of y axis label is calculated by deducting the interval from the highest value row by row. I then print the labels.

Next, in each row, to the right of the y axis label, I need to print the candlesticks. To do so, I looped through the candlesticks vector. For each candlestick, if the current y axis label is within the range of the open and close prices of the candlestick, I print a candle box. Else if the current y axis label is within the range of the high and low prices of the candlestick, I print a candle stick. Else, I print some blank space. I also made sure that the candle box, the candle stick, and the blank space are all the same width, thus everything can be vertically aligned. Of course, I also made use of the `setColor` and `clearColor` functions I coded earlier in task 1.

After I finished the prior steps, I found a new problem: because the open and close prices of a candlestick can be very close to each other, there is no y axis label within their range. I am printing a candle stick without box. This is not ideal. To solve this problem, I decided to change my strategy. I created another local variable called `yAxisLabelBelow` and set its value to the label below the current one. Instead of printing a candle box when current y axis label is within the range of the open and close prices of the candlestick, I now print a candle box when the open and close prices is within the range of the current label and the label below. In other words, instead of the open and close prices wrapping the current label, I now let the two labels wrap the open and close prices. This way, I can ensure that there will always be a candle box to print in each candlestick.

### 2.3 Print the x-axis labels

Similar to the header row, x-axis label printing functionality is divided into a separate private helper function called `drawXAxisLabels`. It will also be reused in task 3.

The x-axis variable is time. The x-axis labels should be the timestamps of the candlesticks. Since the timestamps are already stored in the candlesticks vector, we can simply iterate through the candlesticks vector and print them out. Because the timestamp strings are too long to look pretty, I also decided to refactor the `compute` class and only store a substring of the timestamp string in candlesticks vector. Instead of storing "2020-01-01 00:00:00.00000", I only store "00:00:00". I also adjusted the width of the output stream to make sure that the x-axis labels are vertically aligned with the candlesticks.

### 2.4 Call the `printCandlestickChart` function

Now that the `printCandlestickChart` function is coded, I can call it in the `printCandlesticks` function within the `MerkelMain` class to visualize the trading statistics in a candlestick chart.

## TASK 3: Visualize the trading volume in a volume bar graph

For task 3, my goal is to build upon the code I wrote for task 1 and 2 and visualize the trading volume in a volume bar graph, illustrating the total value of asks or bids of a certain product during a specific time period. The trading volume of a product and an order type at a particular timestamp is calculated by the following formula:

```
Volume = order1.price * order1.amount + order2.price * order2.amount + ... + orderN.price * orderN.amount
```

For implementation, first, I created a helper function in the `OrderBook` class called `getVolume` to perform the above calculation. The `getVolume` function takes a vector of orders as input and returns the trading volume of the orders as output.

Then, I added a new field called `volume` to the `Candlestick` structure.

Next, I edited the `compute` function in the `Candlesticks` class. Now, in each loop of calculation, it will also calculate the trading volume of all of orders of the current timestamp and store it in the `volume` field of the `Candlestick` object before pushing the `Candlestick` object to the candlesticks vector.

After that, I created a new public method called `printVolumeBars` in the `Candlesticks` class. The implementation of the `printVolumeBars` function is very similar to the `printCandlestickChart` function. It involves the same three sections: the header at the top, the main plot (featuring y-axis labels on the left and the volume bars on the right), and the x-axis labels situated at the bottom. The `drawHeaderRow`, `drawXAxisLabels`, `setColor`, and `clearColor` functions are reused here. The only difference is that, when printing the main body of the plot, for the maximum value on the y-axis, I create an additional helper function called `getHighestVolume` to calculate the maximum trading volume of all timestamps. I set the minimum value on the y-axis to 0. For volume bar printing, if the current y axis label is larger than the volume, I will print blank space. Else, I will print the volume bar.

Finally, I called the `printVolumeBars` function in the `printCandlesticks` function within the `MerkelMain` class to visualize the trading volume in a volume bar graph.

Hence, in summary, other than the constructor, the `Candlesticks` class has 4 public member functions in total: `compute`, `printTable`, `printCandlestickChart`, and `printVolumeBars`. They all works on the same member variable `std::vector<Candlestick> candlesticks` and exhibits common environment coupling. In the `printCandlesticks` function within the `MerkelMain` class, I instantiated a `Candlesticks` object first, and then called its `compute`, `printTable`, `printCandlestickChart`, and `printVolumeBars` functions in sequence to perform the computation and visualization. Such is my solution to task 1-3.

## Other changes made to the source code

In addition to the changes above, I also made some other changes to the source code to make it more clean and efficient. They are as follows:

- I refactored the source code and make functions and variables const whenever possible to avoid unexpected changes. 

- When passing objects around, I passed them by reference whenever possible to avoid unnecessary copying.

- In creating new member variables and functions, I made them private whenever possible to avoid exposing unnecessary details to the outside world. This follows the encapsulation and abstraction principles in object-oriented programming.

- I refactored the `processUserOption` function in the `MerkelMain` class. Instead of using if-else statements, I used the map function to map user input to the corresponding function. This reduces the number of lines of code and makes the code more concise and readable.

- I improved the error handling in the `processUserOption` function in the `MerkelMain` class. In the source code, if user enters a string that can be turned into an integer that is not in the menu, for example "999", the program will crash. I solved this issue with the following code:

```C++
if (menu.find(userOption) != menu.end()) {
        // process user option
    } else {
        printError();
    }
```

- I refactored the `tokenise` function in the `CSVReader` class. By turn the input string into a string stream, I can use the `getline` function to tokenize the string by a delimiter. This makes the code more concise and readable.

- In the `readCSV` function in the `CSVReader` class, I closed the file stream after reading the file. 

- In the `OrderBookEntry` class, I made the member variables private and added getter and setter functions to access and modify them. This follows the encapsulation principle in object-oriented programming.

All the additional changes made my code cleaner, more readable, more robust, and take less time to run.
