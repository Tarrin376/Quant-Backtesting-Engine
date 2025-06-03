#ifndef ENGINE_H
#define ENGINE_H

#include <string>

#include "DataFeed.h"

class Engine {
public:
    Engine(std::string& fileName);

    void run();
    
private:
    DataFeed _dataFeed;
};

#endif