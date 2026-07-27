#include "SequentialLink.h"

int main(void) {
    system("chcp 65001");
    List list;
    if (!initList(&list)) {
        printf("Init failed\n");
        return -1;
    }

    printf("=== 1. 测试插入和自动扩容 ===\n");
    // 初始容量是 10，我们要插入 15 个数，强制它扩容
    for (int i = 0; i < 15; i++) {
        insertList(&list, i * 10, list.size); // 尾插: 0, 10, 20...
    }
    printList(&list);
    // 预期输出: Size: 15, Cap: 20 (或者更多), 内容 0 到 140

    printf("\n=== 2. 测试指定位置插入 ===\n");
    insertList(&list, 999, 0); // 头插
    insertList(&list, 888, list.size); // 尾插
    insertList(&list, 777, 5); // 中间插
    printList(&list);

    printf("\n=== 3. 测试查找 ===\n");
    int index = findList(&list, 777);
    if (index != -1) {
        printf("Found 777 at index: %d\n", index);
    } else {
        printf("777 not found\n");
    }

    printf("\n=== 4. 测试删除 ===\n");
    removeList(&list, 0); // 删除头部 (999)
    printf("Removed head:\n");
    printList(&list);

    removeList(&list, list.size - 1); // 删除尾部 (888)
    printf("Removed tail:\n");
    printList(&list);

    printf("\n=== 5. 测试越界保护 ===\n");
    if (!removeList(&list, 100)) {
        printf("Correctly blocked removing index 100\n");
    }

    // 清理内存
    destroyList(&list);

    return 0;
}
