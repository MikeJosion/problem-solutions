# 第四步：重点：余数重复为什么意味着永远不出现 0？

假设：
那么之后的余数序列会完全重复：
也就是说：
序列
会重复成为
循环只会重复这些值。


```java
class Solution {
    public int smallestRepunitDivByK(int k) {
        // 特判：k 为偶数或 5 的倍数，无解
        if (k % 2 == 0 || k % 5 == 0)  return -1;
        
        int remainder = 0;
        for (int len = 1; len <= k; len++) {
            remainder = (remainder * 10 + 1) % k;
            if (remainder == 0) return len;
        }
        return -1; 
    }
}
```

