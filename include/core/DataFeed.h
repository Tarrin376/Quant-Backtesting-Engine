#ifndef DATAFEED_H
#define DATAFEED_H

#include "CSVReader.h"
#include "models/OpenHighLowCloseVolume.h"

class DataFeed {
public:
    explicit DataFeed(CSVReader& csvReader);

    OpenHighLowCloseVolume next();

private:
    CSVReader& _csvReader;
};

#endif