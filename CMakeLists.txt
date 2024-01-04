cmake_minimum_required(VERSION 3.27)
project(code)

set(CMAKE_CXX_STANDARD 20)

# store the executables in the root directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR})

# all the files that are needed to compile the executable
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