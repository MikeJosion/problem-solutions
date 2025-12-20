# [**82. 删除排序链表中的重复元素 II**](https://leetcode.cn/problems/remove-duplicates-from-sorted-list-ii/)

给定一个已排序的链表的头 head ， 删除原始链表中所有重复数字的节点，只留下不同的数字 。返回 已排序的链表 。

## 示例

![示意图](https://assets.leetcode.com/uploads/2021/01/04/linkedlist1.jpg)

## 实现代码

```c

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteDuplicates(struct ListNode* head) {
    // 如果为空,或者只有一个元素直接返回
    if (head == NULL || head->next == NULL)
        return head;
    //如果头节点和下一个重复,需要一个dummy来提供head
    //head 不是“节点”，它只是一个“指针变量的名字”
    struct ListNode* dummy = malloc(sizeof(struct ListNode));
    dummy -> val = 0;
    dummy ->next = head;
    // 定义一个探险家
    struct ListNode* curr = head;
    // //当前要保留的最后的节点
    struct ListNode* prev = dummy;

    // 循环删除重复的元素
    while (curr != NULL && curr->next != NULL) {
        //寻常的方法不好找到开始重复的前一个节点
        if (curr->val == curr->next->val) {
            //先找到重复的值
            int dup = curr->val;
            //如果链表不为空且curr的值等于重复的目标值
            while(curr != NULL && curr->val == dup){
                //拿temp获得curr的指针地址
                struct ListNode* temp = curr;
                //找下一个节点是否重复
                curr = curr ->next;
                //释放内存
                free(temp);
            }
            //让最后一个节点指向删除之后没重复的节点
            prev->next = curr;
        }else{
            prev = curr;
            curr = curr->next;
        }
    }
    struct ListNode* result = dummy->next;
    free(dummy);
    return result;
}

```
