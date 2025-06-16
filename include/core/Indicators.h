#ifndef INDICATORS_H
#define INDICATORS_H

#include <vector>
#include <optional>

#include "models/OpenHighLowCloseVolume.h"
#include "models/BollingerBands.h"
#include "models/Stochastic.h"

namespace Indicators {
    double simpleMovingAverage(const std::vector<OpenHighLowCloseVolume>& history, std::size_t period = 20);
    std::optional<BollingerBands> bollingerBands(const std::vector<OpenHighLowCloseVolume>& history, double stdDevMultiplier = 2, std::size_t period = 20);
    std::optional<Stochastic> stochasticOscillator(const std::vector<OpenHighLowCloseVolume>& history, std::size_t period = 3);
}

#endif