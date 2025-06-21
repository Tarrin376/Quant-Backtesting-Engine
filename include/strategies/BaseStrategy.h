#ifndef BASE_STRATEGY_H
#define BASE_STRATEGY_H

#include <vector>
#include <cstdint>

#include "models/OpenHighLowCloseVolume.h"
#include "models/StrategySignal.h"

class BaseStrategy {
public:
    explicit BaseStrategy(std::size_t period, const char* name)
        : _period{ period }, _name{ name } {}

    const char* getName() {
        return _name;
    }

    virtual ~BaseStrategy() = default;
    
    virtual StrategySignal::Type progress(const OpenHighLowCloseVolume& bar) {
        return StrategySignal::Type::HOLD;
    }

protected:
    const char* _name{ "Base Strategy" };
    const std::size_t _period{};
    std::vector<OpenHighLowCloseVolume> _history{};
};

#endif