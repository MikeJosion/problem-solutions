#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
typedef int E;

typedef struct Node {
    E value;
    struct Node *next;
} Node; //定义了一个Node结构体类型

bool initNode(Node *node, E value) {
    node->next = NULL;
    node->value = value;
    return true;
}

bool insertNode(Node *node, E value, int index) {
    if (index < 1 || node == NULL)return false;
    while (--index) {
        if (node->next == NULL)return false;
        node = node->next;
    }
    //此时循环结束指向的是要插入位置的前面一个元素
    Node *temp = malloc(sizeof(Node));
    if (temp == NULL)return false;
    temp->value = value;
    //画图即可理解
    temp->next = node->next;
    node->next = temp;
    return true;
}

bool removeNode(Node *node, int index) {
    if (index < 1 || node == NULL)return false;
    while (--index) {
        if (node->next == NULL)return false;
        node = node->next;
    }
    if (node->next == NULL)return false;
    //注意点:node->next == NULL防止你试图去删除一个“不存在的节点”，从而导致程序崩溃
    Node *temp = node->next;
    //怎么区分Node temp与Node *temp
    //Node temp:只想要一个临时的、局部的数据容器，不需要它长期存在，也不需要把它挂到链表上时
    //Node *temp:当你想操作现有的节点（查找、删除、修改、移动指针）。想 malloc 一个新节点（malloc 返回的是地址）
    node->next = temp->next;
    free(temp);
    return true;
}

void printNode(const Node *node) {
    while (node != NULL) {
        printf("%d ", node->value);
        node = node->next;
    }
    printf("\n");
}

int sizeNode(const Node *node) {
    if (node == NULL)return 0;
    //一般false是操作失败就是存在错误,0是数量为0
    int count = 0;
    while (node != NULL) {
        count++;
        node = node->next;
    }
    return count;
}

E getNode(const Node *node, int index) {
    if (index < 1 || node == NULL)return false;
    while (--index) {
        if (node == NULL)return false;
        node = node->next;
    }
    return node->value;
}

int findNode(const Node *node, E value) {
    if (node == NULL)return -1;
    int index = 0;
    while (node != NULL) {
        if (node->value == value)return index;
        node = node->next;
        index++;
    }
    return -1;
}


int main(void) {
    system("chcp 65001");
    printf("=== 开始链表测试 ===\n");

    // 1. 初始化头节点 (Head)
    // 注意：这里我们将 head 作为链表的第一个实际数据节点
    Node head;
    initNode(&head, 100);
    printf("初始化后: ");
    printNode(&head);

    // 2. 测试插入 (Insert)
    // 在 head 后面第 1 个位置插入 200 (相当于 Head -> 200)
    insertNode(&head, 200, 1);
    // 在 head 后面第 2 个位置插入 300 (相当于 Head -> 200 -> 300)
    insertNode(&head, 300, 2);
    // 在 head 后面第 1 个位置插入 150 (相当于 Head -> 150 -> 200 -> 300)
    insertNode(&head, 150, 1);

    printf("插入数据后: ");
    printNode(&head);
    printf("当前长度: %d\n", sizeNode(&head));

    // 3. 测试查找 (Find & Get)
    int searchVal = 200;
    int idx = findNode(&head, searchVal);
    printf("查找值 %d 的索引是: %d\n", searchVal, idx);

    // 4. 测试删除 (Remove)
    printf("\n--- 测试删除 ---\n");

    // 删除第 1 个位置 (Head 后面的节点，即 150)
    printf("执行 removeNode(&head, 1) 删除 150...\n");
    if (removeNode(&head, 1)) {
        printf("删除成功: ");
        printNode(&head);
    } else {
        printf("删除失败\n");
    }

    // 删除越界位置 (例如第 10 个位置)
    printf("执行 removeNode(&head, 10) 删除越界节点...\n");
    if (removeNode(&head, 10)) {
        printf("删除成功\n");
    } else {
        printf("删除失败 (这是预期的，因为没有第 10 个节点)\n");
    }

    // 5. 最终状态
    printf("\n最终链表: ");
    printNode(&head);

    return 0;
}
