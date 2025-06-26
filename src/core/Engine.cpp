#include <iostream>

#include "models/OpenHighLowCloseVolume.h"
#include "models/StrategySignal.h"
#include "core/Engine.h"
#include "utils/Logger.h"

Engine::Engine(DataFeed& dataFeed, BaseStrategy& strategy, Broker& broker) : 
    _dataFeed{ dataFeed },
    _strategy{ strategy },
    _broker{ broker } {}

void Engine::run() {
    OpenHighLowCloseVolume prevBar{};
    OpenHighLowCloseVolume bar{};

    StrategySignal::Type signalType{ StrategySignal::Type::HOLD };
    int datasetSize{ 0 };

    while ((bar = _dataFeed.next()).timestamp != "") {
        if (bar.isHeader) {
            continue;
        }
        
        datasetSize++;
        if (signalType != StrategySignal::Type::HOLD) {
            const StrategySignal newSignal{ .type = signalType, .price = bar.open, .volume = bar.volume, .timestamp = bar.timestamp };
            _broker.processSignal(newSignal);
        }

        StrategySignal::Type nextSignalType{ _strategy.progress(bar) };
        signalType = nextSignalType;
        prevBar = bar;
    }

    _broker.finalise(prevBar);

    std::cout << '\n' << _broker.getPortfolioStats() << '\n'; 
    std::cout << "Dataset size: " << datasetSize << '\n';
    std::cout << "Strategy used: " << _strategy.getName() << '\n';
}

void Engine::logResults() {
    Logger::logPositions(_broker.getPortfolioClosedPositions());
    Logger::logTrades(_broker.getPortfolioTradeHistory());
    Logger::logBollingerBands(_strategy.getHistory(), _strategy.getPeriod());
    Logger::logStochastic(_strategy.getHistory(), _strategy.getPeriod());
}