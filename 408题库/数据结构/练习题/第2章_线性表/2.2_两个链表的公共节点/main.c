#include <stdio.h>
#include <stdlib.h>

typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode;

// 创建新节点
LNode *createNode(int val)
{
    LNode *node = (LNode *)malloc(sizeof(LNode));
    node->data = val;
    node->next = NULL;
    return node;
}

// 核心算法：找到两个链表的第一个公共节点
LNode *getIntersectionNode(LNode *headA, LNode *headB)
{
    if (headA == NULL || headB == NULL)
        return NULL;

    LNode *pA = headA;
    LNode *pB = headB;

    // pA 走完 A 再走 B，pB 走完 B 再走 A
    // 路程相等，必在交点或 NULL 处相遇
    while (pA != pB)
    {
        pA = (pA != NULL) ? pA->next : headB;
        pB = (pB != NULL) ? pB->next : headA;
    }

    return pA;
}

// 打印链表
void printList(LNode *head)
{
    LNode *p = head;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    // 构造相交链表：
    //   A: 1 -> 2 ─┐
    //               ├──> 6 -> 7 -> 8
    //   B: 3 -> 4 -> 5 ┘

    // 公共部分: 6 -> 7 -> 8
    LNode *c1 = createNode(6);
    LNode *c2 = createNode(7);
    LNode *c3 = createNode(8);
    c1->next = c2;
    c2->next = c3;

    // 链表 A: 1 -> 2 -> c1
    LNode *a1 = createNode(1);
    LNode *a2 = createNode(2);
    a1->next = a2;
    a2->next = c1;

    // 链表 B: 3 -> 4 -> 5 -> c1
    LNode *b1 = createNode(3);
    LNode *b2 = createNode(4);
    LNode *b3 = createNode(5);
    b1->next = b2;
    b2->next = b3;
    b3->next = c1;

    printf("链表 A: ");
    printList(a1);

    printf("链表 B: ");
    printList(b1);

    LNode *result = getIntersectionNode(a1, b1);
    if (result != NULL)
        printf("相交节点的值: %d\n", result->data);
    else
        printf("两个链表不相交\n");

    // 测试不相交的情况
    LNode *d1 = createNode(10);
    LNode *d2 = createNode(20);
    d1->next = d2;

    LNode *result2 = getIntersectionNode(a1, d1);
    if (result2 != NULL)
        printf("相交节点的值: %d\n", result2->data);
    else
        printf("两个链表不相交\n");

    return 0;
}
