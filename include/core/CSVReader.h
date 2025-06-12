#ifndef DATA_FEED_H
#define DATA_FEED_H

#include <fstream>
#include <string>
#include <vector>

#include "models/OpenHighLowCloseVolume.h"

class CSVReader {
public:
    explicit CSVReader(std::string &filename);
    
    OpenHighLowCloseVolume next();

private:
    std::ifstream _file{};
    bool _firstLine{ true };
    static const std::string _prefix;
};

#endif