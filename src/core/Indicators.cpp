#include "core/Indicators.h"

namespace Indicators {
    double simpleMovingAverage(std::deque<OpenHighLowCloseVolume> &history) {
        std::size_t historySize{ history.size() };
        double total = 0;

        for (OpenHighLowCloseVolume& ohlcv : history) {
            total += ohlcv.close;
        }

        return historySize == 0 ? 0 : total / historySize;
    }
}