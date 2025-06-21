#ifndef DATA_FEED_H
#define DATA_FEED_H

#include <fstream>
#include <string>
#include <string_view>

#include "models/OpenHighLowCloseVolume.h"

class CSVReader {
public:
    explicit CSVReader(const std::string& fileName);
    
    bool next();
    bool isFirstLine();
    std::string_view getLine();

private:
    const std::string _prefix{ "../data/" };
    std::ifstream _file;
    std::string _line{};
    bool _firstLine{ true };
};

#endif