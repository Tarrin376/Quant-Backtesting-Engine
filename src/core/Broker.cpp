#include <cassert>

#include "core/Broker.h"
#include "utils/Math.h"

Broker::Broker(double tradeCommission, double allocationPerc, Portfolio& portfolio) : 
    _tradeCommission{ tradeCommission },
    _allocationPerc{ allocationPerc },
    _portfolio{ portfolio } {}

void Broker::processSignal(const StrategySignal& signal) {
    // The updated trade price after applying slippage
    double slippagePrice = calculateSlippage(signal.price, signal.type);
    // Number of shares to buy/sell in this trade
    double quantity = signal.closeAll ? std::abs(_portfolio.getPositionSize()) : calculateQuantity(slippagePrice, signal.volume, signal.type);

    if (Math::isNearZero(quantity)) {
        return;
    }

    Trade newTrade = Trade{ 
        .type = signal.type, 
        .quantity = quantity, 
        .price = slippagePrice,
        .timestamp = signal.timestamp
    };

    _portfolio.decreaseBalance(_tradeCommission);
    if (newTrade.type == StrategySignal::Type::BUY) {
        _portfolio.decreaseBalance(newTrade.quantity * newTrade.price);
    } else {
        _portfolio.increaseBalance(newTrade.quantity * newTrade.price);
    }

    _portfolio.recordTrade(newTrade);
}

void Broker::finalise(const OpenHighLowCloseVolume& lastBar) {
    if (Math::isNearZero(_portfolio.getPositionSize())) {
        return;
    }

    StrategySignal exitSignal = {
        .type = _portfolio.getPositionSize() > 0 ? StrategySignal::Type::SELL : StrategySignal::Type::BUY,
        .price = lastBar.close,
        .closeAll = true
    };

    processSignal(exitSignal);
}

const Stats& Broker::getPortfolioStats() {
    return _portfolio.getStats();
}

double Broker::calculateQuantity(double price, double marketVolume, StrategySignal::Type type) {
    assert(!Math::isNearZero(price));

    double maxNotionalByCapital = _allocationPerc * _portfolio.getCurrentBalance();
    double capitalAfterCommission = std::max(0.0, maxNotionalByCapital - _tradeCommission);
    double maxQtyByCapital = capitalAfterCommission / price;

    double maxNotionalByLiquidity = _allocationPerc * marketVolume * price;
    double liquidityAfterCommission = std::max(0.0, maxNotionalByLiquidity - _tradeCommission);
    double maxQtyByLiquidity = liquidityAfterCommission / price;

    double positionSize = _portfolio.getPositionSize();

    if (type == StrategySignal::Type::SELL) {
        // If long, close long. If short, increase short
        if (positionSize > 0) {
            // Sell up to position size to close long
            return std::max(0.0, std::min(positionSize, maxQtyByLiquidity));
        } else {
            // Add to short
            return std::max(0.0, std::min(maxQtyByCapital, maxQtyByLiquidity));
        }
    } else {
        if (positionSize < 0) {
            // Buy to close short
            return std::max(0.0, std::min(std::abs(positionSize), maxQtyByLiquidity));
        } else {
            // Add to long
            return std::max(0.0, std::min(maxQtyByCapital, maxQtyByLiquidity));
        }
    }
}

constexpr double Broker::calculateSlippage(double price, StrategySignal::Type type) {
    return (type == StrategySignal::Type::BUY) ? price * (1 + _SLIPPAGE) : price * (1 - _SLIPPAGE);
}