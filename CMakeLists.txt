cmake_minimum_required(VERSION 3.13)
project(xserver)

set(CMAKE_CXX_STANDARD 11)

add_executable(xserver main.cpp kernel/parser.cpp kernel/parser.h exception/base_exception.cpp exception/base_exception.h kernel/tcp_server.cpp kernel/tcp_server.h)

target_link_libraries(xserver pthread)