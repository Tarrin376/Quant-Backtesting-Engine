#include <format>

#include "utils/Logger.h"

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