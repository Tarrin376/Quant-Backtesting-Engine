#ifndef TRADE_H
#define TRADE_H

#include <string>

#include "StrategySignal.h"

struct Trade {
    StrategySignal::Type type{ StrategySignal::Type::HOLD };
    double quantity{};
    double price{};
    std::string timestamp{};
};

#endif