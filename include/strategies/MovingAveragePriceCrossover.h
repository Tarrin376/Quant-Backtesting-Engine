#ifndef MOVING_AVERAGE_PRICE_CROSSOVER_H
#define MOVING_AVERAGE_PRICE_CROSSOVER_H

#include "BaseStrategy.h"

class MovingAveragePriceCrossover : public BaseStrategy {
public:
    explicit MovingAveragePriceCrossover(std::size_t historyWindowSize);
    StrategySignal::Type progress(const OpenHighLowCloseVolume& bar) override;
};

#endif