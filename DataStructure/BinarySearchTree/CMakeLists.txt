cmake_minimum_required(VERSION 4.0)
project(BinarySearchTree C)

set(CMAKE_C_STANDARD 11)

add_executable(BinarySearchTree main.c
        BST.h
        BST.c)
