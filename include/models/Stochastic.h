#ifndef STOCHASTIC_H
#define STOCHASTIC_H

#include <string>

struct Stochastic {
    static constexpr std::size_t COLUMN_COUNT{ 3 };
    static inline const std::array<std::string, COLUMN_COUNT> headers{ "%K", "%D", "Timestamp" };
    
    double percK{};
    double percD{};
    std::string timestamp{};
};

#endif