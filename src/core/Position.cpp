#include "core/Position.h"
#include "utils/Math.h"

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

double Position::getSize() const {
    return _size;
}

double Position::getRealisedPnL() const {
    return _realisedPnL;
}

void Position::close() {
    _exitTime = _lots.back().timestamp;
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