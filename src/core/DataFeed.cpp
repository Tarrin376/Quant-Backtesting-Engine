#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "DataFeed.h"

const std::string DataFeed::_prefix{ "../data/" };

DataFeed::DataFeed(std::string &filename) : _file{ _prefix + filename } {};

OpenHighLowCloseVolume DataFeed::next() {
    std::string line{};
    if (!std::getline(_file, line) || _firstLine) {
        _firstLine = false;
        return OpenHighLowCloseVolume{};
    }

    std::stringstream ss{ line };
    std::string token{};

    OpenHighLowCloseVolume data{};

    std::getline(ss, token, ',');
    data.open = std::stod(token);

    std::getline(ss, token, ',');
    data.high = std::stod(token);

    std::getline(ss, token, ',');
    data.low = std::stod(token);

    std::getline(ss, token, ',');
    data.close = std::stod(token);

    std::getline(ss, token, ',');
    data.volume = std::stol(token);

    std::getline(ss, data.timestamp, ',');

    return data;
}