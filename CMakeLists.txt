cmake_minimum_required(VERSION 3.0.0)
project(CodeOptimization    VERSION 1.0.0
                            DESCRIPTION "Random Cpp Stuff"
                            LANGUAGES CXX)

cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILDTYPE "Debug")
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -march=native")

find_package(OpenMP)
find_package(IPP)
find_package(MKL)
find_package(benchmark REQUIRED)

add_subdirectory(testing)
add_subdirectory(cfar)
