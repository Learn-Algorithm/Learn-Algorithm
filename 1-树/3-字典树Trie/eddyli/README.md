## 字典树 ##
首先看了一下Double Array的实现方法，感觉挺复杂的，一时半会理解不了，先收藏一下吧
[http://linux.thai.net/~thep/datrie/datrie.html](http://linux.thai.net/~thep/datrie/datrie.html)

这次就先使用普通的实现方法简单实现了下。

关于字典树的面试题，在网上找了几个

1. 一个文本文件，大约有一万行，每行一个词，要求统计出其中最频繁出现的前10个词，请给出思想，给出时间复杂度分析。
2. 有一堆访问本站的来源IP地址:
1.1.1.1
.
.
.
.
255.255.255.255
如何组织这些数据以便快速的进行匹配,查询某一个IP地址,如145.345.23.445是否访问过本站?


来源：
[http://blog.csdn.net/v_july_v/article/details/6897097](http://blog.csdn.net/v_july_v/article/details/6897097)