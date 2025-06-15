#include "core/Indicators.h"

namespace Indicators {
    double simpleMovingAverage(std::vector<OpenHighLowCloseVolume>& history, std::size_t period) {
        std::size_t historySize{ history.size() };
        double total = 0;

        for (int i = historySize - std::min(historySize, period); i < historySize; i++) {
            total += history[i].close;
        }

        return historySize == 0 ? 0 : total / historySize;
    }
}