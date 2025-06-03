#include <iostream>

#include "./core/Engine.h"

int main() {
    std::string fileName{ "test.csv" };
    Engine engine{ fileName };
    engine.run();
    return 1;
}