cmake_minimum_required(VERSION 3.16)
project(heap C)

set(CMAKE_C_STANDARD 11)

add_executable(heap main.c
        heap.h
        heap.c)
