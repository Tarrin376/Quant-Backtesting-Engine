#ifndef STRATEGY_SIGNAL_H
#define STRATEGY_SIGNAL_H

#include <cstdint>
#include <string>

struct StrategySignal {
    enum class Type {
        BUY,
        SELL,
        HOLD
    };

    Type type{ Type::HOLD };
    double price{};
    double volume{};
    std::string timestamp{};
    bool closeAll{ false };
};

#endif