#include <cassert>

#include "core/Portfolio.h"

Portfolio::Portfolio(double initialBalance) : 
    _initialBalance{ initialBalance }, 
    _currentBalance{ initialBalance } {}

void Portfolio::recordTrade(Trade& trade) {
    _tradeHistory.push_back(trade);
    // Update the current position accordingly with the new trade
    bool close = _position.update(trade);
    
    // If the position is ready to close, close it
    if (close) {
        closePosition(trade);
    }
}

void Portfolio::decreaseBalance(double amount) {
    assert(amount >= 0);
    _currentBalance -= std::min(_currentBalance, amount);
}

void Portfolio::increaseBalance(double amount) {
    assert(amount >= 0);
    _currentBalance += std::max(0.0, amount);
}

double Portfolio::getCurrentBalance() {
    return _currentBalance;
}

const Stats& Portfolio::getStats() {
    _stats.initialCapital = _initialBalance;
    _stats.finalCapital = _currentBalance;
    _stats.numTrades = _tradeHistory.size();
    _stats.percReturn = ((_currentBalance - _initialBalance) / _initialBalance) * 100;
    _stats.totalProfit = (_currentBalance - _initialBalance);
    return _stats;
}

void Portfolio::closePosition(Trade& trade) {
    // Close position and log it in the history of closed positions
    _position.close();
    _closedPositions.push_back(_position);

    // Create a new position with the trade that contains the remaining quantity that wasn't matched
    _position = Position{};
    _position.update(trade);
}