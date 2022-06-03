cmake_minimum_required (VERSION 3.1)

set(CMAKE_CXX_STANDARD 20)

project(httpslib)

add_executable(lib Server.cpp)