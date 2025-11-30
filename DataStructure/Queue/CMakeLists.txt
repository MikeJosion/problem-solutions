cmake_minimum_required(VERSION 3.10) # 建议改回 3.x，4.0 目前还太超前了
project(Queue C)

set(CMAKE_C_STANDARD 11)

# --- 第一个程序 ---
# 生成的可执行文件名叫 ArrayQueue (或者 array_run)
# 源文件是 ArrayQueue.c
add_executable(ArrayQueue ArrayQueue.c)

# --- 第二个程序 ---
# 生成的可执行文件名叫 LinkedQueue (或者 linked_run)
# 源文件是 LinkedQueue.c
add_executable(LinkedQueue LinkedQueue.c)