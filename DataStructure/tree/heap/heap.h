#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>

// 1. 定义数据类型 (方便以后改成 float 或 struct)
typedef int ElementType;

// 2. 定义堆的模式
typedef enum {
    MAX_HEAP, // 最大堆 (大顶堆)
    MIN_HEAP  // 最小堆 (小顶堆)
} HeapType;

// 3. 堆结构体
typedef struct {
    ElementType *data;  // 动态数组
    int size;           // 当前元素个数
    int capacity;       // 数组总容量
    HeapType type;      // 模式标记
} Heap;

// --- 核心功能接口 ---

// 建立空堆
Heap* createHeap(int capacity, HeapType type);

// 建立堆 (从现有数组构建，O(N)复杂度) - 这是"建立"的高级用法
Heap* buildHeapFromArray(ElementType* arr, int size, HeapType type);

// 销毁堆
void destroyHeap(Heap* heap);

// 插入元素 (Insert)
void heapPush(Heap* heap, ElementType val);

// 删除并返回堆顶元素 (Delete)
ElementType heapPop(Heap* heap);

// 查看堆顶 (不删除)
ElementType heapPeek(Heap* heap);

// 判空
bool heapIsEmpty(Heap* heap);

#endif