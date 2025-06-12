#include <cmath>

namespace Math {
    inline bool isNearZero(double value, double threshold) {
        return value >= -threshold && value <= threshold;
    }
}