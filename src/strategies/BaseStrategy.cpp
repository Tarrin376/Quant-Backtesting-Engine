#include "BaseStrategy.h"
#include "../indicators/Indicators.h"

BaseStrategy::BaseStrategy(std::size_t historyWindowSize) : _historyWindowSize{ historyWindowSize } {};

StrategySignal::Type BaseStrategy::progress(const OpenHighLowCloseVolume &bar) {
    addToHistory(bar);

    double sma = Indicators::simpleMovingAverage(_history);
    if (bar.open < sma && bar.close >= sma) {
        return StrategySignal::Type::BUY;
    } else if (bar.open > sma && bar.close <= sma) {
        return StrategySignal::Type::SELL;
    } else {
        return StrategySignal::Type::HOLD;
    }
}

void BaseStrategy::addToHistory(const OpenHighLowCloseVolume &bar) {
    if (_history.size() == _historyWindowSize) {
        _history.pop_front();
    }

    _history.push_back(bar);
}