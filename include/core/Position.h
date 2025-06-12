#ifndef POSITION_H
#define POSITION_H

#include <deque>
#include <string>

#include "models/Trade.h"

class Position {
public:
    Position();

    void update(Trade &trade);
    void reset();
    bool isClosed();
    double getRealisedPnL();

private:
    const double _EPS = 1e-8;
    int _size{};

    std::deque<Trade> _lots{};
    bool _closed{ false };
    double _realisedPnL{};

    std::string _entryTime{};
    std::string _exitTime{};
    std::string _lastUpdated{};

    void updateRealisedPnL(Trade &trade);
};

#endif