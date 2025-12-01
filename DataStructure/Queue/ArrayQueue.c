#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef int E;

struct Queue {
    E *array;
    int capacity;
    int rear, front;
};

typedef struct Queue *ArrayQueue;

bool initQueue(ArrayQueue queue) {
    queue->array = malloc(sizeof(E) * 10);
    if (queue->array == NULL)return false;
    queue->capacity = 10;
    queue->front = queue->rear = 0;
    return true;
}

//Front 永远指着“虚的”（空的）。 Rear 永远指着“实的”（刚填进去的数据）。
bool offerQueue(ArrayQueue queue, E element) {
    //判断是否满
    if ((queue->rear + 1) % queue->capacity == queue->front)return false;
    //挪位：移动队尾指针
    queue->rear = (queue->rear + 1) % queue->capacity;
    //填数据
    queue->array[queue->rear] = element;
    return true;
}

//front 一定是在第一个元素的前面
void printQueue(ArrayQueue queue) {
    if (queue == NULL || queue->rear == queue->front) { return; }
    int i = queue->front;
    while (i != queue->rear) {
        //// 先挪步（因为 front 是空的，必须先挪再打）
        i = (i + 1) % queue->capacity;
        printf("%d ", queue->array[i]);
    }
    printf("\n");
}

//不可以写queue == NULL判断,因为这是这个队列不存在 (NULL),我们判断的是队列里的元素是否为空
bool isEmpty(ArrayQueue queue) {
    return queue->rear == queue->front;
}

E pollQueue(ArrayQueue queue) {
    //% queue->capacity;每次到末尾之后传送到下标为0的位置
    queue->front = (queue->front + 1) % queue->capacity;
    return queue->array[queue->front];
}


int main(void) {
    system("chcp 65001");
    // 1. 创建队列结构体（注意：ArrayQueue只是指针，需要先有一个实体的结构体）
    struct Queue q_instance;
    ArrayQueue queue = &q_instance;

    // 2. 初始化
    if (initQueue(queue)) {
        printf("Init success.\n");
    }

    // 3. 测试空队列
    printf("Is empty? %d (Expected: 1)\n", isEmpty(queue));

    // 4. 入队测试 (填入 10, 20, 30, 40)
    printf("\n--- Offer 10, 20, 30, 40 ---\n");
    offerQueue(queue, 10);
    offerQueue(queue, 20);
    offerQueue(queue, 30);
    offerQueue(queue, 40);
    printQueue(queue); // 应输出: 10 20 30 40

    // 5. 出队测试 (出队 2 个)
    printf("\n--- Poll 2 elements ---\n");
    printf("Polled: %d\n", pollQueue(queue)); // 应输出 10
    printf("Polled: %d\n", pollQueue(queue)); // 应输出 20
    printQueue(queue); // 应输出: 30 40

    // 6. 测试循环能力 (Rear 绕回到数组开头)
    // 当前 capacity=10，最多存9个。
    // 我们继续加数据，让 rear 下标超过 9 变成 0
    printf("\n--- Offer more to trigger circular wrap ---\n");
    for (int k = 1; k <= 6; k++) {
        offerQueue(queue, k * 100); // 100, 200...
    }
    printQueue(queue);
    // 此时队列应该包含: 30 40 100 200 ...

    // 7. 测试队满
    printf("\n--- Try to fill until full ---\n");
    // 再尝试加一个，应该会报错，因为只剩一个空位了（牺牲位）
    if (!offerQueue(queue, 999)) {
        printf("Test Success: Queue blocked correctly.\n");
    }

    return 0;
}
