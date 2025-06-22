#ifndef TRADE_H
#define TRADE_H

#include <string>
#include <ostream>
#include <array>

#include "StrategySignal.h"

struct Trade {
    StrategySignal::Type type{ StrategySignal::Type::HOLD };
    static inline const std::array<std::string, 4> headers{ "Side", "Price", "Quantity", "Timestamp" };

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