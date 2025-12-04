cmake_minimum_required(VERSION 4.0)
project(BinaryTree C)

set(CMAKE_C_STANDARD 11)

add_executable(BinaryTree BinaryTree.c
        main.c
        BinaryTree.h)
