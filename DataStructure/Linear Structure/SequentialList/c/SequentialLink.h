#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int E;

typedef struct List {
    E *array;
    int capacity;
    int size;
} List;

bool initList(List *list);

bool insertList(List *list, E value, int index);

bool removeList(List *list, int index);

E getList(const List *list, int index);

int findList(const List *list, E value);

void printList(const List *list);

int sizeList(const List *list);

int capacityList(const List *list);

void destroyList(List *list);
