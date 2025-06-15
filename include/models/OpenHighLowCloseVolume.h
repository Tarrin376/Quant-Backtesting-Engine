#ifndef OPEN_HIGH_LOW_CLOSE_VOLUME_H
#define OPEN_HIGH_LOW_CLOSE_VOLUME_H

#include <string>
#include <ostream>

struct OpenHighLowCloseVolume {
    double open{};
    double high{};
    double low{};
    double close{};
    double volume{};
    
    std::string timestamp{};
    bool isHeader{ false };

    friend std::ostream& operator<<(std::ostream& out, const OpenHighLowCloseVolume& ohlcv) {
        return out << " Open: " << ohlcv.open << " High: " << ohlcv.high << " Low: " << ohlcv.low << 
        " Close: " << ohlcv.close << " Volume: " << ohlcv.volume << " Timestamp: " << ohlcv.timestamp;
    }
};

#endif