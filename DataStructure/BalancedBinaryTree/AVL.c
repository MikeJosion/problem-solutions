#include "AVL.h"

// ==========================================
// 1. 辅助工具
// ==========================================
//如果直接访问，碰到 NULL 会报错说没东西；封装一下，碰到 NULL 自动当成 0
//直接写node->height,当node==NULL时NULL->height读了空地址
//报错的本质:“Segmentation Fault” (段错误),
//试图去访问一个系统不允许你访问的内存地址（0x0000000），操作系统为了保护电脑，直接把你的程序杀掉
int getHeight(Node node) {
    if (node == NULL)return 0;
    return node->height;
}

//计算节点的高度,节点的高由最高的那个决定
int max(int a, int b) {
    return a > b ? a : b;
}

// 计算平衡因子: 左子树高度 - 右子树高度
// 结果 > 1 : 左边太高了 (L型)  需要右旋来降低高度
// 结果 < -1: 右边太高了 (R型)  需要左旋来降低高度
int getBalanceFactor(Node node) {
    if (node == NULL)return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// 更新高度 (每次变动后都要调用)
// 整个树的高度 = 左右孩子最高的那个 + 1
void updateHeight(Node node) {
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

// ==========================================
// 2. 旋转操作 (灵魂核心)
// ==========================================

// --- 右旋 (Right Rotation) ---
// 适用场景: 左左 (LL) 失衡
//LL型需要根节点的左边比右边高2,然后左孩子的左边比右边高1/0
// 动作: 把左孩子(y)提上来当爹，自己(root)降下去当右孩子
//灵魂:左孩上位当大哥，老爹降级做右弟(这一步就是把爹赋值给左孩子的右孩子)右孙过继给老爹当左孩子
Node rightRotate(Node root) {
    //总体思路:找变量拿住左孩子和右孙,旋转(灵魂),更新高度,返回新根
    //先将左孩子拿住
    Node newRoot = root->left;
    //左孩子的右孩子会冲突,所以还需要一个变量拿住右孙
    Node temp = newRoot->right;
    //1.旋转(交换父子关系)
    newRoot->right = root; //将newRoot的右孩子变成原来的爹(root)
    root->left = temp; //原来的爹(root)接管我原来的右孩子

    //2.更新高度(注意顺序:先更子,后更父)
    //为什么先更新子再更新父
    //更新原则：自底向上 ,永远先更新处于下层的节点，再更新处于上层的节点。因为上层节点的高度数据 依赖于 下层节点
    updateHeight(root);
    updateHeight(newRoot);

    return newRoot; //返回新的根
}

// --- 左旋 (Left Rotation) ---
// 适用场景: 右右 (RR) 失衡
//RR型需要根节点的右边比左边高2,然后右孩子的右边比左边高1/0
// 动作: 把右孩子(y)提上来当爹，自己(root)降下去当左孩子
//灵魂:右孩子上位当大哥,老爹降级做左弟,左孙过继给老爹当右孩子
Node leftRotate(Node root) {
    Node newRoot = root->right;
    Node temp = newRoot->left;
    newRoot->left = root;
    root->right = temp;
    updateHeight(root);
    updateHeight(newRoot);
    return newRoot;
}

// ==========================================
// 3. 插入 (Insert) - 带自动平衡
// ==========================================
//简单理解就是BST插入加上更新高度和旋转判断
Node insertAVL(Node root, E val) {
    // --- 第一步: 标准 BST 插入 (和昨天写的一样) ---
    if (root == NULL) {
        Node newNode = (Node) malloc(sizeof(AVLNode));
        newNode->element = val;
        newNode->right = newNode->left = NULL;
        newNode->height = 1;
        return newNode;
    }

    //小于往左走,大于往右走
    if (val < root->element) {
        root->left = insertAVL(root->left, val);
    } else if (val > root->element) {
        root->right = insertAVL(root->right, val);
    } else {
        return root;
        //不可以返回NULL,会切断后面的树,return root就是会忽略这次的插入,但是会继续完成售后(更新身高,检查平衡因子)
    }


    // --- 第二步: 更新当前节点的高度 ---
    updateHeight(root);

    // --- 第三步: 检查是否失衡，并“对症下药” (4种情况) ---
    int balance = getBalanceFactor(root);
    //balance > 1：说明左边太高了（左子树比右子树高超过 1）  LL或者LR
    //balance < -1：说明右边太高了（右子树比左子树高超过 1） RR或者RL
    // 情况 A: 左左 (LL) -> 左边太重，且插入在左孩子的左边
    // 对策: 右旋一次
    if (balance > 1 && val < root->left->element) {
        //val < root->left->element 新值比左孩子小，说明插在左孩子的左边 (基于二叉搜索树的原理:比我小的，往左走；比我大的，往右走)
        return rightRotate(root);
    }

    // 情况 B: 右右 (RR) -> 右边太重，且插入在右孩子的右边
    // 对策: 左旋一次
    if (balance < -1 && val > root->right->element) {
        //同理val > root->right->element插在右孩子的右边
        return leftRotate(root);
    }

    // 情况 C: 左右 (LR) -> 左边太重，但插入在左孩子的右边 (拐弯了)
    // 对策: 先把左孩子左旋(变成LL)，再把自己右旋
    //先左旋:把左孩子和右孙互换位置,但是左孩子要去左孙的位置
    if (balance > 1 && val > root->left->element) {
        root->left = leftRotate(root->left); // 先左旋
        //疑问点:为什么root->left = leftRotate(root->left);可以实现先左旋的功能
        //细节去看leftRotate()的代码
        return rightRotate(root); // 再整体右旋
    }

    // 情况 D: 右左 (RL) -> 右边太重，但插入在右孩子的左边 (拐弯了)
    // 对策: 先把右孩子右旋(变成RR)，再把自己左旋
    if (balance < -1 && val < root->right->element) {
        root->right = rightRotate(root->right); // 先微调右孩子
        return leftRotate(root); // 再整体左旋
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
