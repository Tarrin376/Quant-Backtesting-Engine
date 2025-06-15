#ifndef ENGINE_H
#define ENGINE_H

#include <string>

#include "CSVReader.h"
#include "BaseStrategy.h"
#include "Portfolio.h"
#include "Broker.h"
#include "DataFeed.h"

class Engine {
public:
    Engine(DataFeed& dataFeed, BaseStrategy& strategy, Broker& broker);

    void run();
    
private:
    DataFeed& _dataFeed;
    BaseStrategy& _strategy;
    Broker& _broker;
};

#endif