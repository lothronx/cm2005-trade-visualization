# 📈 Trading Data Visualization System

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)
![Git](https://img.shields.io/badge/git-%23F05033.svg?style=for-the-badge&logo=git&logoColor=white)

> A sophisticated C++ application that processes cryptocurrency trading data and visualizes market statistics through interactive console-based charts and tables.

## 🎬 Live Demo

<div align="center">

[![Watch Demo](https://img.shields.io/badge/Watch-Demo-red?style=for-the-badge&logo=youtube)](https://www.youtube.com/watch?v=9SWZQrTzp4g&ab_channel=WuYue)

[![Watch Demo](https://img.youtube.com/vi/9SWZQrTzp4g/0.jpg)](https://www.youtube.com/watch?v=9SWZQrTzp4g&ab_channel=WuYue)

</div>

## 🎯 Project Overview

This project is a comprehensive trading data analysis system developed as part of the **CM2005 Object-Oriented Programming** course. The application processes real cryptocurrency market data (BTC/USDT) and provides users with three distinct visualization methods for analyzing trading patterns over 60-second intervals.

## ✨ Key Features

- **📊 Statistical Tables**: Display OHLC (Open, High, Low, Close) data in formatted tables
- **🕯️ Candlestick Charts**: ASCII-based candlestick visualization with color-coded indicators
- **📈 Volume Bar Charts**: Trading volume visualization showing market activity intensity
- **⚡ Real-time Analysis**: Process and analyze trading data from the past 60 seconds
- **🎨 Interactive Console UI**: User-friendly menu system with input validation

## 🛠️ Technical Skills Demonstrated

### Object-Oriented Programming Principles

- **Encapsulation**: Private data members with controlled access through public methods
- **Abstraction**: Clean interfaces hiding complex implementation details
- **Modularity**: Well-structured classes with single responsibilities
- **Code Reusability**: Helper functions and shared components across different visualizations

### Advanced C++ Techniques

- **Modern C++ Features**: Utilizing C++20 ranges, const correctness, and smart references
- **Memory Management**: Efficient pass-by-reference to avoid unnecessary copying
- **Template Usage**: Generic programming concepts for flexible data handling
- **STL Containers**: Vectors, maps, and string manipulation

### Software Engineering Best Practices

- **Error Handling**: Robust input validation and exception management
- **Code Organization**: Logical separation of concerns across multiple files
- **Performance Optimization**: Efficient algorithms for data processing
- **Documentation**: Comprehensive code comments and clear function signatures

## 🏗️ Architecture

```
├── MerkelMain          # Main application controller
├── Candlesticks        # Trading data visualization engine
├── OrderBook           # Market data management
├── OrderBookEntry      # Individual trade representation
├── CSVReader           # Data parsing utilities
├── Wallet              # Portfolio management
└── CMakeLists.txt      # Build configuration
```

### Core Classes

- **`Candlesticks`**: Processes trading data and generates three types of visualizations
- **`OrderBook`**: Manages collections of trading orders with time-based queries
- **`MerkelMain`**: Orchestrates user interactions and application flow
- **`CSVReader`**: Handles efficient parsing of market data files

## 🚀 Getting Started

### Prerequisites

- C++20 compatible compiler (GCC 10+ or Clang 10+)
- CMake 3.16+
- Trading data file (`20200601.csv`)

### Building the Project

```bash
# Clone the repository
git clone [repository-url]
cd trading-visualization-system

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make

# Run the application
./code
```

### Usage

1. **Launch Application**: Run the executable to access the main menu
2. **Select Option 7**: Choose "Print Candlesticks" from the menu
3. **Input Parameters**: Enter product and order type (e.g., `BTC/USDT,bid`)
4. **View Results**: Analyze the three generated visualizations:
   - Statistical summary table
   - ASCII candlestick chart
   - Volume bar graph

## 💡 Key Algorithms & Data Structures

- **Time Series Analysis**: Efficient backward traversal through historical data
- **Statistical Calculations**: OHLC price computation and volume aggregation
- **Visualization Algorithms**: ASCII-based chart rendering with proper scaling
- **Data Validation**: Regex-based input parsing and sanitization

## 🔧 Technical Innovations

- **Dynamic Time Navigation**: Custom `getPreviousTime()` implementation for historical data access
- **Scalable Visualization**: Adaptive chart sizing based on data ranges
- **Color-Coded Output**: Console formatting for enhanced data interpretation
- **Memory Efficient Design**: Reference-based parameter passing throughout the system

## 📈 Learning Outcomes

This project enhanced my understanding of:

- **Advanced OOP Design Patterns** and their practical applications
- **C++ Standard Library** utilization for efficient data processing
- **Algorithm Design** for time series analysis and visualization
- **Software Architecture** planning and modular development
- **Performance Optimization** through proper memory management
- **User Experience Design** in console-based applications

---

## 🤝 Connect With Me

[![LinkedIn](https://img.shields.io/badge/LinkedIn-%230077B5.svg?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/yuewuxd/)

_Developed by Yue Wu - University of London, CM2005 Object-Oriented Programming_
