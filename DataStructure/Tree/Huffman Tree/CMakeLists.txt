cmake_minimum_required(VERSION 3.16)
project(Huffman_Tree C)

set(CMAKE_C_STANDARD 11)

add_executable(Huffman_Tree main.c
        huffman.h
        huffman.c)
