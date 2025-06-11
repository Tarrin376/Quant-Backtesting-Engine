#include <iostream>

#include "Broker.h"

Broker::Broker(double tradeCommission) : _tradeCommission{ tradeCommission } {};

Trade Broker::processSignal(const StrategySignal &signal) {
    std::cout << "Signal Type: " << (signal.type == StrategySignal::Type::BUY ? "Buy" : signal.type == StrategySignal::Type::SELL ? "Sell" : "Hold") << " Price: " << signal.price << '\n';
    return Trade{};
}

int Broker::calculateTradeSize() {
    return 5;
}

double Broker::calculateSlippage(double price) {
    return 0.05 * price;
}