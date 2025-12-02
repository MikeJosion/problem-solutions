#include "BST.h"
//左小右大 包括子树里面的所有元素都要满足这个条件
int main() {
    // 解决乱码
    system("chcp 65001");

    Node root = NULL;

    printf("=== 1. 开始建树 (插入 50, 30, 20, 40, 70, 60, 80) ===\n");
    root = insertBST(root, 50);
    root = insertBST(root, 30);
    root = insertBST(root, 20);
    root = insertBST(root, 40);
    root = insertBST(root, 70);
    root = insertBST(root, 60);
    root = insertBST(root, 80);

    // 验证: BST 的中序遍历一定是 从小到大 的
    printf("中序遍历结果(应该是有序的): ");
    inOrder(root);
    printf("\n");

    printf("\n=== 2. 测试查找 ===\n");
    int target = 60;
    Node result = searchBST(root, target);
    if (result) printf("找到了 %d!\n", result->element);
    else printf("没找到 %d\n", target);

    printf("\n=== 3. 测试极值 ===\n");
    printf("最小值: %d\n", findMin(root)->element);
    printf("最大值: %d\n", findMax(root)->element);

    printf("\n=== 4. 测试删除 (最难部分) ===\n");

    printf("删除叶子节点 20:\n");
    root = deleteBST(root, 20);
    inOrder(root); printf("\n");

    printf("删除单孩子节点 30 (它的孩子40应该接班):\n");
    root = deleteBST(root, 30);
    inOrder(root); printf("\n");

    printf("删除双孩子节点 50 (根节点，右边最小的60应该上位):\n");
    root = deleteBST(root, 50);
    inOrder(root); printf("\n");

    return 0;
}