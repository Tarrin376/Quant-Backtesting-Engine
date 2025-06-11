#ifndef ENGINE_H
#define ENGINE_H

#include <string>

#include "DataFeed.h"
#include "../strategies/BaseStrategy.h"
#include "../broker/Broker.h"

class Engine {
public:
    Engine(std::string &filename, BaseStrategy &strategy, Broker &broker);

    void run();
    
private:
    DataFeed _dataFeed;
    BaseStrategy _strategy;
    Broker _broker;
};

#endif