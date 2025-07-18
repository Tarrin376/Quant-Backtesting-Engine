#ifndef LOGGER_H
#define LOGGER_H

#include <cstdint>
#include <vector>

#include "CSVWriter.h"
#include "models/Trade.h"
#include "models/OpenHighLowCloseVolume.h"
#include "core/Position.h"

namespace Logger {
    template <typename T, std::size_t N>
    void writeCSV(const std::string& fileName,
                  const std::array<std::string, N>& headers,
                  const std::vector<T>& data,
                  const std::function<std::array<std::string, N>(const T&)> formatter) {
        CSVWriter<T, N> writer(fileName, headers, formatter);
        for (const T& item : data) {
            writer.write(item);
        }
    }

    void logPositions(const std::vector<Position>& positions);
    void logTrades(const std::vector<Trade>& trades);
    void logBollingerBands(const std::vector<OpenHighLowCloseVolume>& history, const std::size_t period);
    void logStochastic(const std::vector<OpenHighLowCloseVolume>& history, const std::size_t period);
}

#endif