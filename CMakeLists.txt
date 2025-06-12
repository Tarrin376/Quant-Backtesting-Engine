cmake_minimum_required(VERSION 4.0.2)

project(backtesting-engine)

set(CMAKE_CXX_STANDARD 20)

#Source files
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h)

#Include directories
include_directories(include)

# Folder where the executable is stored
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include")

message(STATUS "Source files: ${SOURCES}")