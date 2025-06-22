#ifndef BOLLINGER_BANDS_H
#define BOLLINGER_BANDS_H

#include <string>
#include <cstdint>
#include <array>

struct BollingerBands {
    static constexpr std::size_t COLUMN_COUNT{ 4 };
    static inline const std::array<std::string, COLUMN_COUNT> headers{ "Lower", "Middle", "Upper", "Timestamp" };
    
    double lower{};
    double middle{};
    double upper{};
    std::string timestamp{};
};

#endif