# [19. 删除链表的倒数第 N 个结点](https://leetcode.cn/problems/remove-nth-node-from-end-of-list/)**(12.18)**

给你一个链表，删除链表的倒数第 `n`* *个结点，并且返回链表的头结点。

**示例 1：**
![image](https://assets.leetcode.com/uploads/2020/10/03/remove_ex1.jpg)

```plain text
输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]
```

## 难点

<details><summary>1️⃣ 为什么在定义栈的结构体时,我不可以都使用next来表示链表和栈的下一个节点的位置？</summary>


```c
typedef struct Stack {

    // 既然都是指向各自职责的下一个，为什么不能都叫 next
		//eg: 栈节点->栈的next 或 栈节点->链表的next。
    struct ListNode* next;

    struct Stack* next;

} StackNode;
```
> 💡 ****语法禁止**：同一个结构体内不允许同名成员。 并且编译器不能很好的区分next指向的究竟是什么**
>

</details>

<details><summary>2️⃣为什么定义栈的时候不直接传入链表的值然后而是传入指向链表节点的地？</summary>

> 💡 **最终的目的是删除指定节点值,后面的节点仍需要保持链接,存的是地址，才拥有了**改变链表结构**的能力**
>


</details>

<details><summary>3️⃣ 删除指定节点不成功？</summary>

> 💡 ****
>
> 
> ```c
> ❌ 错误写法：
> 
> for (int i = 0; i < n; i++) {
> StackNode* tmp = top;
> top = top->next;
> free(top);
> top = tmp;
> }
> 
> ❌ 错误理解：
> 首先需要一个节点来拿到栈顶的元素StackNode* tmp = top;,如果直接free top,会导致后面的断开连接,
> 所以再top = top->next;,然后=释放空间,再拿一个节点来指向后面的栈顶
> 
> ✅ 正确理解：
> 错误的写法使代码逻辑和想法之间出现了一个严重的“时空错位
> StackNode* tmp = top;
> 此时 tmp 和 top 都指向节点 A。
> top = top->next;
> top 移动到了节点 B。此时 tmp 还在 A。
> free(top); 😱（关键错误点）
> 你本来想释放 A，但你这句代码释放的是 B！
> 因为上一行你刚把 top 移到了 B。现在 B 消失了，B 后面的连接（指向 C 的线）也彻底断了。
> top = tmp;
> 你又把 top 移回了 A（那个你原本想释放却没释放掉的节点）。
> 结果:这一轮循环下来，你删掉了不该删的 B，留下了该删的 A，并且 top 还在原地踏步，陷入了死循环或逻辑混乱
> 
> 😱认识错误点后的写法:
> for (int i = 0; i < n; i++) {
> StackNode* tmp = top;
> top = top->next;
> free(tmp);
> tmp = top;
> }
> 从编程逻辑来看，最后一行 tmp = top; 是多余的（冗余）。
> 
> ✅ 正确判断：
> for (int i = 0; i < n; i++) {
>     StackNode* tmp = top; // 1. 抓稳要删的
>     top = top->next;      // 2. 移到下一个
>     free(tmp);            // 3. 删掉旧的
>     // 循环结束，tmp 自动失效，下一轮会自动重新抓取新的 top
> }
> ```
> 
</details>


## 🏗️ 核心知识点：题目设计之巧妙
> 💡 ****
>
> 
> ## ✅**哨兵位（Dummy Node）的设计：**
> > - **用意**：解决“头节点被删”的特殊情况。
> > - **本质**：通过增加一个“假头”，让链表里的每个节点都有一个“前驱”，从而把所有删除操作统一化。
> > 
> ## 🧪 深度剖析：结构体 vs 结构体指针
> > > 
> ```c
> //结构体
> struct Smartphone {
> char model[20];   // 型号
> int battery;      // 电量
> float price;      // 价格
> };
> struct Smartphone* ptr; //结构体指针
> 
> typedef struct Smartphone {
>     char model[20];   // 型号
>     int battery;      // 电量
>     float price;      // 价格
> } Phone,*Phoneptr;
> 
> ```
> > > 💡 ****
> >
> > > 💡 **第一个结构体**
> > >
> > > - `struct Smartphone { ... };`** 的作用**：
> > 这是在定义一个**“模具”**。它告诉编译器：“从现在起，有一种数据类型叫 `struct Smartphone`，它由一个字符串、一个整数和一个浮点数组成。”
> > > - `struct Smartphone* ptr;`** 的作用**：
> > 这是在定义一个**“导航仪/钥匙”**。它申请了一个空间用来存放地址，这个地址指向的地方必须是一个 `struct Smartphone` 类型的盒子。
> > > - **缺点**：每次使用都必须带上 `struct` 关键字。如果你直接写 `Smartphone myPhone;`，编译器会报错，因为它不认识 `Smartphone` 这个单词，它只认 `struct Smartphone`。
> > > > 💡 **第二个结构体**
> > >
> > > - **定义了实物模具**：
> > 和第一种一样，定义了 `struct Smartphone`。
> > > - **定义了实物别名 **`Phone`：
> > **作用**：让 `Phone` 等价于 `struct Smartphone`。
> > **好处**：以后定义变量只需写 `Phone myPhone;`。它把原本两个单词的类型名缩减为一个，用起来像 `int` 一样方便。
> > > - **定义了指针别名 **`Phoneptr`：
> > **作用**：让 `Phoneptr` 等价于 `struct Smartphone*`。
> > **好处**：定义指针时只需写 `Phoneptr ptr;`。它把“星号 ”隐藏在了别名里。
> > > 
## 💻代码

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
// 使用栈的先进后出可以直接把倒序的给打印出来
typedef struct Stack {
    // 为什么不可以定义两个next,不都是要指向下一个地址吗
    struct ListNode* val;
    struct Stack* next;
} StackNode;
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    // 申请内存
    struct ListNode* dummy = malloc(sizeof(struct ListNode));
    if (dummy == NULL)
        return NULL;
    // 申请完之后要初始化
    dummy->val = 0;
    dummy->next = head;
    // top 始终指向最后进入栈的元素
    StackNode* top = NULL;
    struct ListNode* curr = dummy;
    // 需要把链表的元素存进栈里面
    while (curr) {
        StackNode* temp = malloc(sizeof(StackNode));
        if (temp == NULL)
            return NULL;
        temp->val = curr; // 把整个节点的地址给temp保存
        temp->next = top;
        top = temp;
        curr = curr->next;
    }
    // 从最后面开始出栈保留最后一个出栈的元素
    for (int i = 0; i < n; i++) {
        StackNode* tmp = top; // 1. 抓稳要删的
        top = top->next;      // 2. 移到下一个
        free(tmp);
    }
    struct ListNode* prev = top->val;
    prev->next = prev->next->next;
    struct ListNode* ans = dummy->next;
    free(dummy);
    return ans;
}
```

