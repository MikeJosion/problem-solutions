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
    StackNode *newNode = (StackNode *) malloc(sizeof(StackNode));
    if (newNode == NULL) return false; // 内存不足

    newNode->node = node;
    newNode->next = *s; // 新节点的下一级是原本的栈顶
    *s = newNode; // 栈顶更新为新节点
    return true;
}

BiTree popStack(LinkStack *s) {
    if (isStackEmpty(*s)) return NULL;

    StackNode *topNode = *s; // 暂存栈顶节点
    BiTree treeNode = topNode->node; // 取出数据

    *s = topNode->next; // 栈顶下移
    free(topNode); // 释放栈顶内存
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
    q->front = q->rear = (QueueNode *) malloc(sizeof(QueueNode));
    q->front->next = NULL;
}

bool isQueueEmpty(LinkQueue *q) {
    return q->front == q->rear;
}

void enQueue(LinkQueue *q, BiTree node) {
    QueueNode *newNode = (QueueNode *) malloc(sizeof(QueueNode));
    newNode->node = node;
    newNode->next = NULL;

    q->rear->next = newNode; // 尾部挂载
    q->rear = newNode; // 更新尾指针
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
    scanf(" %c", &ch);
    //注意scanf是" %c",前面是存在一个空格的在读取字符之前，把前面遗留的空格、回车、Tab 全部移走，直到遇到一个真正的字符为止
    //很容易输成"%c"忽略前面的空格
    if (ch == '#') {
        return NULL; //遇到#说明这个地方是空的
    } else {
        TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
        //(TreeNode*)的作用强制类型转换,malloc 默认返回的是 void*;TreeNode是一个节点包含数据和左右指针
        if (node == NULL) {
            printf("申请内存失败");
            return NULL;
            //写return NULL的好处,防止程序崩溃,失败可能会返回一个随机的垃圾值,还可以保持逻辑诚实
        }
        node->data = ch;
        node->left = createTree();
        node->right = createTree();
        return node;
    }
}

// 销毁树 (防止内存泄漏) 手动调用
// 必须用后序逻辑：先销毁孩子，最后销毁自己(左右孩子顺序无所谓,主要是先杀孩子再杀自己)
void destroyTree(BiTree root) {
    if (root == NULL)return;
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
}

// --- 递归遍历实现 (非常简洁) ---
//简单记忆就是轮到根就是打印操作,左就是调用函数左节点走,右就是调用函数右节点走
// 1. 前序 (根 -> 左 -> 右)
void preOrder(BiTree root) {
    if (root == NULL)return;
    printf("%c", root->data);
    preOrder(root->left);
    preOrder(root->right);
}

// 2. 中序 (左 -> 根 -> 右)
void inOrder(BiTree root) {
    if (root == NULL)return;
    inOrder(root->left);
    printf("%c", root->data);
    inOrder(root->right);
}

// 3. 后序 (左 -> 右 -> 根)
void postOrder(BiTree root) {
    if (root == NULL)return;
    postOrder(root->left);
    postOrder(root->right);
    printf("%c", root->data);
}

// ==========================================
// 4. 非递归遍历 (Iterative Traversal) - 重点/难点
//与递归类似,根就是打印操作,左就是调用函数左节点走,右就是调用函数右节点走
//小循环:都是先压栈,再看操作的第一个,根在前要先printf("%c", curr->data);然后结尾都是左:curr = curr->left;
//
// ==========================================

// --- 非递归前序 (根 -> 左 -> 右) ---
//灵魂:前序遍历是拿到节点立刻打印,打印完成再进栈,出栈是为了找它的右孩子
void preOrderIterative(BiTree root) {
    if (root == NULL) return;
    LinkStack s; //创建一个栈的控制指针 s
    initStack(&s); //初始化为空栈
    BiTree curr = root; //在遍历过程指针会不断变化,但是整个树的根是不可以变的,所以curr就相当于探险家
    while (curr != NULL || !isStackEmpty(s)) {
        while (curr != NULL) {
            pushStack(&s, curr);
            printf("%c ", curr->data); //先是根打印
            curr = curr->left;
        }
        //撞墙回溯，向右转
        if (!isStackEmpty(s)) {
            //如果栈空了，说明整棵树都跑遍了,没空说明有长辈在等着去处理他们的右边
            curr = popStack(&s);
            //回到上一个路口
            curr = curr->right;
            //看老爸的右边有没有东西
        }
    }
}

