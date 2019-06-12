cmake_minimum_required(VERSION 3.14)
project(breakout)

set(CMAKE_CXX_STANDARD 14)


find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(breakout  main.cpp map.h)

target_link_libraries(breakout sfml-graphics sfml-audio)
