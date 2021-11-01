cmake_minimum_required(VERSION 3.20)
project(csv_parser)

set(CMAKE_CXX_STANDARD 20)

add_executable(csv_parser main.cpp csv_parser.cpp csv_parser.h)

include_directories(${CURRENT_PROJECT}/include)
