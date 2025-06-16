#include "core/BaseStrategy.h"
#include "core/Indicators.h"

StrategySignal::Type BaseStrategy::progress(const OpenHighLowCloseVolume& bar) {
    _history.push_back(bar);
    double sma = Indicators::simpleMovingAverage(_history);

    if (bar.open < sma && bar.close >= sma) {
        // If the bar crosses the SMA from underneath, indicates bullish market so BUY
        return StrategySignal::Type::BUY;
    } else if (bar.open > sma && bar.close <= sma) {
        // If the bar crosses the SMA from above, indicates bearish market so SELL
        return StrategySignal::Type::SELL;
    } else {
        return StrategySignal::Type::HOLD;
    }
}