#ifndef BROKER_H
#define BROKER_H

#include "models/StrategySignal.h"
#include "models/Trade.h"
#include "Portfolio.h"

class Broker {
public:
    Broker(double tradeCommission, Portfolio &portfolio);

    void processSignal(const StrategySignal &signal);
    double getPortfolioStats();

private:
    Portfolio &_portfolio;
    double _tradeCommission;

    double calculateTradeQuantity(double price, double volume);
    constexpr double calculateSlippage(double price);
};

#endif