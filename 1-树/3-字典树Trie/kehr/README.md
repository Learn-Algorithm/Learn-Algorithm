##字典树（trie）

![图片来源：http://liuke.org/hdu-trietree-1.html](http://liuke.org/wp-content/uploads/2013/03/TrieTree.jpg)

###用途

我理解的字典树有两个很大的特点：  

1. 使用公共前缀，提高查询效率。  

2. 用于压缩存储。  

这两个特点一个是节约时间，一个是节约空间。其它的用途比如词频统计，都是基于这两个特点实现的。

###问题

这一题主要纠结在删除的部分上，实现的思路有两种：

1. 删除单词，但是不 free 节点，只减少最后一个黄色节点的 count（词频） 值。
   这种情况应该适合的情况是：在大量的数据中，热词被频繁「插入」。只减少黄色节点的 count 值，在下一次插入相同单词时，就不需要 malloc 。这样就减少了频繁的内存分配和释放操作，提高性能。

>操作：
>和查询步骤类似。遍历单词节点到最后的黄色节点。如果该节点的 count > 0，则 count-1； 如果 count == 0,则说明该单词以前存在过，但已经被删除，删除失败直接返回。

2. 删除单词，free节点，同时也减少最后一个黄色节点的 count（词频） 值。

>操作：
> 
>1.多个单词共享一个公共前缀。删除其中一个单词时，不删除公共前缀，只删除该单词除公共前缀以外的部分
> 
>2.如果没有公共前缀，且单词自由一个，直接删除该单词。全部free
> 
>3.如果删除的单词重复多个，只count--，不删除该单词。只有当该单词的count == 1 ，此时情况同`2.`，free该单词的全部节点。

这是我想到的情况，如果有什么遗漏和问题，欢迎大家补充。「直接提issue吧:smile:」

###应用

1. 一个比较简单的实现 [digital search tree][1] 

比较实用的应用还没找到，找到了再补充。

###测试

####main

```c

int main()
{
    trietree root = new_node('#');
    int count;

    printf("\n-------------------insert start\n");
    Insert(&root,"a");
    Insert(&root,"ab");
    Insert(&root,"abc");
    Insert(&root,"abc");
    Insert(&root,"abcd");
    Insert(&root,"abcd");
    Insert(&root,"abcde");
    Insert(&root,"abcdef");

    printf("\n-------------------query start\n");
    count = Query(&root,"abcdef");
    printf ("count=%d\n",count);

    printf("\n-------------------remove start\n");
    Remove_not_free(&root,"abcdef");

    printf("\n-------------------remove start\n");
    Remove_not_free(&root,"abcdef");

    printf("\n-------------------query start\n");
    count = Query(&root,"abcdef");
    printf ("count=%d\n",count);

    return 0;
}

```

####result:

```bash

➜  kehr git:(master) ✗ > ./trie 

-------------------insert start
key=a index=0
key=a index=0
key=b index=1
key=a index=0
key=b index=1
key=c index=2
key=a index=0
key=b index=1
key=c index=2
key=a index=0
key=b index=1
key=c index=2
key=d index=3
key=a index=0
key=b index=1
key=c index=2
key=d index=3
key=a index=0
key=b index=1
key=c index=2
key=d index=3
key=e index=4
key=a index=0
key=b index=1
key=c index=2
key=d index=3
key=e index=4
key=f index=5

-------------------query start
word=abcdef
tree->count=1
word=bcdef
tree->count=1
word=cdef
tree->count=2
word=def
tree->count=2
word=ef
tree->count=1
word=f
tree->count=1
count=1

-------------------remove start
remove--world:abcdef
remove--world:bcdef
remove--world:cdef
remove--world:def
remove--world:ef
remove--world:f
remove--tree--from--count=1
remove--tree--to----count=0

-------------------remove start
remove--world:abcdef
remove--world:bcdef
remove--world:cdef
remove--world:def
remove--world:ef
remove--world:f
your world does not exit !

-------------------query start
word=abcdef
tree->count=1
word=bcdef
tree->count=1
word=cdef
tree->count=2
word=def
tree->count=2
word=ef
tree->count=1
word=f
tree->count=0
count=0
➜  kehr git:(master) ✗ > 
```

[1]:http://www.cs.waikato.ac.nz/Teaching/COMP317B/Week_4/digital_search_tree.html

