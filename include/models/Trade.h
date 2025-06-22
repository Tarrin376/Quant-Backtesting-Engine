#ifndef TRADE_H
#define TRADE_H

#include <string>
#include <ostream>
#include <array>
#include <cstdint>

#include "StrategySignal.h"

struct Trade {
    StrategySignal::Type type{ StrategySignal::Type::HOLD };
    static constexpr std::size_t COLUMN_COUNT{ 4 };
    static inline const std::array<std::string, COLUMN_COUNT> headers{ "Side", "Price", "Quantity", "Timestamp" };

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