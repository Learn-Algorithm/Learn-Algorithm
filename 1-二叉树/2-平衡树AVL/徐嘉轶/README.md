AVL树的应用就可以用来做字典的查找吧。

碰到的问题主要在调整height上，现在还不是很清晰，觉得算法可以是基于被调整的节点，在调整之后，再去递归的计算树的高度，但觉得被调整的节点高度变化后，也有可能影响到其祖先节点，只是目前写的用例没有碰到而已。

这里贴一个avl树插入与删除的Flash动画供大家学习 http://www.qmatica.com/DataStructures/Trees/AVL/AVLTree.swf