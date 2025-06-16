#ifndef STRATEGY_SIGNAL_H
#define STRATEGY_SIGNAL_H

#include <cstdint>

struct StrategySignal {
    enum class Type {
        BUY,
        SELL,
        HOLD
    };

    Type type{ Type::HOLD };
    double price{};
    double volume{};
    bool closeAll{ false };
};

#endif