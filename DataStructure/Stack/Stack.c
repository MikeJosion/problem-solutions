#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//顺序表写栈
typedef int E;

struct Stack {
    E * array;
    int capacity;
    int top;   //这里使用top来表示当前的栈顶位置，存的是栈顶元素的下标
};

typedef struct Stack * ArrayStack;  //起个别名

bool initStack(ArrayStack stack) {
    stack->capacity = 10;
    stack->top = -1;
    stack->array = malloc(sizeof(E)*10);
    if (stack->array == NULL)return false;
    return true;
}

bool pushStack(ArrayStack stack, E element) {
    //top是下标top+1是元素的个数
    if (stack->top + 1 == stack->capacity) {
        int newCapacity = stack->capacity * 2;
        // 【关键修改】使用 realloc，它会扩容并保留原数据！
        E * newArray = realloc(stack->array, sizeof(E) * newCapacity);
        if (newArray == NULL) return false; // 扩容失败
        stack->array = newArray;
        stack->capacity = newCapacity; // 更新容量
    }

    stack->top++;
    stack->array[stack->top] = element;
    return true;
}

void printStack(ArrayStack stack) {
    for (int i = 0;i<=stack->top;i++) {
        printf("%d ",stack->array[i]);
    }
    printf("\n");
}

bool isEmpty(ArrayStack stack) {
    return stack->top == -1;
}

E popStack(ArrayStack stack) {
    // 【关键修改】必须先检查是否为空
    if (isEmpty(stack)) {
        printf("错误：栈已空，无法弹栈\n");
        return -1; // 返回一个错误值
    }
    return stack->array[stack->top--];
}



int main(void) {
    system("chcp 65001");

    // 1. 创建栈变量（注意这里要分配实体，不能只定义指针）
    struct Stack myStack;

    // 2. 初始化
    if (initStack(&myStack)) {
        printf("初始化成功\n");
    }

    // 3. 测试入栈 (Push)
    printf("\n=== 测试入栈 ===\n");
    pushStack(&myStack, 100);
    pushStack(&myStack, 200);
    pushStack(&myStack, 300);
    printStack(&myStack);

    // 4. 测试自动扩容 (初始容量是10，我们插入12个元素试试)
    printf("\n=== 测试自动扩容 ===\n");
    for (int i = 1; i <= 12; i++) {
        pushStack(&myStack, i);
    }
    printStack(&myStack);

    // 5. 测试出栈 (Pop)
    printf("\n=== 测试出栈 ===\n");
    printf("Pop出: %d\n", popStack(&myStack));
    printf("Pop出: %d\n", popStack(&myStack));
    printStack(&myStack);

    // 6. 测试空栈保护
    printf("\n=== 测试空栈异常 ===\n");
    // 此时栈里还有很多元素，我们不用循环清空了，直接模拟一个空栈情况测试
    myStack.top = -1; // 暴力清空（仅为了测试）
    popStack(&myStack); // 应该报错而不是崩溃

    // 7. 释放内存 (好习惯)
    free(myStack.array);

    return 0;
}