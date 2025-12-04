cmake_minimum_required(VERSION 4.0)
project(BalancedBinaryTree C)

set(CMAKE_C_STANDARD 11)

add_executable(BalancedBinaryTree main.c
        AVL.h
        AVL.c)
