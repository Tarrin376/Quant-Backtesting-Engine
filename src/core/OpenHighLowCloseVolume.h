#ifndef OPEN_HIGH_LOW_CLOSE_VOLUME_H
#define OPEN_HIGH_LOW_CLOSE_VOLUME_H

#include <cstdint>
#include <string>

struct OpenHighLowCloseVolume {
    std::string date{};
    double close{};
    std::int32_t volume{};
    double open{};
    double high{};
    double low{};
};

std::ostream& operator<<(std::ostream &out, const OpenHighLowCloseVolume &ohlcv);

#endif