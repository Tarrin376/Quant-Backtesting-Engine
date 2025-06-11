#ifndef BROKER_H
#define BROKER_H

#include "../models/StrategySignal.h"
#include "../models/Trade.h"

class Broker {
public:
    Broker(double tradeCommission);

    Trade processSignal(const StrategySignal &signal);

private:
    double _tradeCommission;

    int calculateTradeSize();
    double calculateSlippage(double price);
};

#endif