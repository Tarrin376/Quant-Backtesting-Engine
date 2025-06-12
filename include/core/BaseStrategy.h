#ifndef BASE_STRATEGY_H
#define BASE_STRATEGY_H

#include <deque>

#include "models/OpenHighLowCloseVolume.h"
#include "models/StrategySignal.h"

class BaseStrategy {
public:
    StrategySignal::Type progress(const OpenHighLowCloseVolume &bar);

private:
    std::size_t _historyWindowSize{};
    std::deque<OpenHighLowCloseVolume> _history{};
};

#endif