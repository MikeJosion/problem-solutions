#include "AVL.h"

// ==========================================
// 1. 辅助工具
// ==========================================
//如果直接访问，碰到 NULL 会报错说没东西；封装一下，碰到 NULL 自动当成 0
//直接写node->height,当node==NULL时NULL->height读了空地址
//报错的本质:“Segmentation Fault” (段错误),
//试图去访问一个系统不允许你访问的内存地址（0x0000000），操作系统为了保护电脑，直接把你的程序杀掉
int getHeight(Node node) {
    if (node == NULL) return 0;
    return node->height;
}
//计算节点的高度,节点的高由最高的那个决定
int max(int a, int b) {
    return a > b ? a : b;
}

// 计算平衡因子: 左子树高度 - 右子树高度
// 结果 > 1 : 左边太重了 (L型)
// 结果 < -1: 右边太重了 (R型)
int getBalanceFactor(Node node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// 更新高度 (每次变动后都要调用)
// 自己的高度 = 左右孩子最高的那个 + 1
void updateHeight(Node node) {
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

// ==========================================
// 2. 旋转操作 (灵魂核心)
// ==========================================

// --- 右旋 (Right Rotation) ---
// 适用场景: 左左 (LL) 失衡
// 动作: 把左孩子(y)提上来当爹，自己(root)降下去当右孩子
Node rightRotate(Node root) {
    Node newRoot = root->left;   // 这里的 newRoot 就是原来的左孩子
    Node temp = newRoot->right;  // 暂存 newRoot 的右孩子(也就是冲突的那块肉)

    // 1. 旋转 (互换父子关系)
    newRoot->right = root;       // 我(newRoot)的右孩子变成原来的爹(root)
    root->left = temp;           // 原来的爹(root)接管我原本的右孩子

    // 2. 更新高度 (注意顺序: 先更子，后更父)
    updateHeight(root);
    updateHeight(newRoot);

    return newRoot; // 返回新的根
}

// --- 左旋 (Left Rotation) ---
// 适用场景: 右右 (RR) 失衡
// 动作: 把右孩子(y)提上来当爹，自己(root)降下去当左孩子
Node leftRotate(Node root) {
    Node newRoot = root->right;  // 这里的 newRoot 就是原来的右孩子
    Node temp = newRoot->left;   // 暂存 newRoot 的左孩子

    // 1. 旋转
    newRoot->left = root;        // 我(newRoot)的左孩子变成原来的爹(root)
    root->right = temp;          // 原来的爹(root)接管我原本的左孩子

    // 2. 更新高度
    updateHeight(root);
    updateHeight(newRoot);

    return newRoot;
}

// ==========================================
// 3. 插入 (Insert) - 带自动平衡
// ==========================================
Node insertAVL(Node root, E val) {
    // --- 第一步: 标准 BST 插入 (和昨天写的一样) ---
    if (root == NULL) {
        Node newNode = (Node)malloc(sizeof(AVLNode));
        newNode->element = val;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1; // 新节点高度为 1
        return newNode;
    }

    if (val < root->element) {
        root->left = insertAVL(root->left, val);
    } else if (val > root->element) {
        root->right = insertAVL(root->right, val);
    } else {
        return root; // 不允许重复值
    }

    // --- 第二步: 更新当前节点的高度 ---
    updateHeight(root);

    // --- 第三步: 检查是否失衡，并“对症下药” (4种情况) ---
    int balance = getBalanceFactor(root);

    // 情况 A: 左左 (LL) -> 左边太重，且插入在左孩子的左边
    // 对策: 右旋一次
    if (balance > 1 && val < root->left->element) {
        return rightRotate(root);
    }

    // 情况 B: 右右 (RR) -> 右边太重，且插入在右孩子的右边
    // 对策: 左旋一次
    if (balance < -1 && val > root->right->element) {
        return leftRotate(root);
    }

    // 情况 C: 左右 (LR) -> 左边太重，但插入在左孩子的右边 (拐弯了)
    // 对策: 先把左孩子左旋(变成LL)，再把自己右旋
    if (balance > 1 && val > root->left->element) {
        root->left = leftRotate(root->left); // 先微调左孩子
        return rightRotate(root);            // 再整体右旋
    }

    // 情况 D: 右左 (RL) -> 右边太重，但插入在右孩子的左边 (拐弯了)
    // 对策: 先把右孩子右旋(变成RR)，再把自己左旋
    if (balance < -1 && val < root->right->element) {
        root->right = rightRotate(root->right); // 先微调右孩子
        return leftRotate(root);                // 再整体左旋
    }

    // 如果没失衡，直接返回自己
    return root;
}

// ==========================================
// 4. 遍历 (验证)
// ==========================================
void inOrder(Node root) {
    if (root == NULL) return;
    inOrder(root->left);
    printf("%d ", root->element);
    inOrder(root->right);
}

void preOrder(Node root) {
    if (root == NULL) return;
    printf("%d ", root->element);
    preOrder(root->left);
    preOrder(root->right);
}