#include <string>
#include <array>
#include <iostream>

#include "Engine.h"
#include "OpenHighLowCloseVolume.h"

Engine::Engine(std::string &fileName) : _dataFeed{ fileName } {};

void Engine::run() {
    OpenHighLowCloseVolume data{ _dataFeed.next() };
    while ((data = _dataFeed.next()).volume > 0) {
        std::cout << data << '\n';
    }
}