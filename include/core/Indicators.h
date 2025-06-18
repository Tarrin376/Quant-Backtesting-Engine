#ifndef INDICATORS_H
#define INDICATORS_H

#include <vector>
#include <optional>
#include <cstdint>

#include "models/OpenHighLowCloseVolume.h"
#include "models/BollingerBands.h"
#include "models/Stochastic.h"

namespace Indicators {
    double simpleMovingAverage(const std::vector<OpenHighLowCloseVolume>& history, std::size_t period = 20ULL);
    std::optional<BollingerBands> bollingerBands(const std::vector<OpenHighLowCloseVolume>& history, std::size_t period = 20ULL, double stdDevMultiplier = 2);
    std::optional<Stochastic> stochasticOscillator(const std::vector<OpenHighLowCloseVolume>& history, std::size_t period = 14ULL, std::size_t d = 3ULL);
}

#endif