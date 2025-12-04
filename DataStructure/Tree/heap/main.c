#include <stdio.h>
#include "heap.h"

int main() {
    // ==========================================
    // 场景 1: 这是一个 最小堆 (Min Heap)
    // 就像 "排行榜"，分数越低越靠前
    // ==========================================
    printf("--- 测试最小堆 (Min Heap) ---\n");
    Heap* minHeap = createHeap(10, MIN_HEAP);

    int nums[] = {50, 10, 90, 30, 70, 40, 80, 20, 60};
    int n = sizeof(nums) / sizeof(nums[0]);

    printf("插入数据: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", nums[i]);
        heapPush(minHeap, nums[i]);
    }
    printf("\n");

    printf("弹出顺序 (应从小到大): ");
    while (!heapIsEmpty(minHeap)) {
        printf("%d ", heapPop(minHeap));
    }
    printf("\n\n");
    destroyHeap(minHeap);


    // ==========================================
    // 场景 2: 这是一个 最大堆 (Max Heap)
    // 就像 "大富翁"，钱越多的越靠前
    // 使用 buildHeapFromArray 快速建立
    // ==========================================
    printf("--- 测试最大堆 (Max Heap - 快速建立) ---\n");
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    // 直接把数组扔进去变成堆 (O(N) 复杂度)
    Heap* maxHeap = buildHeapFromArray(arr, size, MAX_HEAP);

    printf("原始数组: 3 1 4 1 5 9 2 6 5\n");
    printf("堆顶元素: %d (应该是 9)\n", heapPeek(maxHeap));

    printf("弹出顺序 (应从大到小): ");
    while (!heapIsEmpty(maxHeap)) {
        printf("%d ", heapPop(maxHeap));
    }
    printf("\n");
    destroyHeap(maxHeap);

    return 0;
}