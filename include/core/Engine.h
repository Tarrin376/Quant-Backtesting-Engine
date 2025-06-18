#ifndef ENGINE_H
#define ENGINE_H

#include "strategies/BaseStrategy.h"
#include "CSVReader.h"
#include "Portfolio.h"
#include "Broker.h"
#include "DataFeed.h"

class Engine {
public:
    Engine(DataFeed& dataFeed, BaseStrategy& strategy, Broker& broker, int executionDelay);

    void run();
    
private:
    DataFeed& _dataFeed;
    BaseStrategy& _strategy;
    Broker& _broker;
    int _executionDelay;
};

#endif