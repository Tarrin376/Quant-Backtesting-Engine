#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <vector>

#include "models/Trade.h"
#include "Position.h"

class Portfolio {
public:
    explicit Portfolio(double initialBalance);

    void decreaseBalance(double amount);
    void increaseBalance(double amount);

    friend class Broker;

private:
    double _initialBalance{};
    double _currentBalance{};
    
    std::vector<Trade> _tradeHistory{};
    std::vector<Position> _closedPositions{};
    Position _position{};
};

#endif