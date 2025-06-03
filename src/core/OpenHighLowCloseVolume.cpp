#include <iostream>

#include "OpenHighLowCloseVolume.h"

std::ostream& operator<<(std::ostream& out, const OpenHighLowCloseVolume& ohlcv) {
    return out << " Open: " << ohlcv.open << " High: " << ohlcv.high << " Low: " << ohlcv.low << 
        " Close: " << ohlcv.close << " Volume: " << ohlcv.volume << " Date: " << ohlcv.date;
}