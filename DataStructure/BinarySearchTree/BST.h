#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ==========================================
// 1. 核心结构
// ==========================================
typedef int E; // BST 通常用于数字排序查找，所以用 int

typedef struct TreeNode {
    E element;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode, *Node;

// ==========================================
// 2. BST 核心功能声明
// ==========================================

// --- 插入 (构建树的唯一方式) ---
// 这里的 root 必须传指针的指针(Node*)，或者利用返回值更新
// 我们采用返回值风格: root = insertBST(root, 10);
Node insertBST(Node root, E val);

// --- 查找 ---
Node searchBST(Node root, E val);

// --- 删除 (难点: 需要处理三种情况) ---
Node deleteBST(Node root, E val);

// --- 辅助功能 ---
Node findMin(Node root); // 找最小 (一路向左)
Node findMax(Node root); // 找最大 (一路向右)

// --- 遍历 ---
// BST 的中序遍历有一个神奇特性: 打印出来是【有序数组】
void inOrder(Node root);

#endif // BST_H