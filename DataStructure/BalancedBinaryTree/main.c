#include "AVL.h"
//平衡二叉树的目的,二叉搜索树如果是按顺序插入一连串递增的树,那么就会倾斜,类似于链表,
//二叉搜索树失去了二叉树的优点,所以平衡二叉树的作用就是控制高度差的值小于等于1
int main() {
    system("chcp 65001");

    Node root = NULL;

    printf("=== 测试: 插入 1, 2, 3, 4, 5 (BST会变成链表，AVL会自动平衡) ===\n");
    // 依次插入，每次插入后 AVL 都会偷偷自动旋转
    root = insertAVL(root, 1);
    root = insertAVL(root, 2);
    root = insertAVL(root, 3);
    root = insertAVL(root, 4);
    root = insertAVL(root, 5);

    printf("\n1. 中序遍历 (必须有序): ");
    inOrder(root); // 预期: 1 2 3 4 5
    printf("\n");

    printf("2. 前序遍历 (查看结构): ");
    preOrder(root);
    // 如果是 BST，前序是: 1 2 3 4 5
    // 如果是 AVL，前序应该是: 2 1 4 3 5 (或者类似的平衡结构)
    // 解释: 2 是根，1是左，4是右，3是4的左，5是4的右。非常平衡！
    printf("\n");

    printf("3. 根节点的高度: %d\n", getHeight(root));
    // BST 高度应该是 5，AVL 应该是 3

    return 0;
}