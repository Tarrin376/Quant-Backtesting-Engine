#include "strategies/BollingerBandMeanReversion.h"
#include "core/Indicators.h"

BollingerBandMeanReversion::BollingerBandMeanReversion(std::size_t period) 
    : BaseStrategy{ period, "Bollinger Band Mean Reversion" } {}

StrategySignal::Type BollingerBandMeanReversion::progress(const OpenHighLowCloseVolume& bar) {
    _history.push_back(bar);
    if (_history.size() < _period) {
        return StrategySignal::Type::HOLD;
    }

    std::optional<BollingerBands> optBands = Indicators::bollingerBands(_history, _period);
    if (!optBands) {
        return StrategySignal::Type::HOLD;
    }

    const BollingerBands& bands = *optBands;
    if (bar.open > bands.lower && bar.close < bands.lower) {
        return StrategySignal::Type::BUY;
    } else if (bar.open < bands.upper && bar.close > bands.upper) {
        return StrategySignal::Type::SELL;
    } else {
        return StrategySignal::Type::HOLD;
    }
}