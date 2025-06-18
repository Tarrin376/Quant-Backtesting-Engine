#ifndef BASE_STRATEGY_H
#define BASE_STRATEGY_H

#include <vector>

#include "models/OpenHighLowCloseVolume.h"
#include "models/StrategySignal.h"

class BaseStrategy {
public:
    explicit BaseStrategy(std::size_t historyWindowSize)
        : _historyWindowSize{ historyWindowSize } {}

    virtual ~BaseStrategy() = default;
    
    virtual StrategySignal::Type progress(const OpenHighLowCloseVolume& bar) = 0;

protected:
    const std::size_t _historyWindowSize{};
    std::vector<OpenHighLowCloseVolume> _history{};
};

#endif