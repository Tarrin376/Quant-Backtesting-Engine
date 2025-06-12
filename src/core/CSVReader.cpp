#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "core/CSVReader.h"

const std::string CSVReader::_prefix{ "../data/" };

CSVReader::CSVReader(std::string &filename) : _file{ _prefix + filename } {};

OpenHighLowCloseVolume CSVReader::next() {
    std::string line{};

    while (std::getline(_file, line)) {
        // Skip empty lines or header line
        if (_firstLine || line.empty()) {
            _firstLine = false;
            continue;
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
        data.volume = std::stod(token);

        std::getline(ss, data.timestamp, ',');

        return data;
    }

    return OpenHighLowCloseVolume{};
}