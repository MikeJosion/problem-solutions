#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxVertex 10

typedef char E;

typedef struct Node {
    int nextVertex;
    struct Node *next;
} *Node;

struct HeadNode {
    E element;
    struct Node *next;
};

typedef struct AdjacencyGraph {
    int vertexCount;
    int edgeCount;
    struct HeadNode vertex[MaxVertex];
} *Graph;

Graph create() {
    Graph graph = malloc(sizeof(struct AdjacencyGraph));
    graph->vertexCount = graph->edgeCount = 0;
    return graph;
}

void addVertex(Graph graph, E element) {
    if (graph->vertexCount >= MaxVertex) return;
    graph->vertex[graph->vertexCount].element = element;
    graph->vertex[graph->vertexCount].next = NULL;
    graph->vertexCount++;
}

void addEdge(Graph graph, int a, int b) {
    // 安全检查：防止下标越界
    if (a >= graph->vertexCount || b >= graph->vertexCount) return;

    Node node = graph->vertex[a].next;
    Node newNode = malloc(sizeof(struct Node));
    newNode->next = NULL;
    newNode->nextVertex = b;
    if (!node) {
        graph->vertex[a].next = newNode;
    } else {
        do {
            if (node->nextVertex == b) {
                // 防止重复添加边
                free(newNode);
                return;
            }
            if (node->next) node = node->next;
            else break;
        } while (1);
        node->next = newNode;
    }
    graph->edgeCount++;
}

void printGraph(Graph graph) {
    printf("--- Graph Structure ---\n");
    for (int i = 0; i < graph->vertexCount; ++i) {
        printf("%d [%c]", i, graph->vertex[i].element);
        Node node = graph->vertex[i].next;
        while (node) {
            printf(" -> %d", node->nextVertex);
            node = node->next;
        }
        putchar('\n');
    }
    printf("-----------------------\n");
}

// [Image of adjacency list diagram]

// 【修正2】删除了原来的 void dfs，保留这个带返回值的版本
// 为了兼容性，使用 int 或者 bool 都可以，这里用 _Bool 没问题
bool dfs(Graph graph, int startVertex, int targetVertex, int *visited) {
    visited[startVertex] = 1;
    printf("%c -> ", graph->vertex[startVertex].element);

    if (startVertex == targetVertex) return 1; // 找到目标，返回真

    Node node = graph->vertex[startVertex].next;
    while (node) {
        if (!visited[node->nextVertex]) {
            // 递归查找，如果下层返回1，说明找到了，直接向上层返回1
            if (dfs(graph, node->nextVertex, targetVertex, visited))
                return 1;
        }
        node = node->next;
    }
    return 0; // 找遍了所有分支都没找到
}

int main() {
    Graph graph = create();
    // 插入 A, B, C, D, E, F
    for (int c = 'A'; c <= 'F'; ++c)
        addVertex(graph, (char) c);

    // 0:A, 1:B, 2:C, 3:D, 4:E, 5:F
    addEdge(graph, 0, 1); // A -> B
    addEdge(graph, 1, 2); // B -> C
    addEdge(graph, 1, 3); // B -> D

    // 如果你想让 A 能走到 F，必须把路连通。
    // 假设路径是 A->B->D->E->F，则：
    addEdge(graph, 3, 4); // D -> E
    addEdge(graph, 4, 5); // E -> F

    printGraph(graph);

    int arr[MaxVertex]; // 使用 MaxVertex 更安全

    // 初始化数组
    for (int i = 0; i < MaxVertex; ++i) arr[i] = 0;

    printf("\nStart Search (A -> F):\n");
    if (dfs(graph, 0, 5, arr)) {
        printf("Found!\n");
    } else {
        printf("Not Found.\n");
    }

    // 再次搜索演示 (A -> C)
    // 重置 visited 数组
    printf("\n\nStart Search (A -> C):\n");
    for (int i = 0; i < MaxVertex; ++i) arr[i] = 0;

    if (dfs(graph, 0, 2, arr)) {
        printf("Found!\n");
    } else {
        printf("Not Found.\n");
    }
}