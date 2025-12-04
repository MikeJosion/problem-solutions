#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>

// ==========================================
// 1. 核心结构 (多了一个 height)
// ==========================================
typedef int E;

typedef struct AVLNode {
    E element;
    struct AVLNode *left;
    struct AVLNode *right;
    int height; // 【新增】记录当前节点的高度
} AVLNode, *Node;

// ==========================================
// 2. 核心功能声明
// ==========================================

// --- 插入 (自动平衡) ---
// 插入后如果不平衡，会自动旋转调整
Node insertAVL(Node root, E val);

// --- 辅助工具 ---
int getHeight(Node node);        // 获取高度 (空节点为0)
int getBalanceFactor(Node node); // 获取平衡因子 (左高 - 右高)

// --- 遍历 (验证用) ---
void inOrder(Node root);         // 中序 (必须有序)
void preOrder(Node root);        // 前序 (验证结构是否平衡)

#endif // AVL_H