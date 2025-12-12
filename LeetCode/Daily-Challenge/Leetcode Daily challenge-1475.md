# [1475. 商品折扣后的最终价格](https://leetcode.cn/problems/final-prices-with-a-special-discount-in-a-shop/)**(12.8)**

给你一个数组 `prices` ，其中 `prices[i]` 是商店里第 `i` 件商品的价格。
商店里正在进行促销活动，如果你要买第 `i` 件商品，那么你可以得到与 `prices[j]` 相等的折扣，其中 `j` 是满足 `j > i` 且 `prices[j] <= prices[i]` 的 **最小下标** ，如果没有满足条件的 `j` ，你将没有任何折扣。
请你返回一个数组，数组中第 `i` 个元素是折扣后你购买商品 `i` 最终需要支付的价格。

## 难点

<details><summary>为什么要使用栈来解决,什么时候适合用栈</summary>

栈既有位置关系又有大小关系,

### 总结：什么时候用栈？
以后只要做题看到以下关键词，**哪怕你不会写，先往“单调栈”想**：
1. **“右边第一个比我大/小的元素”** 
1. **“左边第一个比我大/小的元素”**。
1. **“消除”、“配对”** (比如括号匹配 `(())`，或者消消乐)。

</details>

<details><summary>为什么使用队列不适合</summary>

**只有“后进先出”（LIFO）的栈，才能让你永远先拿到“刚放进去的”、“离当前最近的”那个元素进行比较。**
如果是队列（FIFO），你会先拿到 `8`，这就不符合“找最近邻居”的逻辑了

</details>

> 💡 ****
>
> 
> ## 解法一:直接遍历
> > > 💡 **从第 *i*+1 件商品开始依次向后遍历，直到找到第一个满足 *prices*[*j*]≤*prices*[*i*] 的下标 *j* 即可求出该物品的最终折扣价格**
> >
> > 
> ```java
> class Solution {
>     public int[] finalPrices(int[] prices) {
>         int n = prices.length;
>         int[] a = new int[n];
>         for (int i = 0; i < n; ++i) {
>             int discount = 0;
>             for (int j = i + 1; j < n; ++j) {
>                 if(prices[j] <= prices[i]){
>                     discount = prices[j];
>                     break;
>                 }
>             }
>             a[i] = prices[i] - discount;
>         }
>         return a;
>     }
> }
> ```
> > 💡 ****
>
> 
> ## 解法二:单调栈
> > 
> ```java
> class Solution {
>     public int[] finalPrices(int[] prices) {
>         int[] result = new int[prices.length];
>  
>         int[] stack = new int[prices.length]; 
>         int top = -1; // 栈顶指针，-1表示空
>      
>         for (int i = 0; i < prices.length; i++) result[i] = prices[i];
> 
>         for (int i = 0; i < prices.length; i++) {
>             // stack[top] 就是 peek()
>             while (top != -1 && prices[i] <= prices[stack[top]]) {
>                 
>                 // stack[top--] 就是 pop()
>                 int index = stack[top--]; 
>                 
>                 result[index] = prices[index] - prices[i];
>             }
>             // stack[++top] 就是 push()
>             stack[++top] = i;
>         }
>         return result;
>     }
> }
> ```
> 