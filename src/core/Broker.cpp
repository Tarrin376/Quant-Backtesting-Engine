#include <iostream>

#include "core/Broker.h"

Broker::Broker(double tradeCommission, Portfolio &portfolio) : 
    _tradeCommission{ tradeCommission }, 
    _portfolio{ portfolio } {};

void Broker::processSignal(const StrategySignal &signal) {
    // The updated trade price after applying slippage
    double slippagePrice = calculateSlippage(signal.price);
    // Number of shares to buy/sell in this trade
    double quantity = calculateTradeQuantity(slippagePrice, signal.volume);

    Trade newTrade = Trade{ 
        .type = signal.type, 
        .quantity = quantity, 
        .price = slippagePrice, 
        .fee = _tradeCommission
    };

    _portfolio.decreaseBalance(newTrade.fee);
    // Add the trade to the trade history for this portfolio
    _portfolio._tradeHistory.push_back(newTrade);
    // Update the current position accordingly with the new trade
    _portfolio._position.update(newTrade);

    // If the position has closed, log it and create a new position
    if (_portfolio._position.isClosed()) {
        _portfolio._closedPositions.push_back(_portfolio._position);
        _portfolio.increaseBalance(_portfolio._position.getRealisedPnL());
        _portfolio._position.reset();
    }
}

double Broker::getPortfolioStats() {
    return _portfolio._currentBalance;
}

double Broker::calculateTradeQuantity(double price, double volume) {
    // Max USD you can spend: 10% of volume's notional, capped by current balance, minus commission
    double maxUSD = std::min(0.1 * volume * price, _portfolio._currentBalance) - _tradeCommission;

    // Number of shares to buy/sell in this trade
    return std::max(maxUSD / price, 0.0);
}

constexpr double Broker::calculateSlippage(double price) {
    return 1.03 * price;
}