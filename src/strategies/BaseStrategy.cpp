#include "strategies/BaseStrategy.h"

BaseStrategy::BaseStrategy(const std::size_t period, const std::string name)
    : _period{ period }, _name{ name } {}

const std::string BaseStrategy::getName() const {
    return _name;
}

const std::vector<OpenHighLowCloseVolume>& BaseStrategy::getHistory() const {
    return _history;
}

const std::size_t BaseStrategy::getPeriod() const {
    return _period;
}