#ifndef DATA_FEED_H
#define DATA_FEED_H

#include <fstream>
#include <string>
#include <vector>

#include "OpenHighLowCloseVolume.h"

class DataFeed {
public:
    explicit DataFeed(std::string &fileName);
    OpenHighLowCloseVolume next();

private:
    std::ifstream _file{};
    bool _firstLine{ true };
    static const std::string _prefix;
};

#endif