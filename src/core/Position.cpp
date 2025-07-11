#include "core/Position.h"
#include "utils/Math.h"

const std::array<std::string, 4> Position::headers{ "Entry", "Exit", "PnL", "Type" };

bool Position::update(Trade& trade) {
    if (_entryTime.empty()) {
        _entryTime = trade.timestamp;
    }

    if (trade.type == StrategySignal::Type::BUY) {
        // If going long, increase position size by trade quantity. If going short, update realised PnL
        if (_size >= 0) {
            _lots.push_back(trade);
            _size += trade.quantity;
        } else {
            return updateRealisedPnL(trade);
        }
    } else {
        // If going short, decrease position size by trade quantity. If going long, update realised PnL
        if (_size <= 0) {
            _lots.push_back(trade);
            _size -= trade.quantity;
        } else {
            return updateRealisedPnL(trade);
        }
    }

    return false;
}

void Position::close(const Trade& closingTrade) {
    _type = closingTrade.type == StrategySignal::Type::SELL ? Type::LONG : Type::SHORT;
    _exitTime = closingTrade.timestamp;
    _closed = true;
}

bool Position::updateRealisedPnL(Trade& trade) {
    while (trade.quantity > 0 && !_lots.empty()) {
        Trade& lot = _lots.front();
        double matched = std::min(trade.quantity, lot.quantity);

        double pnl = (lot.type == StrategySignal::Type::SELL ? lot.price - trade.price : trade.price - lot.price) * matched;
        _realisedPnL += pnl;
        
        // Update position size, depending on whether it is a short or long position
        _size = (lot.type == StrategySignal::Type::SELL ? _size + matched : _size - matched);

        lot.quantity -= matched;
        trade.quantity -= matched;
        
        // If lot has been matched, remove from front of queue
        if (Math::isNearZero(lot.quantity)) {
            _lots.pop_front();
        }
    }

    return Math::isNearZero(_size);
}

double Position::getSize() const {
    return _size;
}

double Position::getRealisedPnL() const {
    return _realisedPnL;
}

Position::Type Position::getType() const {
    return _type;
}

const std::string& Position::getEntryTime() const {
    return _entryTime;
}

const std::string& Position::getExitTime() const {
    return _exitTime;
}