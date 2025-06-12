#ifndef ENGINE_H
#define ENGINE_H

#include <string>

#include "CSVReader.h"
#include "BaseStrategy.h"
#include "Portfolio.h"
#include "Broker.h"

class Engine {
public:
    Engine(std::string &filename, BaseStrategy &strategy, Broker &broker);

    void run();
    
private:
    CSVReader _csvReader;
    BaseStrategy _strategy;
    Broker _broker;
};

#endif