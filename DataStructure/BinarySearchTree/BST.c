#include "BST.h"

// ==========================================
// 1. 插入 (Insert) - 递归版
// 灵魂: 比我小去左边，比我大去右边
// (从根开始,比根节点大就是往右子树走,比根节点小就是往左子树走)
//注意插入必须要走到死胡同
// ==========================================
Node insertBST(Node root, E val) {
    // 1. 找到了空位，就在这里安家
    if (root == NULL) {
        Node newNode = (Node)malloc(sizeof(TreeNode));
        newNode->element = val;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    // 2. 比根小，往左走
    if (val < root->element) {
        root->left = insertBST(root->left, val);
    }
    // 3. 比根大，往右走
    else if (val > root->element) {
        root->right = insertBST(root->right, val);
    }
    // 4. 如果相等，BST通常不存重复值，直接返回

    return root; // 返回当前节点，保持链条不断
}

// ==========================================
// 2. 查找 (Search) - 迭代版
// 灵魂: 像猜数字游戏一样，大往右，小往左
// ==========================================
Node searchBST(Node root, E val) {
    while (root != NULL) {
        if (val < root->element) {
            root = root->left;  // 目标比当前小，去左边找
        } else if (val > root->element) {
            root = root->right; // 目标比当前大，去右边找
        } else {
            return root;        // 找到了！(val == root->element)
        }
    }
    return NULL; // 走到死胡同也没找到
}

// ==========================================
// 3. 极值查找 (Min / Max)
// ==========================================
Node findMin(Node root) {
    if (root == NULL) return NULL;
    // 最小的一定在最左边
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node findMax(Node root) {
    if (root == NULL) return NULL;
    // 最大的一定在最右边
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

// ==========================================
// 4. 删除 (Delete) - 递归版 (最难逻辑)
// 灵魂:
// 1. 如果是叶子: 直接删。
// 2. 如果独苗(单孩子): 让孩子接班。
// 3. 如果儿女双全: 找右子树里最小的那个(继承人)来顶替，然后把那个继承人删掉。
//也可以找左边最大的(左子树的最右节点)
// ==========================================
Node deleteBST(Node root, E val) {
    if (root == NULL) return NULL;

    // --- 第一步: 先找到要删的节点 ---
    if (val < root->element) {
        root->left = deleteBST(root->left, val);
    }
    else if (val > root->element) {
        root->right = deleteBST(root->right, val);
    }
    // --- 第二步: 找到了 (val == root->element)，准备动手 ---
    else {
        // 情况 A: 它是叶子节点，或者只有一个孩子
        //只要我左边是NULL，就把右边交上去。不管右边是子节点，还是NULL，直接交上去
        if (root->left == NULL) {
            Node temp = root->right; // 让右孩子接班 (可能是NULL)
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node temp = root->left;  // 让左孩子接班
            free(root);
            return temp;
        }

        // 情况 B: 儿女双全 (左右都有)
        // 策略: 找右子树里最小的节点 (Successor) 来顶替位置
        Node temp = findMin(root->right);

        // 1. 把右子树最小的节点的值直接给要删除的节点
        root->element = temp->element;
        //关于右子树最小的节点:一定是“没有左孩子”的，但不一定是叶子节点（它可能有右孩子）
        // 2. 去右子树里，把那个继承人的旧肉身删掉
        root->right = deleteBST(root->right, temp->element);
    }
    return root;
}
//注意点:最后不可以直接free那个右子树最小节点,因为它可能有右孩子,所以要重复deleteBST()这样就是单节点,孩子会上去接班


// ==========================================
// 5. 中序遍历 (验证用)
// ==========================================
void inOrder(Node root) {
    if (root == NULL) return;
    inOrder(root->left);
    printf("%d ", root->element);
    inOrder(root->right);
}