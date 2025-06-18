#include <string>

#include "core/Engine.h"
#include "strategies/MovingAveragePriceCrossover.h"

int main(int argc, char* argv[]) {
    std::string filename{};
    double tradeCommission{};

    double initialBalance{ 10000 };
    double allocationPerc{ 0.1 };
    std::size_t historyWindowSize{ 14 };

    for (int i = 0; i + 1 < argc; ++i) {
        std::string arg{ argv[i] };

        if (arg == "--filename" || arg == "-f") {
            filename = argv[++i];
        } else if (arg == "--commission" || arg == "-c") {
            tradeCommission = std::stod(argv[++i]);
        } else if (arg == "--balance" || arg == "-b") {
            initialBalance = std::stod(argv[++i]);
        } else if (arg == "--history" || arg == "-h") {
            historyWindowSize = static_cast<std::size_t>(std::stoi(argv[++i]));
        } else if (arg == "--allocation" || arg == "-a") {
            allocationPerc = std::stod(argv[++i]);
        }
    }

    CSVReader csvReader{ filename };
    DataFeed dataFeed{ csvReader };

    Portfolio portfolio{ initialBalance };
    Broker broker{ tradeCommission, allocationPerc, portfolio };
    MovingAveragePriceCrossover strategy{ historyWindowSize };

    Engine engine{ dataFeed, strategy, broker };
    engine.run();
    return 1;
}