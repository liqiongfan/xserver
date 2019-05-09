cmake_minimum_required(VERSION 3.10)
project(test C)
set(CMAKE_C_STANDARD 99)

add_executable(
        test
        hashtable.c
        ../kernel/tools/hash.h
        ../kernel/tools/hashtable.c
        ../kernel/tools/hashtable.h
#        string_split.c
        ../kernel/net/tcp_server.c
        ../kernel/net/tcp_server.h
#        ../kernel/tools/string.c
#        ../kernel/tools/string.h
        ../kernel/tools/list.c
        ../kernel/tools/list.h
)