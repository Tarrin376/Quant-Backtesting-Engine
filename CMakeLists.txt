cmake_minimum_required(VERSION 4.0.2)

project(backtesting-engine)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_SOURCE_FILES
    src/main.cpp
    src/core/DataFeed.cpp
    src/core/Engine.cpp
    src/core/OpenHighLowCloseVolume.cpp
    src/strategies/BaseStrategy.cpp
    src/indicators/Indicators.cpp
    src/broker/Broker.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC "${SOURCE_DIR}")