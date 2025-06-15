#include <iostream>
#include <cassert>

#include "core/Broker.h"
#include "utils/Math.h"

Broker::Broker(double tradeCommission, Portfolio& portfolio) : 
    _tradeCommission{ tradeCommission }, 
    _portfolio{ portfolio } {}

void Broker::processSignal(const StrategySignal& signal) {
    // The updated trade price after applying slippage
    double slippagePrice = calculateSlippage(signal.price, signal.type);
    // Number of shares to buy/sell in this trade
    double quantity = calculateTradeQuantity(slippagePrice, signal.volume);

    if (Math::isNearZero(quantity)) {
        return;
    }

    Trade newTrade = Trade{ 
        .type = signal.type, 
        .quantity = quantity, 
        .price = slippagePrice
    };

    _portfolio.decreaseBalance(_tradeCommission);
    if (newTrade.type == StrategySignal::Type::BUY) {
        _portfolio.decreaseBalance(newTrade.quantity * newTrade.price);
    } else {
        _portfolio.increaseBalance(newTrade.quantity * newTrade.price);
    }

    _portfolio.recordTrade(newTrade);
}

const Stats& Broker::getPortfolioStats() {
    return _portfolio.getStats();
}

double Broker::calculateTradeQuantity(double price, double marketVolume) {
    assert(!Math::isNearZero(price));

    // Capital constraint: 10% of capital, minus commission
    double maxCapital = _VOLUME_PERC * _portfolio.getCurrentBalance();
    double capitalAfterCommission = std::max(0.0, maxCapital - _tradeCommission);
    double maxQtyByCapital = capitalAfterCommission / price;

    // Liquidity constraint: 10% of market volume * price, minus commission
    double maxNotionalByLiquidity = _VOLUME_PERC * marketVolume * price;
    double liquidityAfterCommission = std::max(0.0, maxNotionalByLiquidity - _tradeCommission);
    double maxQtyByLiquidity = liquidityAfterCommission / price;

    // Final quantity is minimum of both constraints
    return std::max(0.0, std::min(maxQtyByCapital, maxQtyByLiquidity));
}

constexpr double Broker::calculateSlippage(double price, StrategySignal::Type type) {
    return (type == StrategySignal::Type::BUY) ? price * (1 + _SLIPPAGE) : price * (1 - _SLIPPAGE);
}