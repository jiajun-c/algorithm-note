# 数据结构时间复杂度分析

|数据结构|底层实现|插入|删除|查询|
|-|-|-|-|-|
|map|红黑树|Olog(n)|Olog(n)|Olog(n)
|unordered_map|hash表|O(1)|O(1)|O(1)|
|set|红黑树|Olog(n)|Olog(n)|Olog(n)|
|unordered_set|hash表|O(1)|O(1)|O(1)|
|list|双向链表|O(1)|O(1)|O(n)|

在需要O(1)复杂度的题目中，应该使用以hash表为底层实现的数据结构，通常还会结合链表等数据结构进行实现。