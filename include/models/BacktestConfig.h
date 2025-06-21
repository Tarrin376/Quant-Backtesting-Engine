#ifndef BACKTEST_CONFIG_H
#define BACKTEST_CONFIG_H

#include <string>
#include <cstdint>

struct BacktestConfig {
    std::string strategyName{ "bb-mean-rev" };
    std::string fileName{};

    double tradeCommission{ 0.0 };
    double initialBalance{ 10000 };
    double allocationPerc{ 0.1 };

    int executionDelay{ 0 };
    std::size_t period{ 14 };
};

#endif