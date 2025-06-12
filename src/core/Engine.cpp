#include <string>
#include <array>
#include <iostream>

#include "models/OpenHighLowCloseVolume.h"
#include "models/StrategySignal.h"
#include "models/Trade.h"
#include "core/Engine.h"

Engine::Engine(std::string &filename, BaseStrategy &strategy, Broker &broker) : 
    _csvReader{ filename },
    _strategy{ strategy },
    _broker{ broker } {};

void Engine::run() {
    OpenHighLowCloseVolume bar{};
    StrategySignal::Type signalType{};

    while ((bar = _csvReader.next()).timestamp != "") {
        if (signalType != StrategySignal::Type::HOLD) {
            const StrategySignal newSignal{ .type = signalType, .price = bar.open, .volume = bar.volume };
            _broker.processSignal(newSignal);
        }

        StrategySignal::Type nextSignalType{ _strategy.progress(bar) };
        signalType = nextSignalType;
    }

    std::cout << "Current balance: " << _broker.getPortfolioStats();
}