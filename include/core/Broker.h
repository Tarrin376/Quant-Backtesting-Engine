#ifndef BROKER_H
#define BROKER_H

#include "models/StrategySignal.h"
#include "models/OpenHighLowCloseVolume.h"
#include "models/Trade.h"
#include "models/Stats.h"
#include "Portfolio.h"

class Broker {
public:
    Broker(double tradeCommission, double allocationPerc, Portfolio& portfolio);

    void processSignal(const StrategySignal& signal);
    void finalise(const OpenHighLowCloseVolume& lastBar);
    const Stats& getPortfolioStats();

private:
    static constexpr double _SLIPPAGE = 0.001;
    
    Portfolio& _portfolio;
    double _tradeCommission;
    double _allocationPerc;

    double calculateTradeQuantity(double price, double volume);
    constexpr double calculateSlippage(double price, StrategySignal::Type type);
};

#endif