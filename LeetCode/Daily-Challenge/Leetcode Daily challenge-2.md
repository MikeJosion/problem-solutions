# [2. 两数相加](https://leetcode.cn/problems/add-two-numbers/)**(12.16)**

给你两个 **非空** 的链表，表示两个非负的整数。它们每位数字都是按照 **逆序** 的方式存储的，并且每个节点只能存储 **一位** 数字。
请你将两个数相加，并以相同形式返回一个表示和的链表。
你可以假设除了数字 0 之外，这两个数都不会以 0 开头。

## 难点

<details><summary>1️⃣ 为什么第一个节点要「特殊处理」？</summary>


```c
if (head == NULL) {
head = tail = node;
}
空链表时，tail 是 NULL，不能直接用
```

</details>

<details><summary>2️⃣ 最高位还有进位，如何正确补节点？</summary>

> 💡 ****
>
> 
> ```c
> ❌ 错误写法（早期常见）：
> 
> if (l1 != NULL || l2 != NULL || carry > 0)
> 
> ✅ 正确理解：
> 
> 进位只可能在 while 循环结束后 产生
> 
> 出了 while：
> 
> l1 != NULL ❌（已经遍历完）
> 
> l2 != NULL ❌（已经遍历完）
> ✅ 正确判断：
> if (carry > 0) {
> // 补一个新节点
> }
> ```
> > 💡 ****
>
> - 出 while 之后
> > - `l1 != NULL` ❌
> > - `l2 != NULL` ❌
> > 👉 **这两个判断已经没有任何意义了**
> 

</details>

<details><summary>3️⃣ 为什么每次新建节点都要 `next = NULL`？</summary>

> 💡 **新节点的 `next` 必须显式设为 `NULL`，否则它可能指向一块“垃圾内存”,**
>
> - `malloc` **只分配内存，不初始化**
> > - `node->next` 里一开始是 **随机值**
> 
</details>


## 🧠 核心知识点总结
> 💡 ****
>
> 
> ## ✅ 链表遍历与「对齐技巧」
> > 
> ### 不同长度链表的处理方式：
> > 
> ```c
> int a = l1 ? l1->val :0;
> int b = l2 ? l2->val :0;
> ```
> > 含义：
> > - 链表短了 → 当作补 0
> > - 不需要提前算长度
> > - 一行代码解决对齐问题
> > 
> ## 🔐 链表指针安全三原则
> > 1. **用之前先判空**
>   
>   ```c
>   if (l1) l1 = l1->next;
>   ```
>   > 1. **新节点一定初始化**
>   
>   ```c
>   node->next =NULL;
>   ```
>   > 1. **尾节点必须指向 NULL**
>   
>   ```c
>   tail->next =NULL;
>   
>   ```
>   
```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
// sum是当前位的真实相加结果  sum = a + b + carry
// cur当前链表节点的值  cur = sum % 10
// carry表示进位0或者1 carry  = sum / 10
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    // 先将链表的头尾定义为空,这个就是拿来记录答案的链表
    struct ListNode *head = NULL, *tail = NULL;
    int carry = 0, sum = 0, cur = 0;
    //判断可以直接写l1 || l2
    while (l1 != NULL || l2 != NULL) {
        int a = l1 ? l1->val : 0;
        int b = l2 ? l2->val : 0;
        sum = a + b + carry;
        carry = sum / 10;
        cur = sum % 10;
        struct ListNode* node = malloc(sizeof(struct ListNode));
        //如果head==NULL说明一个还没有插入,这里使用的是尾插法
        if (head == NULL) {
            node->val = cur;
            node->next = NULL;
            head = tail = node;
        } else {
            tail->next = node;
            node->val = cur;
            tail = node;
            tail->next = NULL;
        }
        if(l1 != NULL){
            l1 = l1->next;
        }
        if(l2 != NULL){
            l2 = l2->next;
        }
    }
    //要注意如果最后两个一样长而且后面进一,两个都为空但是进一没空间存储了
     if(carry > 0){
            tail->next = malloc(sizeof(struct ListNode));
            tail->next->val = carry;
            tail->next->next = NULL;
        }
        return head;
}
```




