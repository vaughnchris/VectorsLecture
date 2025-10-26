cmake_minimum_required(VERSION 4.0)
project(FunctionsLecture)

set(CMAKE_CXX_STANDARD 20)

add_executable(FunctionsLecture main.cpp
        utilities.cpp
        utilities.h)
file(COPY ${CMAKE_SOURCE_DIR}/products.csv DESTINATION ${CMAKE_BINARY_DIR})