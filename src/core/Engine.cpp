#include <iostream>
#include <format>

#include "models/OpenHighLowCloseVolume.h"
#include "models/StrategySignal.h"
#include "core/Engine.h"
#include "utils/CSVWriter.h"

Engine::Engine(DataFeed& dataFeed, BaseStrategy& strategy, Broker& broker, int executionDelay) : 
    _dataFeed{ dataFeed },
    _strategy{ strategy },
    _broker{ broker },
    _executionDelay{ executionDelay } {}

void Engine::run() {
    OpenHighLowCloseVolume prevBar{};
    OpenHighLowCloseVolume bar{};

    StrategySignal::Type signalType{ StrategySignal::Type::HOLD };
    int timeoutPeriod{ 0 };
    int datasetSize{ 0 };

    while ((bar = _dataFeed.next()).timestamp != "") {
        if (bar.isHeader) {
            continue;
        }
        
        timeoutPeriod = std::max(0, timeoutPeriod - 1);
        datasetSize++;

        if (signalType != StrategySignal::Type::HOLD && timeoutPeriod == 0) {
            const StrategySignal newSignal{ .type = signalType, .price = bar.open, .volume = bar.volume, .timestamp = bar.timestamp };
            _broker.processSignal(newSignal);
        }

        if (timeoutPeriod == 0) {
            StrategySignal::Type nextSignalType{ _strategy.progress(bar) };
            timeoutPeriod = _executionDelay + 1;
            signalType = nextSignalType;
            prevBar = bar;
        }
    }

    _broker.finalise(prevBar);

    std::cout << '\n' << _broker.getPortfolioStats() << '\n'; 
    std::cout << "Dataset size: " << datasetSize << '\n';
    std::cout << "Strategy used: " << _strategy.getName() << '\n';
}

void Engine::logResults() {
    CSVWriter<Position, Position::headers.size()> closedPositionsWriter(
        "closed_positions.csv", 
        Position::headers,
        [](const Position& position) -> const CSVWriter<Position, Position::headers.size()>::Row {
            return { 
                position.getEntryTime(), 
                position.getExitTime(), 
                std::format("{:.2f}", position.getRealisedPnL()), 
                position.getType() == Position::Type::LONG ? "Long" : "Short" 
            };
        }
    );

    for (const Position& position : _broker.getPortfolioClosedPositions()) {
        closedPositionsWriter.write(position);
    }

    CSVWriter<Trade, Trade::headers.size()> tradesWriter(
        "trades.csv",
        Trade::headers,
        [](const Trade& trade) -> const CSVWriter<Trade, Trade::headers.size()>::Row {
            return {
                trade.type == StrategySignal::Type::BUY ? "Buy" : "Sell",
                std::format("{:.2f}", trade.price),
                std::to_string(trade.quantity),
                trade.timestamp
            };
        }
    );

    for (const Trade& trade : _broker.getPortfolioTradeHistory()) {
        tradesWriter.write(trade);
    }
}