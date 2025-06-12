#ifndef TIME_H
#define TIME_H

#include <iomanip>
#include <ctime>
#include <string>

namespace Time {
    inline std::string now() {
        std::time_t now = std::time(nullptr);
        std::tm *gmt = std::gmtime(&now);

        char buf[30];
        std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", gmt);
        return std::string(buf);
    }
}

#endif