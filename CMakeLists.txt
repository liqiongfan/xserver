cmake_minimum_required(VERSION 3.13)
project(Xserver C)

set(CMAKE_C_STANDARD 99)

add_executable(
    Xserver main.c
    kernel/config.h
    kernel/net/tcp_server.c
    kernel/net/tcp_server.h
    kernel/net/tcp_server.c
    kernel/net/tcp_server.h
    kernel/tools/server_chain.c
    kernel/tools/server_chain.h
)

target_link_libraries(Xserver pthread dl)