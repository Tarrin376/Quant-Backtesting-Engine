#include "strategies/BollingerBandMeanReversion.h"
#include "core/Indicators.h"
#include <iostream>

BollingerBandMeanReversion::BollingerBandMeanReversion(std::size_t period) 
    : BaseStrategy{ period, "Bollinger Band Mean Reversion" } {}

StrategySignal::Type BollingerBandMeanReversion::progress(const OpenHighLowCloseVolume& bar) {
    _history.push_back(bar);
    if (_history.size() < _period + 1) {
        return StrategySignal::Type::HOLD;
    }

    std::optional<BollingerBands> optBands = Indicators::bollingerBands(_history, _period);
    const OpenHighLowCloseVolume& prevBar = _history[_history.size() - 2];

    if (!optBands) {
        return StrategySignal::Type::HOLD;
    }

    const BollingerBands& bands = *optBands;

    // Long reversion: crossed back above lower band
    if (prevBar.close < bands.lower && bar.close >= bands.lower) {
        return StrategySignal::Type::BUY;
    }

    // Short reversion: crossed back below upper band
    if (prevBar.close > bands.upper && bar.close <= bands.upper) {
        return StrategySignal::Type::SELL;
    }

    return StrategySignal::Type::HOLD;
}