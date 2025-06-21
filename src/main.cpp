#include <string>
#include <memory>
#include <iostream>

#include "core/Engine.h"
#include "strategies/BollingerBandMeanReversion.h"
#include "strategies/MovingAveragePriceCrossover.h"
#include "strategies/StochasticOscillatorCrossover.h"
#include "models/BacktestConfig.h"

std::unique_ptr<BaseStrategy> determineStrategy(const std::string& strategyName, std::size_t period) {
    if (strategyName == "ma-price-cross") {
        return std::make_unique<MovingAveragePriceCrossover>(period);
    } else if (strategyName == "bb-mean-rev") {
        return std::make_unique<BollingerBandMeanReversion>(period);
    } else if (strategyName == "stochastic-osc-cross") {
        return std::make_unique<StochasticOscillatorCrossover>(period);
    } else {
        return nullptr;
    }
}

int main(int argc, char* argv[]) {
    BacktestConfig config{};

    for (int i = 0; i + 1 < argc; ++i) {
        std::string arg{ argv[i] };

        if (arg == "--filename" || arg == "-f") {
            config.fileName = argv[++i];
        } else if (arg == "--commission" || arg == "-c") {
            config.tradeCommission = std::stod(argv[++i]);
        } else if (arg == "--balance" || arg == "-b") {
            config.initialBalance = std::stod(argv[++i]);
        } else if (arg == "--period" || arg == "-p") {
            config.period = static_cast<std::size_t>(std::stoi(argv[++i]));
        } else if (arg == "--allocation" || arg == "-a") {
            config.allocationPerc = std::stod(argv[++i]);
        } else if (arg == "--delay" || arg == "-d") {
            config.executionDelay = std::stoi(argv[++i]);
        } else if (arg == "--strategy" || arg == "-s") {
            config.strategyName = argv[++i];
        }
    }

    std::unique_ptr<BaseStrategy> strategy = determineStrategy(config.strategyName, config.period);
    if (!strategy) {
        std::cout << "Invalid strategy provided, terminating backtest..." << '\n';
        return 1;
    }

    CSVReader csvReader{ config.fileName };
    DataFeed dataFeed{ csvReader };

    Portfolio portfolio{ config.initialBalance };
    Broker broker{ config.tradeCommission, config.allocationPerc, portfolio };

    Engine engine{ dataFeed, *strategy, broker, config.executionDelay };
    engine.run();
    engine.logResults();
    return 1;
}