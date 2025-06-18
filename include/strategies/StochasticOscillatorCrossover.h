#ifndef STOCHASTIC_OSCILLATOR_CROSSOVER_H
#define STOCHASTIC_OSCILLATOR_CROSSOVER_H

#include "BaseStrategy.h"

class StochasticOscillatorCrossover : public BaseStrategy {
public:
    explicit StochasticOscillatorCrossover(std::size_t period);
    StrategySignal::Type progress(const OpenHighLowCloseVolume& bar) override;

private:
    double prevPercK{ -1 };
    double prevPercD{ -1 };
};

#endif