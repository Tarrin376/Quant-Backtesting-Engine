#ifndef INDICATORS_H
#define INDICATORS_H

#include <vector>

#include "models/OpenHighLowCloseVolume.h"

namespace Indicators {
    double simpleMovingAverage(std::vector<OpenHighLowCloseVolume>& history, std::size_t period);
}

#endif