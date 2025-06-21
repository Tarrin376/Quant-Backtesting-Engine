#ifndef TRADE_H
#define TRADE_H

#include <string>
#include <ostream>

#include "StrategySignal.h"

struct Trade {
    StrategySignal::Type type{ StrategySignal::Type::HOLD };
    double quantity{};
    double price{};
    std::string timestamp{};

    friend std::ostream& operator<<(std::ostream& out, const Trade& trade) {
        out << (trade.type == StrategySignal::Type::BUY ? "Buy" : "Sell") << " @ $" << trade.price 
        << " Q: " << trade.quantity << " Timestamp: " << trade.timestamp << '\n';
        return out;
    }
};

#endif