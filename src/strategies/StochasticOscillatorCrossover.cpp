#include "strategies/StochasticOscillatorCrossover.h"
#include "core/Indicators.h"

StochasticOscillatorCrossover::StochasticOscillatorCrossover(std::size_t period) 
    : BaseStrategy{ period } {}

StrategySignal::Type StochasticOscillatorCrossover::progress(const OpenHighLowCloseVolume& bar) {
    _history.push_back(bar);
    if (_history.size() < _period) {
        return StrategySignal::Type::HOLD;
    }

    std::optional<Stochastic> stochasticOpt = Indicators::stochasticOscillator(_history, _period);
    if (!stochasticOpt) {
        return StrategySignal::Type::HOLD;
    }

    const Stochastic& stochastic = *stochasticOpt;
    StrategySignal::Type signal{ StrategySignal::Type::HOLD };

    if (prevPercK != -1 && prevPercK < prevPercD && stochastic.percK > stochastic.percD) {
        signal = StrategySignal::Type::BUY;
    } else if (prevPercK != -1 && prevPercK > prevPercD && stochastic.percK < stochastic.percD) {
        signal = StrategySignal::Type::SELL;
    }

    prevPercK = stochastic.percK;
    prevPercD = stochastic.percD;
    return signal;
}