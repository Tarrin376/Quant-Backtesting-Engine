#include <iostream>

#include "models/OpenHighLowCloseVolume.h"
#include "models/StrategySignal.h"
#include "models/Trade.h"
#include "core/Engine.h"

Engine::Engine(DataFeed& dataFeed, BaseStrategy& strategy, Broker& broker) : 
    _dataFeed{ dataFeed },
    _strategy{ strategy },
    _broker{ broker } {}

void Engine::run() {
    OpenHighLowCloseVolume prevBar{};
    OpenHighLowCloseVolume bar{};

    StrategySignal::Type signalType{};
    int datasetSize{ 0 };

    while ((bar = _dataFeed.next()).timestamp != "") {
        if (bar.isHeader) {
            continue;
        }

        datasetSize++;
        if (signalType != StrategySignal::Type::HOLD) {
            const StrategySignal newSignal{ .type = signalType, .price = bar.open, .volume = bar.volume };
            _broker.processSignal(newSignal);
        }

        StrategySignal::Type nextSignalType{ _strategy.progress(bar) };
        signalType = nextSignalType;
        prevBar = bar;
    }

    _broker.finalise(prevBar);

    std::cout << '\n' << _broker.getPortfolioStats() << '\n'; 
    std::cout << "Dataset size: " << datasetSize << '\n';
}