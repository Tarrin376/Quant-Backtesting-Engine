#include "utils/CSVReader.h"

CSVReader::CSVReader(const std::string& fileName) 
    : _file{ _prefix + fileName } {}

bool CSVReader::next() {
    bool readSuccess = !std::getline(_file, _line).fail();
    if (_firstLine) {
        _firstLine = false;
    }

    return readSuccess;
}

bool CSVReader::isFirstLine() {
    return _firstLine;
}

std::string_view CSVReader::getLine() {
    return _line;
}