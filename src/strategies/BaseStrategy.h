#ifndef BASE_STRATEGY_H
#define BASE_STRATEGY_H

#include <deque>

#include "../core/OpenHighLowCloseVolume.h"
#include "../models/StrategySignal.h"

class BaseStrategy {
public:
    explicit BaseStrategy(std::size_t historyWindowSize);

    StrategySignal::Type progress(const OpenHighLowCloseVolume &bar);

private:
    std::size_t _historyWindowSize{};
    std::deque<OpenHighLowCloseVolume> _history{};

    void addToHistory(const OpenHighLowCloseVolume &bar);
};

#endif