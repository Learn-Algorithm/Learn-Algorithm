# Splay树的原理

------

Splay树和AVL树一样都是为了保证排序二叉树的平衡而设计的。与AVL每次插入和删除操作后进行i平衡操作不同，Splay通过Splay操作将最近访问过的节点旋转至根节点，这样很好的保证了局部性原理（上次访问的元素下次可能依然会访问，和cache原理一样）。

Splay操作同样通过旋转来完成，基本的旋转包括：

 - Right_Rotate() 
 - Left_Rotate()
 - RR_Rotate()
 - LL_Rotate()
 - LR_Rotate()
 - RL_Rotate()

参考文章如下：
http://blog.csdn.net/niuox/article/details/8018280
