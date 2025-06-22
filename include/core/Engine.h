#ifndef ENGINE_H
#define ENGINE_H

#include <string>

#include "strategies/BaseStrategy.h"
#include "Portfolio.h"
#include "Broker.h"
#include "DataFeed.h"

class Engine {
public:
    Engine(DataFeed& dataFeed, BaseStrategy& strategy, Broker& broker);

    void run();
    void logResults();
    
private:
    DataFeed& _dataFeed;
    BaseStrategy& _strategy;
    Broker& _broker;
};

#endif