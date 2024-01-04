cmake_minimum_required(VERSION 3.27)
project(code)

set(CMAKE_CXX_STANDARD 20)

add_executable(code main.cpp
        MerkelMain.cpp
        MerkelMain.h
        CSVReader.cpp
        CSVReader.h
        OrderBook.cpp
        OrderBook.h
        OrderBookEntry.cpp
        OrderBookEntry.h
        Wallet.cpp
        Wallet.h
        Candlesticks.cpp
        Candlesticks.h)
