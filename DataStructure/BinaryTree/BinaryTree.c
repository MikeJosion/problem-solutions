// BinaryTree.c
#include "BinaryTree.h"

// ==========================================
// 1. 链式栈的实现 (Stack Implementation)
//    这里采用无头节点法，s 直接指向栈顶
// ==========================================

void initStack(LinkStack *s) {
    *s = NULL; // 初始化为空，栈顶指针置空
}

bool isStackEmpty(LinkStack s) {
    return s == NULL;
}

bool pushStack(LinkStack *s, BiTree node) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode == NULL) return false; // 内存不足

    newNode->node = node;
    newNode->next = *s; // 新节点的下一级是原本的栈顶
    *s = newNode;       // 栈顶更新为新节点
    return true;
}

BiTree popStack(LinkStack *s) {
    if (isStackEmpty(*s)) return NULL;

    StackNode *topNode = *s;       // 暂存栈顶节点
    BiTree treeNode = topNode->node; // 取出数据

    *s = topNode->next;            // 栈顶下移
    free(topNode);                 // 释放栈顶内存
    return treeNode;
}

BiTree peekStack(LinkStack s) {
    if (isStackEmpty(s)) return NULL;
    return s->node; // 只看不拿
}

// ==========================================
// 2. 链式队列的实现 (Queue Implementation)
//    这里采用带头节点法 (Dummy Head)，方便操作
// ==========================================

void initQueue(LinkQueue *q) {
    // 申请一个空的头节点，front 和 rear 都指向它
    q->front = q->rear = (QueueNode *)malloc(sizeof(QueueNode));
    q->front->next = NULL;
}

bool isQueueEmpty(LinkQueue *q) {
    return q->front == q->rear;
}

void enQueue(LinkQueue *q, BiTree node) {
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->node = node;
    newNode->next = NULL;

    q->rear->next = newNode; // 尾部挂载
    q->rear = newNode;       // 更新尾指针
}

BiTree deQueue(LinkQueue *q) {
    if (isQueueEmpty(q)) return NULL;

    // 注意：链式队列带头节点，数据在 front->next 里
    QueueNode *p = q->front->next;
    BiTree treeNode = p->node;

    q->front->next = p->next; // 越过 p

    // 特殊情况：如果队列只有一个元素，删完后 rear 要归位
    if (q->rear == p) {
        q->rear = q->front;
    }

    free(p);
    return treeNode;
}

// ==========================================
// 3. 二叉树核心：创建与递归遍历
// ==========================================

// 【核心算法】递归创建二叉树
// 用户输入格式示例：ABD##E##C## (#表示空)
BiTree createTree() {
    char ch;
    // 技巧：scanf(" %c") 引号里的第一个空格是为了跳过上一轮留下的回车符或空格
    // 如果不加这个空格，读取会出错
    scanf(" %c", &ch);

    if (ch == '#') {
        return NULL; // 遇到井号，表示这里是空的
    } else {
        // 1. 造根节点
        TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
        node->data = ch;

        // 2. 递归造左子树
        node->left = createTree();

        // 3. 递归造右子树
        node->right = createTree();

        return node;
    }
}

// 销毁树 (防止内存泄漏)
// 必须用后序逻辑：先销毁孩子，最后销毁自己
void destroyTree(BiTree root) {
    if (root == NULL) return;
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
}

// --- 递归遍历实现 (非常简洁) ---

// 1. 前序 (根 -> 左 -> 右)
void preOrder(BiTree root) {
    if (root == NULL) return;
    printf("%c ", root->data); // 先打印自己
    preOrder(root->left);      // 再管左边
    preOrder(root->right);     // 最后管右边
}

// 2. 中序 (左 -> 根 -> 右)
void inOrder(BiTree root) {
    if (root == NULL) return;
    inOrder(root->left);       // 先管左边
    printf("%c ", root->data); // 再打印自己
    inOrder(root->right);      // 最后管右边
}

// 3. 后序 (左 -> 右 -> 根)
void postOrder(BiTree root) {
    if (root == NULL) return;
    postOrder(root->left);     // 先管左边
    postOrder(root->right);    // 再管右边
    printf("%c ", root->data); // 最后打印自己
}

// ==========================================
// 4. 非递归遍历 (Iterative Traversal) - 重点/难点
// ==========================================

// --- 非递归前序 (根 -> 左 -> 右) ---
void preOrderIterative(BiTree root) {
    if (root == NULL) return;

    LinkStack s;
    initStack(&s);

    BiTree curr = root;

    while (curr != NULL || !isStackEmpty(s)) {
        // 1. 一路向左，边走边打印，并把节点存入栈(为了等会儿回来找右孩子)
        while (curr != NULL) {
            printf("%c ", curr->data); // 【前序】：先打印
            pushStack(&s, curr);
            curr = curr->left;
        }

        // 2. 左边走到头了，从栈里弹出来，转身向右
        if (!isStackEmpty(s)) {
            curr = popStack(&s);
            curr = curr->right;
        }
    }
}

// --- 非递归中序 (左 -> 根 -> 右) ---
void inOrderIterative(BiTree root) {
    if (root == NULL) return;

    LinkStack s;
    initStack(&s);

    BiTree curr = root;

    while (curr != NULL || !isStackEmpty(s)) {
        // 1. 一路向左，只入栈，不打印
        while (curr != NULL) {
            pushStack(&s, curr);
            curr = curr->left;
        }

        // 2. 左边走到头了，弹出来打印，然后转身向右
        if (!isStackEmpty(s)) {
            curr = popStack(&s);
            printf("%c ", curr->data); // 【中序】：从左边回来时才打印
            curr = curr->right;
        }
    }
}

// --- 非递归后序 (左 -> 右 -> 根) --- 这是最难的！
void postOrderIterative(BiTree root) {
    if (root == NULL) return;

    LinkStack s;
    initStack(&s);

    BiTree curr = root;
    BiTree prev = NULL; // 记录上一次访问的节点

    while (curr != NULL || !isStackEmpty(s)) {
        // 1. 一路向左入栈
        while (curr != NULL) {
            pushStack(&s, curr);
            curr = curr->left;
        }

        // 2. 左边没了，看看栈顶（先不弹）
        BiTree top = peekStack(s);

        // 3. 判断：如果有右孩子，且右孩子没被访问过 -> 转战右边
        if (top->right != NULL && top->right != prev) {
            curr = top->right;
        }
        // 4. 没有右孩子，或者右孩子已经访问过了 -> 可以打印根节点了
        else {
            printf("%c ", top->data); // 【后序】：最后打印
            popStack(&s);             // 真的弹出了
            prev = top;               // 标记为已访问
            curr = NULL;              // 关键！重置为空，防止下一次循环又往左钻
        }
    }
}

// ==========================================
// 5. 层序遍历 (Level Order) - 使用队列
// ==========================================
void levelOrder(BiTree root) {
    if (root == NULL) return;

    LinkQueue q;
    initQueue(&q);

    enQueue(&q, root); // 根节点先入队

    while (!isQueueEmpty(&q)) {
        // 1. 出队并打印
        BiTree node = deQueue(&q);
        printf("%c ", node->data);

        // 2. 有左孩子带左孩子
        if (node->left != NULL) {
            enQueue(&q, node->left);
        }

        // 3. 有右孩子带右孩子
        if (node->right != NULL) {
            enQueue(&q, node->right);
        }
    }

    // 实际工程中这里需要释放队列头节点的内存，这里为了代码简单省略
}