#ifndef STRATEGY_SIGNAL_H
#define STRATEGY_SIGNAL_H

struct StrategySignal {
    enum class Type {
        BUY,
        SELL,
        HOLD
    };

    Type type{ Type::HOLD };
    double price{};
};

#endif