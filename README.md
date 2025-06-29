# 📈 Quant Backtesting Engine (In Progress)

This project is a high-fidelity C++ backtesting engine for simulating algorithmic trading strategies on 1-minute OHLCV market data.

## 🛠 Tech Stack

- **Languages:** C++, Python
- **Build Tools:** CMake
- **APIs:** Alpaca Markets API (see here: https://alpaca.markets/)

![image](https://github.com/user-attachments/assets/eea8fe4a-571c-4a95-8052-6ee65b0ed636)

---

## 🚀 Features

- High-performance C++ backtesting engine for algorithmic trading strategies using 1-minute OHLCV data.
- Realistic trade executions using slippage, commissions, and next-bar open fills for accurate PnL simulation.
- Offers a variety of technical indicators (e.g., Moving Averages, Stochastic, Bollinger Bands) to power various trading strategies.
- Interactive visualisations for trading strategy performance analysis using Jupyter Notebook.

---

## ⚙️ Architecture Diagram

![Architecture Diagram](https://github.com/user-attachments/assets/c9658d01-45cc-4336-8a75-2eb14ee43de0)

---

## Project Structure

```
Quant-Backtesting-Engine/
├── src/                  # C++ Source files
├── include/              # C++ Header files
├── python_scripts/       # Python scripts for constructing backtesting data and strategy performance visualisation
├── data/                 # Market data files should be stored here for backtesting
├── bin/                  # Compiled executable (generated)
├── build/                # Build files (generated)
├── CMakeLists.txt        # CMake build configuration
└── README.md             # This file
```

## 🛠️ Getting Started

### Backtesting Engine setup

#### 1. Clone the Repository
```bash
> git clone https://github.com/Tarrin376/Quant-Backtesting-Engine.git && cd Quant-Backtesting-Engine
```

#### 2. Create a build directory and move to it
```bash
> mkdir build
> cd build
```

#### 3. Build executable with CMake (the executable will be generated in the /bin directory)
```bash
> cmake ..
> cmake --build .
```

#### 4. Run the backtesting-engine executable
```bash
> cd ../bin
> ./backtesting-engine.exe
```

You should see the following output:
```bash
===== Backtest Statistics =====
Initial Capital     : $10000.00
Final Capital       : $10000.00
Final Profit/Loss   : $0.00
Percentage Return   : 0.00%
Number of Trades    : 0
Win Rate            : 0.00%
Winning Positions   : 0
Losing Positions    : 0
===============================

Dataset size: 0
Strategy used: Bollinger Band Mean Reversion
```



This is expected, as we haven't specified any backtesting data file to use in the /data directory.
