#ifndef POSITION_H
#define POSITION_H

#include <deque>
#include <string>
#include <ostream>

#include "models/Trade.h"

class Position {
public:
    Position& operator=(const Position&) = default;

    bool update(Trade& trade);
    double getSize() const;
    double getRealisedPnL() const;
    void close(const Trade& closingTrade);

    friend std::ostream& operator<<(std::ostream& out, const Position& position) {
        out << " Entry timestamp: " << position._entryTime << " Exit timestamp: " << position._exitTime 
        << " Realised PnL: " << position._realisedPnL << '\n';
        return out;
    }

private:
    double _size{};
    std::deque<Trade> _lots{};

    bool _closed{ false };
    double _realisedPnL{};

    std::string _entryTime{};
    std::string _exitTime{};

    bool updateRealisedPnL(Trade& trade);
};

#endif