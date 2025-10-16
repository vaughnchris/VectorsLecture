cmake_minimum_required(VERSION 4.0)
project(ArraysLEcture)

set(CMAKE_CXX_STANDARD 20)

add_executable(ArraysLEcture main.cpp)
file(COPY ${CMAKE_SOURCE_DIR}/products.csv DESTINATION ${CMAKE_BINARY_DIR})