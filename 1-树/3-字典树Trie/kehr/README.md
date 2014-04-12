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
    trietree root = new_node ('#');
    int count, flag;
    char* word;

    while (true)
    {
        printf ("\n[0] exit    [1] insert    [2] remove    [3] query\n");
        printf ("option:");
        scanf ("%d",&flag);

        if (0 == flag) break;

        switch (flag )
        {
            case 1:

                printf ("\n输入待插入的单词，以空格分开（end with EOF）:");

                while (scanf("%s",word) != EOF)
                {
                    Insert (&root, word);
                }

                break;

            case 2:

                printf ("\n输入待删除的单词：");
                scanf ("%s",word);

                Remove_not_free(&root,word);

                break;

            case 3:

                printf ("\n输入待查询的单词：");
                scanf ("%s",word);

                count = Query (&root,word);

                if (!count)
                {
                    printf ("\n单词不存在！\n");
                }
                else
                {
                    printf ("\n%s 的引用共有 %d 个。\n",word,count);
                }

                break;

            default:

                printf ("Invalid option!\n");

                break;
        }
    }

    return 0;
}

```

####result:

```bash

➜  kehr git:(master) ✗ > ./trie

[0] exit    [1] insert    [2] remove    [3] query
option:1

输入待插入的单词，以空格分开（end with EOF）:a ab abc abc abc
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

[0] exit    [1] insert    [2] remove    [3] query
option:3

输入待查询的单词：abc
word=abc
tree->count=1
word=bc
tree->count=1
word=c
tree->count=3

abc 的引用共有 3 个。

[0] exit    [1] insert    [2] remove    [3] query
option:2

输入待删除的单词：abc
remove--word:abc
remove--word:bc
remove--word:c
remove--tree--from--count=3
remove--tree--to----count=2

[0] exit    [1] insert    [2] remove    [3] query
option:3

输入待查询的单词：abc
word=abc
tree->count=1
word=bc
tree->count=1
word=c
tree->count=2

abc 的引用共有 2 个。

[0] exit    [1] insert    [2] remove    [3] query
option:2

输入待删除的单词：ab
remove--word:ab
remove--word:b
remove--tree--from--count=1
remove--tree--to----count=0

[0] exit    [1] insert    [2] remove    [3] query
option:3

输入待查询的单词：ab
word=ab
tree->count=1
word=b
tree->count=0

单词不存在！

[0] exit    [1] insert    [2] remove    [3] query
option:0
➜  kehr git:(master) ✗ > 

```

[1]:http://www.cs.waikato.ac.nz/Teaching/COMP317B/Week_4/digital_search_tree.html

