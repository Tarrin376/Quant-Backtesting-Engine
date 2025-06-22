#ifndef POSITION_H
#define POSITION_H

#include <deque>
#include <string>
#include <array>
#include <fstream>

#include "models/Trade.h"

class Position {
public:
    enum class Type {
        LONG,
        SHORT
    };

    Position& operator=(const Position&) = default;

    bool update(Trade& trade);
    void close(const Trade& closingTrade);

    double getSize() const;
    double getRealisedPnL() const;
    Type getType() const;

    const std::string& getEntryTime() const;
    const std::string& getExitTime() const;

    static const std::array<std::string, 4> headers;

private:
    double _size{};
    std::deque<Trade> _lots{};

    bool _closed{ false };
    double _realisedPnL{};

    std::string _entryTime{};
    std::string _exitTime{};
    Type _type{};

    bool updateRealisedPnL(Trade& trade);
};

#endif