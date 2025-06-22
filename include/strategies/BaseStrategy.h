#ifndef BASE_STRATEGY_H
#define BASE_STRATEGY_H

#include <vector>
#include <cstdint>
#include <string>

#include "models/OpenHighLowCloseVolume.h"
#include "models/StrategySignal.h"

class BaseStrategy {
public:
    BaseStrategy(const std::size_t period, const std::string name);

    const std::string getName() const;
    const std::vector<OpenHighLowCloseVolume>& getHistory() const;
    const std::size_t getPeriod() const;

    virtual ~BaseStrategy() = default;
    
    virtual StrategySignal::Type progress(const OpenHighLowCloseVolume& bar) {
        return StrategySignal::Type::HOLD;
    }

protected:
    const std::string _name{ "Base Strategy" };
    const std::size_t _period{};
    std::vector<OpenHighLowCloseVolume> _history{};
};

#endif