# 2.2 两个链表的公共节点

## 题目描述

给定两个单链表的头指针 headA 和 headB，找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 NULL。

```
示意图：两个链表在节点 c1 处开始相交

A:     a1 -> a2 ──┐
                   ├──> c1 -> c2 -> c3
B: b1 -> b2 -> b3 ┘
```

题目数据 **保证** 整个链式结构中不存在环。函数返回结果后，链表必须 **保持其原始结构**。

> 对应 LeetCode 第 160 题「相交链表」

## 思路分析

### 方法：双指针（等距法）

**核心思想**：让两个指针走过相同的总路程，这样它们一定会在交点相遇。

设链表 A 独有部分长度为 `a`，链表 B 独有部分长度为 `b`，公共部分长度为 `c`：

- 指针 pA：走完 A 后转向 B 的头部，总路程 = `a + c + b`
- 指针 pB：走完 B 后转向 A 的头部，总路程 = `b + c + a`

两者路程相等，因此它们会同时到达交点（或同时到达 NULL）。

### 图示

```
第一轮：
  pA:  a1 -> a2 -> c1 -> c2 -> c3 -> [转到B头] b1 -> b2 -> b3 -> c1 ✓
  pB:  b1 -> b2 -> b3 -> c1 -> c2 -> c3 -> [转到A头] a1 -> a2 -> c1 ✓
                                                                    ↑ 相遇！
```

## 关键代码

```c
LNode* getIntersectionNode(LNode *headA, LNode *headB)
{
    if (headA == NULL || headB == NULL)
        return NULL;

    LNode *pA = headA;
    LNode *pB = headB;

    // 当 pA 和 pB 相遇时退出（不相交时两者同时为 NULL）
    while (pA != pB)
    {
        pA = (pA != NULL) ? pA->next : headB;
        pB = (pB != NULL) ? pB->next : headA;
    }

    return pA;
}
```

## 复杂度

- **时间复杂度**: O(n + m)，n 和 m 分别为两个链表的长度
- **空间复杂度**: O(1)，只使用了两个指针
