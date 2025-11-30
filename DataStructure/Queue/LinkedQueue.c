#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int E;

struct Node {
    E element;
    struct Node *next;
};

typedef struct Node *Node;

struct Queue {
    Node front, rear;
};

typedef struct Queue *LinkedQueue;

//front 指针永远指着一个“没用的”头结点，它不存有效数据，只是作为队伍的“车头”。
bool initQueueLink(LinkedQueue queue) {
    Node node = malloc(sizeof(struct Node));
    if (node == NULL)return false;
    queue->rear = queue->front = node;
    // 【关键修改】把头结点的 next 指针置空！
    // 如果不加这一句，node->next 里面是垃圾值（随机地址），
    // 可能会导致遍历打印时程序崩溃。
    node->next = NULL;
    return true;
}

//尾插
//rear 的作用：rear 总是指向链表的最后一个节点。新来的人，就接在 rear 的后面，然后 rear 自己往后挪一位。
bool offerQueueLink(LinkedQueue queue, E element) {
    Node node = malloc(sizeof(struct Node));
    if (node == NULL)return false;
    node->element = element;
    //标记了“队尾”的结束 重点
    node->next = NULL;
    //把新节点挂在当前队尾后面
    queue->rear->next = node;
    // 把“队尾标签”贴到新节点上
    queue->rear = node;
    return true;
}

void printQueueLink(LinkedQueue queue) {
    if (queue == NULL) { return; }
    // 注意：从 front->next 开始，因为 front 是假人
    Node node = queue->front->next;
    while (node != NULL) {
        printf("%d -> ", node->element);
        node = node->next;
    }
    printf("NULL\n");
}

bool isEmptyLink(LinkedQueue queue) {
    return queue->front == queue->rear;
}

E pollQueueLink(LinkedQueue queue) {
    //queue->front 是虚拟头结点（火车头），它不存数据。front->next 才是当前队列里排在第一位的真正数据节点
    Node temp = queue->front->next;
    //后面返回这个要销毁的数据
    E e = temp->element;
    //将front的next连接给删除的下一个
    queue->front->next = temp->next;
    //如果删的是最后一个节点，必须把 rear 指针拉回来，让它重新指向 front（头结点）。此时 front == rear，代表队列回归由于空状态。
    if (queue->rear == temp) queue->rear = queue->front;
    free(temp);
    return e;
}

int main(void) {
    system("chcp 65001"); // 解决 Windows 中文乱码

    // 1. 创建队列实体
    struct Queue q_body;
    LinkedQueue queue = &q_body;

    // 2. 初始化
    if (initQueueLink(queue)) {
        printf("初始化成功 (Init success).\n");
    }

    // 3. 入队测试 (10, 20, 30)
    printf("\n--- Step 1: Offer 10, 20, 30 ---\n");
    offerQueueLink(queue, 10);
    offerQueueLink(queue, 20);
    offerQueueLink(queue, 30);
    printQueueLink(queue);

    // 4. 出队测试 (出两个)
    printf("\n--- Step 2: Poll 2 elements ---\n");
    printf("Polled: %d\n", pollQueueLink(queue)); // 应是 10
    printf("Polled: %d\n", pollQueueLink(queue)); // 应是 20
    printQueueLink(queue); // 应该只剩 30

    // 5. 极端测试：把最后一个也删了，测试 rear 是否归位
    printf("\n--- Step 3: Poll the last one ---\n");
    printf("Polled: %d\n", pollQueueLink(queue)); // 应是 30
    printQueueLink(queue); // 应显示 Empty

    // 此时队列已空，rear 应该已经被拉回 front 了

    // 6. 复活测试：空队之后再加数据，看会不会崩
    printf("\n--- Step 4: Offer after empty (Check rear logic) ---\n");
    offerQueueLink(queue, 100);
    offerQueueLink(queue, 200);
    printQueueLink(queue);

    return 0;
}
