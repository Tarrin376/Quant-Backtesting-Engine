#include <iostream>

#include "models/OpenHighLowCloseVolume.h"
#include "models/StrategySignal.h"
#include "models/Trade.h"
#include "core/Engine.h"

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
            const StrategySignal newSignal{ .type = signalType, .price = bar.open, .volume = bar.volume };
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
}