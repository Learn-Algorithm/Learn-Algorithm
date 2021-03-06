Learn-Algorithm作业——AVL树
=======
##使用AVL树的案例
+  [Flumotion](https://github.com/offlinehacker/flumotion) - 一个流媒体服务器，项目中使用AVL树来存储IP地址等数据 [具体代码](https://sourcegraph.com/github.com/offlinehacker/flumotion/symbols/python/flumotion/common/avltree/AVLTree#examples)
+  [consistent-hashing](https://github.com/domnikl/consistent-hashing) - 一个一致哈希表的Ruby实现  [具体代码](https://sourcegraph.com/github.com/domnikl/consistent-hashing/symbols/ruby/gem/ConsistentHashing/AVLTree#examples)

##实现AVL树时遇到的问题
在写`Delete()`方法的时候，我仿照`Insert()`方法，写了删除节点后维持树平衡的算法，其中考虑了删除代码后会出现`L-L`，`L-R`，`R-R`，`R-L`的情况。但是测试的时候发现删除节点老是会出现`segmentation fault`而异常退出，分析之后，发现删除节点的时候是不可能出现`L-R`，`R-L`的情况的，它们只可能在插入节点时出现，所以删除节点后，若节点出现不平衡，则只需执行相应的左旋或右旋即可。