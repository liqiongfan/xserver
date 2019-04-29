cmake_minimum_required(VERSION 3.13)
project(info C)

set(CMAKE_C_STANDARD 99)

add_library(info SHARED info.c)