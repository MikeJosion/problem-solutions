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
    struct ListNode* val;
    struct Stack* next;
} Node;
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    // 如果要删除的是head节点之后的元素,链表的后半段会丢失,所以需要一个办法来使头节点和普通的节点都可以正常使用
    // 如果要删除的节点是头节点本身，dummy
    // 作为它的前驱，仍然可以把新的头节点正确连接并返回。
    struct ListNode* dummy = malloc(sizeof(struct ListNode));
    if (dummy == NULL)
        return NULL;
    dummy->val = 0;
    dummy->next = head;
    //使用我们定义的栈把链表放进去
    Node * top = NULL;
    struct ListNode * curr = dummy;
    while(curr){
        //申请内存写错:Node* temp = malloc(sizeof(Node*));
        //疑问:我申请的是结构指针对吧,所以Node*不应该是一个整体吗
        //你申请的是“Node 指向的结构体内存”，不是“Node 这个指针本身的内存”。*
        Node* temp = malloc(sizeof(Node));
        if(temp == NULL)return NULL;
        temp->next = top;
        top = temp;
        temp->val = curr;
        curr = curr->next;
    }
    //使用出栈来找
    for(int i = 0;i<n;i++){
        Node* temp = top;
        top = top->next;
        free(temp);
    }
    //使用链表删除的方法来删除指定的节点,现在是在要删除的前一个节点
    struct ListNode * prev = top->val;//要删除的前一个
    //还需要清空栈
    while (top) {
    Node* temp = top;
    top = top->next;
    free(temp);
}
    struct ListNode * freenode = prev->next;
    prev->next = freenode->next;
    free(freenode);
    struct ListNode* result = dummy->next;
    free(dummy);
    return result;
}

// 思路:是因为他是要删除倒数的元素,利用栈的后进先出特性，在出栈 N 次后，栈顶元素即为倒数第 N 个节点的前驱节点,又因为我的栈存的是链表节点的地址和下一个栈的地址,所以我在循环遍历到要删除节点的前一个节点,再利用链表删除节点的方法完成删除。,再把中间值保存的和前面的节点连接就可以返回正确答案

```


