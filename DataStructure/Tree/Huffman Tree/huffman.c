#include "huffman.h"

// ==========================================
// 最小堆操作实现
// ==========================================

// 创建一个空的最小堆
MinHeap CreateHeap(int Capacity) {
    MinHeap H = (MinHeap)malloc(sizeof(struct HeapStruct));
    // Data数组大小为 Capacity + 1，因为下标0用于存放哨兵
    H->Data = (HuffmanTree *)malloc((Capacity + 1) * sizeof(HuffmanTree));
    H->Capacity = Capacity;
    H->Size = 0;

    // 设置哨兵，简化插入判断
    H->Data[0] = (HuffmanTree)malloc(sizeof(struct HTNode));
    H->Data[0]->Weight = MINDATA;
    H->Data[0]->Left = NULL;
    H->Data[0]->Right = NULL;

    return H;
}

// 插入 (Insert)
void Insert(MinHeap H, HuffmanTree T) {
    int i;
    if (H->Size == H->Capacity) {
        printf("Heap is full\n");
        return;
    }
    // 上滤 (Percolate Up)
    for (i = ++H->Size; H->Data[i / 2]->Weight > T->Weight; i /= 2) {
        H->Data[i] = H->Data[i / 2];
    }
    H->Data[i] = T;
}

// 删除最小元 (DeleteMin)
HuffmanTree DeleteMin(MinHeap H) {
    int i, Child;
    HuffmanTree MinItem, LastItem;

    if (H->Size == 0) {
        printf("Heap is empty\n");
        return NULL;
    }
    MinItem = H->Data[1];
    LastItem = H->Data[H->Size--];

    // 下滤 (Percolate Down)
    for (i = 1; i * 2 <= H->Size; i = Child) {
        Child = i * 2;
        if (Child != H->Size && H->Data[Child + 1]->Weight < H->Data[Child]->Weight)
            Child++;

        if (LastItem->Weight > H->Data[Child]->Weight)
            H->Data[i] = H->Data[Child];
        else
            break;
    }
    H->Data[i] = LastItem;
    return MinItem;
}

// 建堆 (BuildHeap)
void BuildHeap(MinHeap H) {
    int i, j, Child;
    HuffmanTree Tmp;
    // 从最后一个非叶子节点开始调整
    for (i = H->Size / 2; i > 0; i--) {
        Tmp = H->Data[i];
        for (j = i; j * 2 <= H->Size; j = Child) {
            Child = j * 2;
            if (Child != H->Size && H->Data[Child + 1]->Weight < H->Data[Child]->Weight)
                Child++;

            if (Tmp->Weight > H->Data[Child]->Weight)
                H->Data[j] = H->Data[Child];
            else
                break;
        }
        H->Data[j] = Tmp;
    }
}

// ==========================================
// 哈夫曼核心算法
// ==========================================

HuffmanTree Huffman(MinHeap H) {
    int i, N;
    HuffmanTree T;

    N = H->Size;
    BuildHeap(H); // 课本逻辑：先调整堆

    // 做 N-1 次合并
    for (i = 1; i < N; i++) {
        T = (HuffmanTree)malloc(sizeof(struct HTNode));
        T->Left = DeleteMin(H);  // 找最小
        T->Right = DeleteMin(H); // 找次小
        T->Weight = T->Left->Weight + T->Right->Weight; // 合并权值
        Insert(H, T); // 插入新节点
    }

    return DeleteMin(H); // 返回根节点
}

// ==========================================
// 辅助功能实现
// ==========================================

// 递归打印编码
void PrintHuffmanCodes(HuffmanTree root, char *code, int depth) {
    if (!root) return;

    if (!root->Left && !root->Right) {
        code[depth] = '\0';
        printf("权值 %2d 的编码: %s\n", root->Weight, code);
        return;
    }

    if (root->Left) {
        code[depth] = '0';
        PrintHuffmanCodes(root->Left, code, depth + 1);
    }
    if (root->Right) {
        code[depth] = '1';
        PrintHuffmanCodes(root->Right, code, depth + 1);
    }
}

// 释放哈夫曼树内存
void FreeTree(HuffmanTree T) {
    if (T) {
        FreeTree(T->Left);
        FreeTree(T->Right);
        free(T);
    }
}

// 释放堆内存
void FreeHeap(MinHeap H) {
    if (H) {
        if (H->Data) {
            free(H->Data[0]); // 释放哨兵
            free(H->Data);
        }
        free(H);
    }
}