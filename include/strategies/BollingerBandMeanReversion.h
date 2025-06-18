#ifndef BOLLINGER_BAND_MEAN_REVERSION_H
#define BOLLINGER_BAND_MEAN_REVERSION_H

#include "BaseStrategy.h"

class BollingerBandMeanReversion : public BaseStrategy {
public:
    explicit BollingerBandMeanReversion(std::size_t period);
    StrategySignal::Type progress(const OpenHighLowCloseVolume& bar) override;
};

#endif