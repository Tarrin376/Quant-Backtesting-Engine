cmake_minimum_required(VERSION 4.0.2)

project(backtesting-engine)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_SOURCE_FILES
    src/main.cpp
    src/test.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC "${SOURCE_DIR}")