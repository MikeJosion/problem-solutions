# [**83. 删除排序链表中的重复元素**](https://leetcode.cn/problems/remove-duplicates-from-sorted-list/)

给定一个已排序的链表的头 head ， 删除所有重复的元素，使每个元素只出现一次 。返回 已排序的链表 。

## 示例

![alt text](image-1.png)

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
    //如果为空直接返回
    if(head == NULL)return NULL;
    //头节点不可以乱动所以需要一个探险家
    struct ListNode* curr = head;
    //开始判断删除重复元素,只要当前节点和后面不为空就进去判断
    while(curr != NULL && curr->next != NULL){
        //需要一个暂时的节点来存储curr的下一个节点,方便后面释放内存
        struct ListNode* temp = curr->next;
        if(curr->val == temp->val){
            curr->next = temp->next;
            free(temp);
        }else{
            curr = curr->next;
        }
    }
    return head;
}

```
