//#ifndef + #define = 给头文件上锁，防止重复包含，避免重复定义的报错。
#ifndef BINARYTREE_H // “有没有上锁？”
#define BINARYTREE_H // “没有？那现在上锁！”

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// ==========================================
//1.核心结构:二叉树节点
// ==========================================
typedef char ElemType;//方便以后改为int或者其他的类型

typedef struct TreeNode {
    ElemType data;     //树的值
    struct TreeNode * left;  //左孩子
    struct TreeNode * right; //右孩子
}TreeNode,*BiTree; //别名
//TreeNode是一个节点对象包括了数据,左右孩子;BiTree指向的是这个节点的地址

// ==========================================
// 2. 辅助工具：链式栈 (给非递归遍历用)
//    存的是树节点的指针 (BiTree)
// ==========================================
typedef struct StackNode {
    BiTree node;              // 存树的节点
    struct StackNode *next;
} StackNode, *LinkStack;

// --- 栈的操作声明 ---
void initStack(LinkStack *s);           // 初始化
bool isStackEmpty(LinkStack s);         // 判空
bool pushStack(LinkStack *s, BiTree node); // 入栈
BiTree popStack(LinkStack *s);          // 出栈
BiTree peekStack(LinkStack s);          // 看一眼栈顶 (后序遍历专用)

// ==========================================
// 3. 辅助工具：链式队列 (给层序遍历用)
// ==========================================
typedef struct QueueNode {
    BiTree node;              // 存树的节点
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front; // 头指针
    QueueNode *rear;  // 尾指针
} LinkQueue;

// --- 队列的操作声明 ---
void initQueue(LinkQueue *q);           // 初始化
bool isQueueEmpty(LinkQueue *q);        // 判空
void enQueue(LinkQueue *q, BiTree node); // 入队
BiTree deQueue(LinkQueue *q);           // 出队

// ==========================================
// 4. 二叉树的核心功能
// ==========================================

// --- 创建与销毁 ---
// 按照前序输入创建 (如 "ABD##E##C##")
BiTree createTree();
void destroyTree(BiTree root);

// --- 递归遍历 (Recursive) ---
void preOrder(BiTree root);
void inOrder(BiTree root);
void postOrder(BiTree root);

// --- 非递归遍历 (Iterative) ---
void preOrderIterative(BiTree root);
void inOrderIterative(BiTree root);
void postOrderIterative(BiTree root); // 难点

// --- 层序遍历 (Level Order) ---
void levelOrder(BiTree root);

#endif // BINARYTREE_H