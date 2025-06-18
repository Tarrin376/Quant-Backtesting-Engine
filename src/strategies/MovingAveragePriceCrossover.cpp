#include "strategies/MovingAveragePriceCrossover.h"
#include "core/Indicators.h"

MovingAveragePriceCrossover::MovingAveragePriceCrossover(std::size_t period) 
    : BaseStrategy{ period } {}

StrategySignal::Type MovingAveragePriceCrossover::progress(const OpenHighLowCloseVolume& bar) {
    _history.push_back(bar);
    if (_history.size() < _period) {
        return StrategySignal::Type::HOLD;
    }

    double sma = Indicators::simpleMovingAverage(_history, _period);
    if (bar.open < sma && bar.close > sma) {
        // If the bar crosses the SMA from underneath, indicates bullish market so BUY
        return StrategySignal::Type::BUY;
    } else if (bar.open > sma && bar.close < sma) {
        // If the bar crosses the SMA from above, indicates bearish market so SELL
        return StrategySignal::Type::SELL;
    } else {
        return StrategySignal::Type::HOLD;
    }
}