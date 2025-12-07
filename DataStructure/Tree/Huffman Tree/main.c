#include <stdio.h>
#include "huffman.h"

int main() {
    system("chcp 65001");
    // 1. 准备测试权值
    int weights[] = {5, 29, 7, 8, 14, 23, 3, 11};
    int n = sizeof(weights) / sizeof(weights[0]);
    int i;

    printf("=== 哈夫曼树测试 (基于课本最小堆实现) ===\n");
    printf("初始权值: ");
    for(i = 0; i < n; i++) printf("%d ", weights[i]);
    printf("\n\n");

    // 2. 初始化堆并装填数据
    // 注意：课本算法是假定数据已经在堆数组里，然后调用 BuildHeap
    MinHeap H = CreateHeap(n);
    for (i = 0; i < n; i++) {
        HuffmanTree node = (HuffmanTree)malloc(sizeof(struct HTNode));
        node->Weight = weights[i];
        node->Left = NULL;
        node->Right = NULL;

        // 直接填入 Data 数组，Size 自增
        H->Data[++H->Size] = node;
    }

    // 3. 构建哈夫曼树
    HuffmanTree root = Huffman(H);

    // 4. 打印结果
    printf("--- 哈夫曼编码 ---\n");
    char codeBuffer[256]; // 编码缓存
    PrintHuffmanCodes(root, codeBuffer, 0);

    // 5. 简单的校验
    printf("\n根节点总权值: %d\n", root->Weight);

    // 6. 清理内存
    FreeTree(root);
    FreeHeap(H);

    return 0;
}