cmake_minimum_required(VERSION 3.28)
project(Stack C)

set(CMAKE_C_STANDARD 11)

# --- 只要把下面这两行分开写，问题就解决了 ---

# 第一个程序：叫 ArrayStack，只包含 Stack.c
add_executable(ArrayStack Stack.c)

# 第二个程序：叫 LinkedStack，只包含 LinkedStack.c
add_executable(LinkedStack LinkedStack.c)