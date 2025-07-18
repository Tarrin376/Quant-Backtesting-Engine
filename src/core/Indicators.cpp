#include <cmath>
#include <limits>
#include <iostream>

#include "core/Indicators.h"

namespace Indicators {
    double simpleMovingAverage(const std::vector<OpenHighLowCloseVolume>& history, std::size_t period) {
        std::size_t historySize{ history.size() };
        if (historySize == 0) {
            return 0.0;
        }

        std::size_t effectivePeriod = std::min(period, historySize);
        double total = 0;

        for (std::size_t i = historySize - effectivePeriod; i < historySize; ++i) {
            total += history[i].close;
        }

        return total / effectivePeriod;
    }

    std::optional<BollingerBands> bollingerBands(const std::vector<OpenHighLowCloseVolume>& history, std::size_t period, double stdDevMultiplier) {
        std::size_t historySize{ history.size() };
        if (historySize == 0) {
            return {};
        }

        std::size_t effectivePeriod = std::min(period, historySize);
        double sma = simpleMovingAverage(history, effectivePeriod);
        double variance = 0.0;

        for (std::size_t i = historySize - effectivePeriod; i < historySize; ++i) {
            double dist = history[i].close - sma;
            variance += dist * dist;
        }

        double stdDev = std::sqrt(variance / effectivePeriod);
        return BollingerBands{
            .lower = sma - stdDev * stdDevMultiplier,
            .middle = sma,
            .upper = sma + stdDev * stdDevMultiplier
        };
    }

    std::optional<Stochastic> stochasticOscillator(const std::vector<OpenHighLowCloseVolume>& history, std::size_t period, std::size_t d) {
        std::size_t historySize{ history.size() };
        if (historySize < period + d - 1) {
            return {};
        }

        double percK{};
        double percD{};
        
        for (std::size_t i = historySize - d; i < historySize; ++i) {
            double high = std::numeric_limits<double>::lowest();
            double low = std::numeric_limits<double>::max();

            for (std::size_t j = i - period + 1; j <= i; ++j) {
                high = std::max(high, history[j].high);
                low = std::min(low, history[j].low);
            }

            double curPercK = high == low ? 50.0 : (history[i].close - low) / (high - low) * 100;
            percD += curPercK;

            if (i == historySize - 1) {
                percK = curPercK;
            }
        }

        return Stochastic{ .percK = percK, .percD = percD / d };
    }
}