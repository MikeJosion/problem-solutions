cmake_minimum_required(VERSION 3.16)
project(sequential C)

set(CMAKE_C_STANDARD 11)

add_executable(sequential SequentialLink.c
        main.c
        SequentialLink.h)
