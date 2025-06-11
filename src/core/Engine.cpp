#include <string>
#include <array>
#include <iostream>

#include "Engine.h"
#include "OpenHighLowCloseVolume.h"
#include "../models/StrategySignal.h"

Engine::Engine(std::string &filename, BaseStrategy &strategy, Broker &broker) : 
    _dataFeed{ filename },
    _strategy{ strategy },
    _broker{ broker } {};

void Engine::run() {
    OpenHighLowCloseVolume bar{ _dataFeed.next() };
    StrategySignal::Type signalType{};

    while ((bar = _dataFeed.next()).timestamp != "") {
        if (signalType != StrategySignal::Type::HOLD) {
            const StrategySignal newSignal{ .type = signalType, .price = bar.close };
            _broker.processSignal(newSignal);
        }

        StrategySignal::Type nextSignalType = _strategy.progress(bar);
        signalType = nextSignalType;
    }
}