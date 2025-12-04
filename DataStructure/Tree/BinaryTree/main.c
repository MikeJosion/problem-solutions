#include "BinaryTree.h"

int main() {
    // 1. 解决 Windows 控制台中文乱码 (可选)
    system("chcp 65001");

    // 2. 提示输入
    // 我们用这个经典的例子：
    //       A
    //      / \
    //     B   C
    //      \
    //       D
    // 前序输入序列应该是: A B # D # # C # #
    printf("请输入前序建树序列 (例如: A B # D # # C # #):\n");
    printf("注意：# 代表空节点，字母之间可以用空格隔开\n> ");

    // 3. 创建树
    BiTree root = createTree();
    printf("\n=== 树创建成功! ===\n");

    // 4. 递归遍历测试
    printf("\n[递归] 前序: "); preOrder(root);
    printf("\n[递归] 中序: "); inOrder(root);
    printf("\n[递归] 后序: "); postOrder(root);
    printf("\n");

    // 5. 非递归遍历测试
    printf("\n[迭代] 前序: "); preOrderIterative(root);
    printf("\n[迭代] 中序: "); inOrderIterative(root);
    printf("\n[迭代] 后序: "); postOrderIterative(root);
    printf("\n");

    // 6. 层序遍历测试
    printf("\n[层序] 遍历: "); levelOrder(root);
    printf("\n");

    // 7. 销毁树
    destroyTree(root);
    printf("\n=== 树已销毁，程序结束 ===\n");

    return 0;
}