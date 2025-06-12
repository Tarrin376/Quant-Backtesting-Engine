#include "core/BaseStrategy.h"
#include "core/Indicators.h"

StrategySignal::Type BaseStrategy::progress(const OpenHighLowCloseVolume &bar) {
    _history.push_back(bar);
    double sma = Indicators::simpleMovingAverage(_history);

    // If the bar crosses the SMA from underneath, indicates bullish market so BUY
    // If the bar crosses the SMA from above, indicates bearish market so SELL
    if (bar.open < sma && bar.close >= sma) {
        return StrategySignal::Type::BUY;
    } else if (bar.open > sma && bar.close <= sma) {
        return StrategySignal::Type::SELL;
    } else {
        return StrategySignal::Type::HOLD;
    }
}