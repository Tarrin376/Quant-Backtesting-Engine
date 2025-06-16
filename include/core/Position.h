#ifndef POSITION_H
#define POSITION_H

#include <deque>
#include <string>

#include "models/Trade.h"

class Position {
public:
    Position& operator=(const Position&) = default;

    bool update(Trade& trade);
    double getSize() const;
    double getRealisedPnL() const;
    void close();

private:
    double _size{};
    std::deque<Trade> _lots{};

    bool _closed{ false };
    double _realisedPnL{};

    std::string _entryTime{};
    std::string _exitTime{};
    std::string _lastUpdated{};

    bool updateRealisedPnL(Trade& trade);
};

#endif