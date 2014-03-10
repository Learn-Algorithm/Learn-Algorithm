# trie tree 字典数


Trie树的基本性质可以归纳为：

* 根节点不包含字符，除根节点意外每个节点只包含一个字符。
* 从根节点到某一个节点，路径上经过的字符连接起来，为该节点对应的字符串。
* 每个节点的所有子节点包含的字符串不相同。

至于结点对儿子的指向，一般有三种方法：

* 对每个结点开一个字母集大小的数组，对应的下标是儿子所表示的字母，内容则是这个儿子对应在大数组上的位置，即标号；
* 每个结点挂一个链表，按一定顺序记录每个儿子是谁；
* 使用左儿子右兄弟表示法记录这棵树。


字典树结构:

amy	56
ann	15
emma	30
rob	27
roger	52

```
              .
      /       |      \
     a        e       r
   /   \      |       |
  m     n     m       o
  |     |     |     /   \
  y     n     m    b     g
  |     |     |    |     |
\0 56 \0 15   a  \0 27   e
              |          |
            \0 30        r
                         |
                       \0 52
```


使用左儿子右兄弟表示法记录这棵树


```
	|
  a --------- e ----- r
  |           |       |
  m --- n     m       o
  |     |     |       |
  y     n     m       b ----- g
  |     |     |       |       |
\0 56 \0 15   a     \0 27     e
              |               |
            \0 30             r
                              |
                            \0 52

```

## 资料


* [Trie](http://www.cs.bu.edu/teaching/c/tree/trie/)
* [http://dongxicheng.org/structure/trietree/](数据结构之Trie树)
* http://www.mathcs.emory.edu/~cheung/Courses/323/Syllabus/Text/trie01.html
* [tengine trie tree useragent](http://tengine.taobao.org/download/programmer-201209-Tengine.pdf)
* [Double array trie](http://linux.thai.net/~thep/datrie/datrie.html)

