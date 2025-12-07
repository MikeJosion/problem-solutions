cmake_minimum_required(VERSION 4.0)
project(Huffman_Tree C)

set(CMAKE_C_STANDARD 11)

add_executable(Huffman_Tree main.c
        huffman.h
        huffman.c)
