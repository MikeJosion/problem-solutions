#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>

#define MINDATA -1  // 最小堆的哨兵值

// ==========================================
// 数据结构定义
// ==========================================

// 1. 哈夫曼树结点
struct HTNode {
    int Weight;             // 权值
    struct HTNode *Left;    // 左子树
    struct HTNode *Right;   // 右子树
};

typedef struct HTNode *HuffmanTree;

// 2. 最小堆结构
struct HeapStruct {
    int Capacity;       // 最大容量
    int Size;           // 当前元素个数
    HuffmanTree *Data;  // 存储节点的数组 (下标从1开始)
};

typedef struct HeapStruct *MinHeap;

// ==========================================
// 函数声明
// ==========================================

// 最小堆相关函数
MinHeap CreateHeap(int Capacity);
void Insert(MinHeap H, HuffmanTree T);
HuffmanTree DeleteMin(MinHeap H);
void BuildHeap(MinHeap H);

// 核心算法
HuffmanTree Huffman(MinHeap H);

// 辅助工具函数
void PrintHuffmanCodes(HuffmanTree root, char *code, int depth);
void FreeTree(HuffmanTree T);
void FreeHeap(MinHeap H);

#endif