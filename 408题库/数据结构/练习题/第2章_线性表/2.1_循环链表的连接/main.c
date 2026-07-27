#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode, *LinkList;

// 创建循环链表（带头节点）
LinkList createList(int arr[], int n)
{
    LinkList head = (LinkList)malloc(sizeof(LNode));
    head->next = head;

    LNode *tail = head;

    for (int i = 0; i < n; i++)
    {
        LNode *node = (LNode *)malloc(sizeof(LNode));
        node->data = arr[i];

        node->next = head;
        tail->next = node;

        tail = node;
    }

    return head;
}

// 打印循环链表
void printList(LinkList L)
{
    LNode *p = L->next;

    while (p != L)
    {
        printf("%d ", p->data);
        p = p->next;
    }

    printf("\n");
}

// 核心算法：将循环链表 h2 连接到 h1 之后，保持循环
LinkList CircularList(LinkList h1, LinkList h2)
{
    LNode *p1 = h1->next, *p2 = h2->next;
    while (p1->next != h1)
    {
        p1 = p1->next;
    }
    while (p2->next != h2)
    {
        p2 = p2->next;
    }
    p1->next = h2->next;
    p2->next = h1;
    return h1;
}

int main()
{
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};

    LinkList h1 = createList(a, 3);
    LinkList h2 = createList(b, 3);

    printf("h1: ");
    printList(h1);

    printf("h2: ");
    printList(h2);

    CircularList(h1, h2);

    printf("连接后: ");
    printList(h1);

    return 0;
}
