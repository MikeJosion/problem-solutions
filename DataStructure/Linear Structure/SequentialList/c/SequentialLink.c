#include "SequentialLink.h"
//初始化
bool initList(List *list) {
    list->array = malloc(sizeof(E) * 10);
    if (list->array == NULL)return false;
    list->capacity = 10;
    list->size = 0;
    return true;
}

//先判断下标,再看要不要扩容,最后插入
bool insertList(List *list, E value, int index) {
    if (index < 0 || index > list->size)return false;
    if (list->capacity == list->size) {
        //需要申请内存,是申请数组
        int newCapacity = list->capacity * 2;
        E *newArrary = realloc(list->array, sizeof(E) * newCapacity);
        //检查内存是否申请成功的判断条件不可是list->array==NULL,因为realloc申请失败原内存地址还保留
        if (newArrary == NULL)return false;
        list->array = newArrary;
        list->capacity = newCapacity;
    }
    list->array[index] = value;
    list->size++;
    return true;
}

//注意:插入与删除永远只操作： array[i] 和 array[i+1],这样可以避免下标越界的问题
bool removeList(List *list, int index) {
    if (index < 0 || index >= list->size)return false;
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
