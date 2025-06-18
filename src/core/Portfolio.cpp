#include <cassert>
#include <iostream>

#include "core/Portfolio.h"

Portfolio::Portfolio(double initialBalance) : 
    _initialBalance{ initialBalance }, 
    _currentBalance{ initialBalance } {}

void Portfolio::recordTrade(Trade& trade) {
    _tradeHistory.push_back(trade);
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
    _currentBalance += amount;
}

double Portfolio::getCurrentBalance() const {
    return _currentBalance;
}

double Portfolio::getPositionSize() const {
    return _position.getSize();
}

const Stats& Portfolio::getStats() {
    _stats.percReturn = ((_currentBalance - _initialBalance) / _initialBalance) * 100;
    _stats.initialCapital = _initialBalance;
    _stats.finalCapital = _currentBalance;
    _stats.numTrades = _tradeHistory.size();
    _stats.totalProfit = _currentBalance - _initialBalance;
    
    int winning = getNumWinningPositions();
    int losing = getNumLosingPositions();

    _stats.winningPositions = winning;
    _stats.losingPositions = losing;
    _stats.winRate = winning + losing == 0 ? 0 : (static_cast<double>(winning) / (winning + losing)) * 100;
    return _stats;
}

int Portfolio::getNumWinningPositions() const {
    int winningPositions{};

    for (const Position& position : _closedPositions) {
        if (position.getRealisedPnL() > 0) {
            winningPositions++;
        }
    }

    return winningPositions;
}

int Portfolio::getNumLosingPositions() const {
    int losingPositions{};

    for (const Position& position : _closedPositions) {
        if (position.getRealisedPnL() < 0) {
            losingPositions++;
        }
    }

    return losingPositions;
}

void Portfolio::closePosition(Trade& trade) {
    // Close position and log it in the history of closed positions
    _position.close();
    _closedPositions.push_back(_position);

    // Create a new position with the trade that contains the remaining quantity that wasn't matched
    _position = Position{};
    if (trade.quantity > 0) {
        _position.update(trade);
    }
}