#ifndef INDICATORS_H
#define INDICATORS_H

#include <deque>

#include "../core/OpenHighLowCloseVolume.h"

namespace Indicators {
    double simpleMovingAverage(std::deque<OpenHighLowCloseVolume> &history);
}

#endif