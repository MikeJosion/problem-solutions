#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int E;

typedef struct List {
    E *array;
    int capacity;
    int size;
} List;

bool initList(List *list) {
    // 建议初始容量不用给太大，测试扩容效果
    list->array = malloc(sizeof(E) * 10);
    if (list->array == NULL) return false;
    list->capacity = 10;
    list->size = 0;
    return true;
}

bool insertList(List *list, E value, int index) {
    if (index < 0 || index > list->size) return false;

    // 扩容逻辑优化
    if (list->size == list->capacity) {
        int newCapacity = list->capacity == 0 ? 10 : list->capacity * 2;
        E *temp = realloc(list->array, sizeof(E) * newCapacity);
        if (temp == NULL) return false;

        list->array = temp;
        list->capacity = newCapacity; // 成功后再改 capacity
    }

    // 【修正1】循环逻辑：从最后一位往后搬
    for (int i = list->size - 1; i >= index; i--) {
        list->array[i + 1] = list->array[i];
    }

    list->array[index] = value;
    list->size++;
    return true;
}

bool removeList(List *list, int index) {
    if (index < 0 || index >= list->size) return false;

    // 【修正2】循环条件：防止读取越界
    for (int i = index; i < list->size - 1; i++) {
        list->array[i] = list->array[i + 1];
    }

    list->size--;
    return true;
}

E getList(const List *list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Error: Index out of bounds\n");
        return -1; // 错误返回
    }
    return list->array[index];
}

int findList(const List *list, E value) {
    for (int i = 0; i < list->size; i++) {
        if (list->array[i] == value) return i;
    }
    return -1; // 【修正3】找不到返回 -1，避免和下标 0 混淆
}

void printList(const List *list) {
    printf("List (Size: %d, Cap: %d): [ ", list->size, list->capacity);
    for (int i = 0; i < list->size; i++) {
        printf("%d ", list->array[i]);
    }
    printf("]\n");
}

int sizeList(const List *list) {
    return list->size; // 【修正4】这里要返回 size
}

int capacityList(const List *list) {
    return list->capacity;
}

// 释放内存（良好的习惯）
void destroyList(List *list) {
    if (list->array != NULL) {
        free(list->array);
        list->array = NULL;
    }
    list->size = 0;
    list->capacity = 0;
}

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
