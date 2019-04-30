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
    kernel/tools/list.c kernel/tools/list.h
        kernel/crypts/base64.c kernel/crypts/base64.h kernel/crypts/md5.c kernel/crypts/md5.h kernel/crypts/sha256.c kernel/crypts/sha256.h)

target_link_libraries(Xserver pthread dl)