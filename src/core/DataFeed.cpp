#include <sstream>
#include <string>

#include "core/DataFeed.h"

DataFeed::DataFeed(CSVReader& csvReader) : _csvReader{ csvReader } {}

OpenHighLowCloseVolume DataFeed::next() {
    if (_csvReader.isFirstLine()) {
        _csvReader.next();
        return OpenHighLowCloseVolume{ .timestamp = "N/A", .isHeader = true };
    }

    if (!_csvReader.next()) {
        return OpenHighLowCloseVolume{};
    }

    std::stringstream ss{ _csvReader.getLine().data() };
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