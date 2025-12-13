#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// --- 1. 图结构的定义 (为了代码能运行，补充了这部分) ---
#define MaxVertex 10
typedef char E;

typedef struct Node {
    int nextVertex;
    struct Node * next;
} * Node;

struct HeadNode {
    E element;
    struct Node * next;
};

typedef struct AdjacencyGraph {
    int vertexCount;
    int edgeCount;
    struct HeadNode vertex[MaxVertex];
} * Graph;

// --- 2. 队列定义与实现 (重点修复区) ---
typedef int T;

struct QueueNode {
    T element;
    struct QueueNode * next;
};
typedef struct QueueNode * QNode;

struct Queue{
    QNode front, rear;
};
typedef struct Queue * LinkedQueue;

_Bool initQueue(LinkedQueue queue){
    QNode node = malloc(sizeof(struct QueueNode));
    if(node == NULL) return 0;
    node->next = NULL;  // 【修复 1】必须初始化 next 为 NULL，否则是野指针
    queue->front = queue->rear = node;
    return 1;
}

_Bool offerQueue(LinkedQueue queue, T element){
    QNode node = malloc(sizeof(struct QueueNode));
    if(node == NULL) return 0;
    node->element = element;
    node->next = NULL;  // 【修复 2】新节点的 next 必须指向 NULL

    queue->rear->next = node;
    queue->rear = node;
    return 1;
}

_Bool isEmpty(LinkedQueue queue){
    return queue->front == queue->rear;
}

T pollQueue(LinkedQueue queue){
    if(isEmpty(queue)) return -1; // 安全检查

    QNode topNode = queue->front->next;
    T e = topNode->element;

    queue->front->next = topNode->next;

    // 如果队列取空了，rear 需要指回 front (头结点)
    if(queue->rear == topNode) queue->rear = queue->front;

    free(topNode);
    return e;
}

// --- 3. 广度优先遍历 (BFS) ---
_Bool bfs(Graph graph, int startVertex, int targetVertex, int * visited, LinkedQueue queue) {
    offerQueue(queue, startVertex);
    visited[startVertex] = 1;

    while (!isEmpty(queue)) {
        int current = pollQueue(queue);

        // 打印当前节点
        printf("%c", graph->vertex[current].element);

        // 【优化逻辑】在出队时判断是否找到目标，这样能保证打印出 F
        if (current == targetVertex) {
            return 1;
        }
        printf(" -> "); // 如果还没找到，打印箭头

        // 遍历邻居
        Node node = graph->vertex[current].next;
        while (node) {
            if(!visited[node->nextVertex]) {
                offerQueue(queue, node->nextVertex);
                visited[node->nextVertex] = 1; // 进队时立刻标记，防止重复进队
            }
            node = node->next;
        }
    }
    return 0;
}

// 辅助函数：快速建图
Graph create(){
    Graph g = malloc(sizeof(struct AdjacencyGraph));
    g->vertexCount = 0; g->edgeCount = 0;
    return g;
}
void addVertex(Graph g, char c) {
    g->vertex[g->vertexCount].element = c;
    g->vertex[g->vertexCount].next = NULL;
    g->vertexCount++;
}
void addEdge(Graph g, int a, int b) {
    Node n = malloc(sizeof(struct Node));
    n->nextVertex = b;
    n->next = g->vertex[a].next;
    g->vertex[a].next = n;
}

int main(){
    Graph graph = create();
    for (int c = 'A'; c <= 'F' ; ++c) addVertex(graph, (char)c);

    // 构建连接 A->B->C, B->D, D->E->F
    addEdge(graph, 0, 1); // A->B
    addEdge(graph, 1, 2); // B->C
    addEdge(graph, 1, 3); // B->D
    addEdge(graph, 3, 4); // D->E
    addEdge(graph, 4, 5); // E->F

    int arr[MaxVertex] = {0}; // 初始化访问数组

    // 队列初始化
    struct Queue queue;
    if (initQueue(&queue)) {
        printf("BFS Path: ");
        if(bfs(graph, 0, 5, arr, &queue)) {
            printf("\nFound Target!\n");
        } else {
            printf("\nTarget Not Found.\n");
        }
    }
    return 0;
}