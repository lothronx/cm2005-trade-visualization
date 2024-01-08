# CM2005 Object Oriented Programming Midterm Report

Name: Yue Wu

Student Number: 210312838

My goal for the midterm assignment is to enable users to view market data of the past 60 seconds in table, candlestick chart, and volume bar graph. The user can choose to view the data of a product and order type of their choice by type in the product name and order type in this format: `productName,orderType`, for example, `BTC/USDT,bid`. To achieve this goal, I performed the three following tasks. I also made some additional changes to the source code to make the program more clean and efficient.

## TASK 1: Structure the program, compute the data, and print the table

For task 1, my goal is that given a product and order type, the program can compute its trading statistics of the past 60 seconds and print the results in a table. To do so, following the object oriented programming principle, I created a new class `Candlesticks` as well as made changes to the `OrderBook` class and `MerkelMain` class.

### 1.1 Change the program start time

Firstly, I examined the source code and noticed that the program begins with the earliest timestamp. The program then moves to the subsequent timestamp whenever the user inputs "6" and triggers the `gotoNextTimeframe` function.

The midterm instructions require students to visualize trading statistics. It would be strange to visualize statistics for "the future" since they haven't occurred yet. Therefore, I set my objective to display trading statistics from the past 60 seconds.

However, if the program started from the very first timestamp, there would be no trading history to analyze and display. To address this, I decided to have my program start from the 13th timestamp, which is 65 seconds after the earliest timestamp. (The gap between each timestamp is 5 seconds.)

In the `MerkelMain` class, I made the program start from the 13th timestamp by amending the `init` function and looping the `currentTime` member variable 12 times in the `getNextTime` function before everything else.

### 1.2 Expand the menu

In the source code, the menu has 6 options. The trading statistic visualization functionality will be the 7th option. I decided to call it `printCandlesticks`. In the `MerkelMain` class, I amended the `printMenu`, `getUserOption`, and `processUserOption` functions accordingly to include the new option.

Additionally, I refactored the `processUserOption` function. As an alternative to the if-else statements in the source code, I used the map function to map user input to the corresponding function. This reduces the number of lines of code and makes the code more concise and readable.

Also, the error handling was not robust enough in the source code. If user enters an integer that is not in the menu, for example "999", the program will crash. The map function can solve this problem by the following code:

```C++
if (menu.find(userOption) != menu.end()) {
        // process user option
    } else {
        printError();
    }
```

### 1.3 Create the `printCandlesticks` function

For step 3, I implemented the `printCandlesticks` function in the `MerkelMain` class. The structure of the `printCandlesticks` function is similar to the `enterAsk` function in the source code.

- First, it prints the instructions.
- Then, it takes user input and tokenizes it into tokens. Here, I also used regex functions to trim the leading and trailing whitespace from the tokens. This makes my program more user friendly.
- Next, I validate whether the user input is valid by checking whether the number of tokens is 2, whether the first token is a valid product name, and whether the second token is a valid order type.
- If the tokens are invalid, the program will print an error message.
- Otherwise, the program will pass the tokens along with other necessary information to initialize a `Candlesticks` object and leave the rest of the work to the `Candlesticks` class.

Encapsulating all the internal computation and visualization details in the `Candlesticks` class is a good practice of object oriented programming.

### 1.4 Code the `Candlesticks` class

For task 1, the main job of the `Candlesticks` class is to take necessary information from the outside world, calculate the trading statistics, and print the results in a table.

My considerations and decisions are as follows:

#### 1.4.1 Member variables

What outside information does the `Candlesticks` class need to perform the computation? The `Candlesticks` class needs the product name and order type to be sure. It also need to know the current time. Moreover, in order to analyze the orders of the past 60 seconds, it needs to have access to the order book. Thus, the `Candlesticks` class needs 4 constructor parameters in total: `product`, `orderType`, `timestamp`, and `orderBook`. They should be passed by reference to avoid unnecessary copying.

How should the `Candlesticks` class store the computed data? My decision is to use a vector of `Candlestick` objects. Each `Candlestick` object should store the open, close, high, and low prices of one timestamp. Since the `Candlestick` structure is simple, I decided to define it as a structure instead of a class:

```C++
struct Candlestick {
    std::string time;
    double open;
    double high;
    double low;
    double close;
};
```

Hence, the `Candlesticks` class should have 5 member variables in total. They should all be private. Other than the candlesticks vector which we will edit later, the other 4 member variables should also be constants.

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

