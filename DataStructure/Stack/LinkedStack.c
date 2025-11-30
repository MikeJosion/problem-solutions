#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int E;

// 定义链表节点结构体
struct ListNode {
    E element;
    struct ListNode *next;
};

// 定义 Node 为指向 struct ListNode 的指针
typedef struct ListNode *Node;

// 初始化：head 是一个指向头节点的指针
void initStackLink(Node head) {
    head->next = NULL;
}

// 入栈 (头插法)
bool pushStackLink(Node head, E element) {
    Node node = malloc(sizeof(struct ListNode)); // 创建新节点
    if (node == NULL) return false; // 内存不足

    node->element = element;
    node->next = head->next; // 新节点指向原来的第一个节点
    head->next = node;       // 头节点指向新节点
    return true;
}

// 判空
bool isEmptyLink(Node head) {
    return head->next == NULL;
}

// 出栈
E popStackLink(Node head) {
    // 【关键修复】必须先判断是否为空！
    if (isEmptyLink(head)) {
        printf("Error: Stack is empty!\n");
        return -1; // 返回错误码
    }

    Node top = head->next;       // top 指向栈顶节点
    E e = top->element;          // 取出数据
    head->next = top->next;      // 头节点跳过栈顶，指向下一个

    free(top);                   // 【重要】释放内存
    return e;
}

// 打印栈
void printStackLink(Node head) {
    printf("Stack: [Top] -> ");
    Node curr = head->next; // 从头节点的下一个开始遍历
    while (curr) {
        printf("%d -> ", curr->element);
        curr = curr->next;
    }
    printf("NULL\n");
}

// --- 测试主函数 ---
int main(void) {
    system("chcp 65001"); // 解决控制台乱码

    // 1. 创建头节点（Dummy Head）
    // 注意：这里我们在栈上创建一个实体的头节点，比较方便
    struct ListNode headNode;
    Node head = &headNode; // head 指针指向这个实体

    // 2. 初始化
    initStackLink(head);
    printf("=== 链式栈初始化完成 ===\n");

    // 3. 测试入栈
    printf("\n--- Push 测试 ---\n");
    pushStackLink(head, 10);
    pushStackLink(head, 20);
    pushStackLink(head, 30);
    printStackLink(head); // 应该是 30 -> 20 -> 10

    // 4. 测试出栈
    printf("\n--- Pop 测试 ---\n");
    printf("Pop: %d\n", popStackLink(head)); // 应该是 30
    printStackLink(head);

    printf("Pop: %d\n", popStackLink(head)); // 应该是 20
    printStackLink(head);

    // 5. 测试空栈情况
    printf("\n--- 空栈测试 ---\n");
    popStackLink(head); // 把剩下的 10 弹出来
    printStackLink(head); // 此时应该是空

    printf("尝试从空栈 Pop: ");
    E val = popStackLink(head); // 应该触发报错

    return 0;
}