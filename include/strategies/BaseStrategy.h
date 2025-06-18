#ifndef BASE_STRATEGY_H
#define BASE_STRATEGY_H

#include <vector>
#include <cstdint>

#include "models/OpenHighLowCloseVolume.h"
#include "models/StrategySignal.h"

class BaseStrategy {
public:
    explicit BaseStrategy(std::size_t period)
        : _period{ period } {}

    virtual ~BaseStrategy() = default;
    
    virtual StrategySignal::Type progress(const OpenHighLowCloseVolume& bar) {
        return StrategySignal::Type::HOLD;
    }

protected:
    const std::size_t _period{};
    std::vector<OpenHighLowCloseVolume> _history{};
};

#endif