//注意点:出栈之后要一个接着这个出栈的元素看有没有右孩子,撞墙回溯在大循环里面,不是外面
//疑问点:当左边走到底之后右边的元素是怎么写进栈的又是怎么打印的
//当 curr 变成了右孩子之后，外层的大循环 (while) 会再次开始

// --- 非递归中序 (左 -> 根 -> 右) ---
//灵魂:中序是拿到节点进栈,直到一路向左走到底出栈的时候再打印
void inOrderIterative(BiTree root) {
    if (root == NULL) return;
    LinkStack s;
    initStack(&s);
    BiTree curr = root;
    while (curr != NULL || !isStackEmpty(s)) {
        while (curr != NULL) {
            pushStack(&s, curr);
            curr = curr->left;
        }
        //撞墙之后别慌张，先弹栈，再打印，最后右转
        if (!isStackEmpty(s)) {
            curr = popStack(&s);
            printf("%c ", curr->data);
            curr = curr->right;
        }
    }
}

//注意点:撞墙回溯时是先弹栈之后再打印
//当你跳出小循环进入 if 语句时，此时此刻 curr 等于 NULL。 你第一句就写 curr->data，相当于叫电脑去读一个空地址的数据，电脑直接报错罢工


// --- 非递归后序 (左 -> 右 -> 根) ---
//灵魂:先拿到元素进栈,当左边一路走到底时,回看栈顶这个没有左孩子”（或者左孩子刚走完）的节点本身
//如果它有右孩子，而且没去过,不出栈也不打印;如果它没有右孩子，或者我们刚刚就是从右孩子那边回来的出栈 -> 打印
void postOrderIterative(BiTree root) {
    if (root == NULL) return;
    LinkStack s;
    initStack(&s);
    BiTree curr = root;
    BiTree prev = NULL;
    //prev 的作用就是记录右孩子有没有去过,因为后序遍历会经过两次根节点
    //先去左,然后返回根,然后去右再返回根,直到左右全部去过之后,返回根之后再打印根

    while (curr != NULL || !isStackEmpty(s)) {
        // 1. 一路向左入栈
        while (curr != NULL) {
            pushStack(&s, curr);
            curr = curr->left;
        }

        // 2. 左边没了，看看栈顶（先不弹）;取栈顶元素的值，赋值给 top
        BiTree top = peekStack(s);
        //peekStack 的作用就是： “大哥（栈顶节点），你先在里面坐会儿，别出来。我先看看你的右孩子去没去过，再决定你是留下来加班，还是下班回家。

        // 3. 判断：如果有右孩子，且右孩子没被访问过 -> 转战右边
        if (top->right != NULL && top->right != prev) {
            //prev 就是你刚刚“干掉”（打印并出栈）的那一个节点
            curr = top->right;
        }
        // 4. 没有右孩子，或者右孩子已经访问过了 -> 可以打印根节点了
        else {
            printf("%c ", top->data); // 【后序】：最后打印
            popStack(&s); // 真的弹出了
            prev = top; // 给父节点看,如果 prev == 我的右孩子：父节点就知可以打印了
            curr = NULL; // 关键！重置为空，防止下一次循环又往左钻
        }
    }
}

// ==========================================
// 5. 层序遍历 (Level Order) - 使用队列(先进先出)
// ==========================================
void levelOrder(BiTree root) {
    if (root == NULL) return;

    LinkQueue q;
    initQueue(&q);

    enQueue(&q, root); // 根节点先入队

    while (!isQueueEmpty(&q)) {
        //上一层的人负责把下一层的人“拉进队列”里，等循环转回来的时候，下一层的人自然就被处理了。
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
