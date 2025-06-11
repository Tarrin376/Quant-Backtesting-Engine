#include <iostream>
#include <string>

#include "./core/Engine.h"

int main(int argc, char *argv[]) {
    std::string filename{};
    std::size_t historyWindowSize{ 1 };
    double tradeCommission{};

    for (int i{ 1 }; i + 1 < argc; ++i) {
        std::string arg{ argv[i] };

        if (arg == "-f") {
            filename = argv[++i];
        } else if (arg == "-w") {
            historyWindowSize = static_cast<std::size_t>(std::stoi(argv[++i]));
        } else if (arg == "-c") {
            tradeCommission = std::stod(argv[++i]);
        }
    }

    BaseStrategy strategy{ historyWindowSize };
    Broker broker{ tradeCommission };
    Engine engine{ filename, strategy, broker };

    engine.run();
    return 1;
}