Moreover, `compute` and `printTable` functions neither take any parameters nor return any values. Instead, they exhibits common environment coupling. This reduces interdependence and follows a good practice in object-oriented programming.

Another important detail to note is that, considering users' habits, I iterated through the candlesticks vector in reverse order. This ensures that the table displays the oldest timestamp at the top and the most recent timestamp at the bottom.

### 1.5 Call the `Candlesticks` class and its member functions

Now that we have coded the `Candlesticks` class, we can instantiate a `Candlesticks` object and call its `compute` and `printTable` methods in the `printCandlesticks` function in the `MerkelMain` class. Now, when the user enters "7" in the menu, the program will print the trading statistics of the past 60 seconds in a table.

## TASK 2: Visualize the data in a candlestick chart

For task 2, my goal is to visualize the previously computed trading data in a candlestick chart. To do so, I added a new public method `printCandlestickChart` to the `Candlesticks` class. This method is then called in the `printCandlesticks` function within the `MerkelMain` class.

Considering that text is displayed row by row in the console, we can break down a candlestick chart into three sections: the header at the top, the main plot (featuring y-axis labels on the left and the candlesticks on the right), and the x-axis labels situated at the bottom.

### 2.1 Print the header row

Since the header row will be needed again for task 3, it's better to divide it into a separate private helper function called `drawHeaderRow` and call it within the `printCandlestickChart` function. To distinguish the header rows between task 2 and task 3, I also included the y axis variable name as a parameter in the `drawHeaderRow` function and print it above the y-axis on the header row.

### 2.2 Print the main body

To print the main plot, I first created 4 local variables to set up its basic structure:

- `plotHeight`: the number of rows in the main body
- `highest`: maximum value on the y-axis
- `lowest`: minimum value on the y-axis
- `interval`: the interval between each row

The maximum value on the y-axis should be the highest price of all prices within the candlesticks vector. I created a helper function called `getHighestPrice` to calculate this value. Similarly, the minimum value on the y-axis should be the lowest price of all prices. I created another helper function called `getLowestPrice` to do the calculation. The interval between each row should be the difference between the maximum and minimum values divided by the plot height minus one, since, for example, there will be only 19 intervals between 20 rows.

Now that I have set up the basic structure of the plot, I can start to print the y-axis labels. Looping through the plot height, I created a local variable called `yAxisLabel`. The value of `yAxisLabel` is calculated by deducting the interval from the highest value row by row. I then print the labels.

Next, in each row, to the right of the y axis label, I need to print the candlesticks. To do so, I looped through the candlesticks vector. For each candlestick, if the current y axis label is within the range of the open and close prices of the candlestick, I print a candle box. Else if the current y axis label is within the range of the high and low prices of the candlestick, I print a candle stick. Else, I print some blank space. I also made sure that the candle box, the candle stick, and the blank space are all the same width, thus everything can be vertically aligned. Of course, I also made use of the `setColor` and `clearColor` functions I coded earlier in task 1.

After I finished the prior steps, I found a new problem: because the open and close prices of a candlestick can be very close to each other, there is no y axis label within their range. I am printing a candle stick without box. This is not ideal. To solve this problem, I decided to change my strategy. I created another local variable called `yAxisLabelBelow` and set its value to the label below the current one. Instead of printing a candle box when current y axis label is within the range of the open and close prices of the candlestick, I now print a candle box when the open and close prices is within the range of the current label and the label below. In other words, instead of the open and close prices wrapping the current label, I now let the two labels wrap the open and close prices. This way, I can ensure that there will always be a candle box to print in each candlestick.

### 2.3 Print the x-axis labels

Similar to the header row, x-axis label printing functionality is divided into a separate private helper function called `drawXAxisLabels`. It will also be reused in task 3.

The x-axis variable is time. The x-axis labels should be the timestamps of the candlesticks. Since the timestamps are already stored in the candlesticks vector, we can simply iterate through the candlesticks vector and print them out. Because the timestamp strings are too long to look pretty, I also decided to refactor the `compute` class and only store a substring of the timestamp string in candlesticks vector. Instead of storing "2020-01-01 00:00:00.00000", I only store "00:00:00". I also adjusted the width of the output stream to make sure that the x-axis labels are vertically aligned with the candlesticks.

## TASK 3: visualize some trading data in a volume bar graph

## Other changes made to the source code

## which aspects of your work that were challenging/ original/ creative/ exceptional.
