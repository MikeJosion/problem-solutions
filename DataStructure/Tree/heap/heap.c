#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for memcpy

// --- 内部私有函数 ---
// 核心比较器: 统一处理最大堆和最小堆的逻辑
// 如果是最大堆: 返回 a > b
// 如果是最小堆: 返回 a < b
static bool compare(ElementType a, ElementType b, HeapType type) {
    if (type == MAX_HEAP) {
        return a > b;
    } else {
        return a < b;
    }
}

static void swap(ElementType *a, ElementType *b) {
    ElementType temp = *a;
    *a = *b;
    *b = temp;
}

// 上浮 (Sift Up): 插入新元素后，如果不满足规则，往上爬
static void siftUp(Heap* heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;

        // 核心口诀: 孩子比父亲"强"，就要上位
        // "强"的定义由 compare 函数决定 (最大堆就是更大，最小堆就是更小)
        if (compare(heap->data[index], heap->data[parent], heap->type)) {
            swap(&heap->data[index], &heap->data[parent]);
            index = parent; // 继续往上查
        } else {
            break; // 满足规则了，停
        }
    }
}

// 下沉 (Sift Down): 删除堆顶后，把末尾元素放顶端，往下沉
static void siftDown(Heap* heap, int index) {
    int half = heap->size / 2; // 优化: 只有非叶子节点才需要下沉

    while (index < half) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int target = left; // 假设左孩子是我们要交换的目标

        // 如果右孩子存在，且右孩子比左孩子更"强"
        if (right < heap->size && compare(heap->data[right], heap->data[left], heap->type)) {
            target = right;
        }

        // 如果现在的节点比目标孩子还要"强" (或者一样)，说明位置对了，不用沉了
        if (compare(heap->data[index], heap->data[target], heap->type)) {
            break;
        }

        // 否则，交换，继续往下沉
        swap(&heap->data[index], &heap->data[target]);
        index = target;
    }
}

// --- 接口实现 ---

Heap* createHeap(int capacity, HeapType type) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    if (!heap) return NULL;

    heap->data = (ElementType*)malloc(sizeof(ElementType) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    heap->type = type;
    return heap;
}

// O(N) 建堆算法 (Floyd建堆法)
Heap* buildHeapFromArray(ElementType* arr, int size, HeapType type) {
    Heap* heap = createHeap(size * 2, type); // 开辟双倍空间以防万一
    if (!heap) return NULL;

    // 1. 批量拷贝数据
    memcpy(heap->data, arr, sizeof(ElementType) * size);
    heap->size = size;

    // 2. 从最后一个非叶子节点开始，倒着做下沉
    // 这是建堆最快的方法，复杂度 O(N)，比一个一个插 O(NlogN) 快
    for (int i = (size / 2) - 1; i >= 0; i--) {
        siftDown(heap, i);
    }
    return heap;
}

void destroyHeap(Heap* heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

void heapPush(Heap* heap, ElementType val) {
    if (heap->size == heap->capacity) {
        // 自动扩容 (2倍)
        heap->capacity *= 2;
        heap->data = (ElementType*)realloc(heap->data, sizeof(ElementType) * heap->capacity);
    }

    // 1. 放到最后
    heap->data[heap->size] = val;
    // 2. 上浮调整
    siftUp(heap, heap->size);
    // 3. 计数增加
    heap->size++;
}

ElementType heapPop(Heap* heap) {
    if (heapIsEmpty(heap)) {
        printf("Heap is empty!\n");
        return -1; // 错误值
    }

    ElementType top = heap->data[0];

    // 1. 拿最后一个元素补到堆顶
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    // 2. 如果还有元素，进行下沉调整
    if (heap->size > 0) {
        siftDown(heap, 0);
    }

    return top;
}

ElementType heapPeek(Heap* heap) {
    if (heapIsEmpty(heap)) return -1;
    return heap->data[0];
}

bool heapIsEmpty(Heap* heap) {
    return heap == NULL || heap->size == 0;
}