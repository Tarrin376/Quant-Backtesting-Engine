#ifndef MATH_H
#define MATH_H

#include <cmath>

namespace Math {
    constexpr inline bool isNearZero(double value) {
        return value >= -1e-8 && value <= 1e-8;
    }
}

#endif