#include "core/CSVReader.h"

const std::string CSVReader::_prefix{ "../data/" };

CSVReader::CSVReader(std::string& filename) : _file{ _prefix + filename } {}

std::string_view CSVReader::getLine() {
    return _line;
}

bool CSVReader::isFirstLine() {
    return _firstLine;
}

bool CSVReader::next() {
    bool readSuccess = !std::getline(_file, _line).fail();
    if (_firstLine) {
        _firstLine = false;
    }

    return readSuccess;
}