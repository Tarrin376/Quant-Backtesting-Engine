#include <string>

#include "core/Engine.h"

int main(int argc, char* argv[]) {
    std::string filename{};
    double tradeCommission{};
    double initialBalance{};

    for (int i = 0; i + 1 < argc; ++i) {
        std::string arg{ argv[i] };

        if (arg == "--filename" || arg == "-f") {
            filename = argv[++i];
        } else if (arg == "--commission" || arg == "-c") {
            tradeCommission = std::stod(argv[++i]);
        } else if (arg == "--balance" || arg == "-b") {
            initialBalance = std::stod(argv[++i]);
        }
    }

    CSVReader csvReader{ filename };
    DataFeed dataFeed{ csvReader };

    Portfolio portfolio{ initialBalance };
    Broker broker{ tradeCommission, portfolio };
    BaseStrategy strategy{};

    Engine engine{ dataFeed, strategy, broker };
    engine.run();
    return 1;
}