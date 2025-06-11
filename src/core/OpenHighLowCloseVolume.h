#ifndef OPEN_HIGH_LOW_CLOSE_VOLUME_H
#define OPEN_HIGH_LOW_CLOSE_VOLUME_H

#include <cstdint>
#include <string>

struct OpenHighLowCloseVolume {
    double open{};
    double high{};
    double low{};
    double close{};
    std::int32_t volume{};
    std::string timestamp{};
};

std::ostream& operator<<(std::ostream &out, const OpenHighLowCloseVolume &ohlcv);

#endif