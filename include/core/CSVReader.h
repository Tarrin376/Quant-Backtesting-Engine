#ifndef DATA_FEED_H
#define DATA_FEED_H

#include <fstream>
#include <string>
#include <string_view>

#include "models/OpenHighLowCloseVolume.h"

class CSVReader {
public:
    explicit CSVReader(std::string &filename);
    
    bool next();
    bool isFirstLine();
    std::string_view getLine();

private:
    std::ifstream _file{};
    std::string _line{};
    bool _firstLine{ true };
    static const std::string _prefix;
};

#endif