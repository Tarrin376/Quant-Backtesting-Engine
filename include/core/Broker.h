#ifndef BROKER_H
#define BROKER_H

#include "models/StrategySignal.h"
#include "models/Trade.h"
#include "models/Stats.h"
#include "Portfolio.h"

class Broker {
public:
    Broker(double tradeCommission, Portfolio& portfolio);

    void processSignal(const StrategySignal& signal);
    const Stats& getPortfolioStats();

private:
    static constexpr double _SLIPPAGE = 0.001;
    static constexpr double _VOLUME_PERC = 0.1;
    
    Portfolio& _portfolio;
    double _tradeCommission;

    double calculateTradeQuantity(double price, double volume);
    constexpr double calculateSlippage(double price, StrategySignal::Type type);
};

#endif