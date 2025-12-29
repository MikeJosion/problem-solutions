# [**160. 相交链表**](https://leetcode.cn/problems/intersection-of-two-linked-lists/)

给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 null 。

图示两个链表在节点 c1 开始相交：

题目数据 保证 整个链式结构中不存在环。

注意，函数返回结果后，链表必须 保持其原始结构

## 示例

![示意图](https://assets.leetcode.cn/aliyun-lc-upload/uploads/2018/12/14/160_statement.png)

“两条路径不同起点，能不能 O(1) 找相遇点？”

👉 识别条件比模板本身重要

那你到底“该怎么记”？
✅ 推荐方式（非常适合你现在）
🧠 一个「口令级模板」

你只需要记住这 1 句话：

“两个指针走 A+B 和 B+A，第一次相等就是答案。”

## 实现代码

```java

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) {
 *         val = x;
 *         next = null;
 *     }
 * }
 */
public class Solution {
    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
         if(headA == null || headB == null)return null;
         ListNode p = headA;
         ListNode q = headB;
         while(p != q){
            p = (p == null) ? headB : p.next;
            q = (q == null) ? headA : q.next;
         }
         return p;
    }
}

```
