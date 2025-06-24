#include <format>

#include "utils/Logger.h"
#include "core/Indicators.h"

void Logger::logPositions(const std::vector<Position>& positions) {
    Logger::writeCSV<Position, Position::COLUMN_COUNT>("closed_positions.csv", Position::headers, positions,
        [](const Position& p) -> const std::array<std::string, Position::COLUMN_COUNT> {
            return {
                p.getEntryTime(),
                p.getExitTime(),
                std::format("{:.2f}", p.getRealisedPnL()),
                p.getType() == Position::Type::LONG ? "Long" : "Short"
            };
        });
}

void Logger::logTrades(const std::vector<Trade>& trades) {
    Logger::writeCSV<Trade, Trade::COLUMN_COUNT>("trades.csv", Trade::headers, trades,
        [](const Trade& t) -> const std::array<std::string, Trade::COLUMN_COUNT> {
            return {
                t.type == StrategySignal::Type::BUY ? "Buy" : "Sell",
                std::format("{:.2f}", t.price),
                std::to_string(t.quantity),
                t.timestamp
            };
        });
}

void Logger::logBollingerBands(const std::vector<OpenHighLowCloseVolume>& history, const std::size_t period) {
    std::vector<OpenHighLowCloseVolume> accHistory{};
    std::vector<BollingerBands> bollingerBandsHistory{};

    for (const OpenHighLowCloseVolume& ohlc : history) {
        accHistory.emplace_back(ohlc);
        std::optional<BollingerBands> bollingerBands = Indicators::bollingerBands(accHistory, period);
        if (bollingerBands) {
            bollingerBands->timestamp = ohlc.timestamp;
            bollingerBandsHistory.push_back(*bollingerBands);
        }
    }

    Logger::writeCSV<BollingerBands, BollingerBands::COLUMN_COUNT>(
        "bollinger_bands.csv", 
        BollingerBands::headers, 
        bollingerBandsHistory,
        [](const BollingerBands& b) -> const std::array<std::string, BollingerBands::COLUMN_COUNT> {
            return {
                std::to_string(b.lower),
                std::to_string(b.middle),
                std::to_string(b.upper),
                b.timestamp
            };
        });
}