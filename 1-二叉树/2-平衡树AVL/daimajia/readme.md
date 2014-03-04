总结：
====

这次这个AVL树写的我异常的蛋疼... 总是小错误不断。不仅仅AVL的过程麻烦，而且自己对迭代的循环过程还是有些拿捏不住，AVL的插入做起来还是比较顺畅的

就是这个删除...

在基本上犯了所有的错误后，终于找到一条归路，单步调试不下二十遍，bug一点儿点儿的改，思路也越来越清晰，毕竟想着自己是活动的发起人，要是我也稀里糊涂的开始就这么着了，那这个活动迟早得完蛋。

就这样...终于搞明白了每一个细节。

------------------

## 遇到的错误:

Mac下`fflush(stdin)` 完全不Work啊！妈蛋！更多细节看这里：<http://blog.csdn.net/cxsjabcabc/article/details/7552447>

再分享一个关于EOF的：<http://ocw.nctu.edu.tw/course/icp011/ch02.pdf>

## 关于AVL Tree的应用:

用AVL Tree来为文本建立索引并且统计单词个数：<http://courses.cs.vt.edu/cs2604/Summer2000/projects/AVLIndex.pdf>