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
    const std::vector<Trade>& getPortfolioTradeHistory() const;
    const std::vector<Position>& getPortfolioClosedPositions() const;

private:
    static constexpr double _SLIPPAGE = 0.001;
    
    Portfolio& _portfolio;
    double _tradeCommission{};
    double _allocationPerc{};

    double calculateQuantity(double price, double volume, StrategySignal::Type type);
    constexpr double calculateSlippage(double price, StrategySignal::Type type);
};

#endif