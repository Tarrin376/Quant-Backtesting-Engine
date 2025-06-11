#ifndef TRADE_H
#define TRADE_H

#include <cstdint>
#include <string>

#include "StrategySignal.h"

struct Trade {
    StrategySignal::Type type{ StrategySignal::Type::HOLD };
    std::int32_t quantity{};
    double price{};
    double fee{};
    std::string timestamp{};
};

#endif