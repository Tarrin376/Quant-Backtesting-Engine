#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <vector>

#include "models/Trade.h"
#include "models/Stats.h"
#include "Position.h"

class Portfolio {
public:
    explicit Portfolio(double initialBalance);

    void recordTrade(Trade& trade);
    void decreaseBalance(double amount);
    void increaseBalance(double amount);

    double getCurrentBalance() const;
    double getPositionSize() const;
    const std::vector<Trade>& getTradeHistory() const;
    const std::vector<Position>& getClosedPositions() const;
    const Stats& getStats();

private:
    double _initialBalance{};
    double _currentBalance{};
    
    std::vector<Trade> _tradeHistory{};
    std::vector<Position> _closedPositions{};
    Position _position{};
    Stats _stats{};

    int getNumWinningPositions() const;
    int getNumLosingPositions() const;
    void closePosition(const Trade& closingTrade);
};

#endif