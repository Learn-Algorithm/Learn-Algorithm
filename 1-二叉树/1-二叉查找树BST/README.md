# 第一期-1 「二叉查找树(BST)」#

### 概念：

二叉查找树（Binary search tree），也叫有序二叉树（Ordered binary tree）,排序二叉树(Sorted binary tree)。是指一个空树或者具有下列性质的二叉树：

1.	若任意节点的左子树不为空，则左子树上所有的节点值小于它的根节点值
2.	若任意节点的右子树不为空，则右子树上所有节点的值均大于它的根节点的值
3.	任意节点左右子树也为二叉查找树
4.	没有键值相等的节点

### 性能分析：

查找代价：

*	树中每个节点左右子树高度大致相同时，树高为logN,则平均查找长度与logN成正比，查找的平均时间复杂度在O(logN)数量级上
*	当先后插入的关键字有序时，BST退化成单支树结构，此时树高N，平均查找长度为(N+1)/2，平均复杂度在O(N)数量级上

插入代价：

*	新节点插入到树的叶子上，完全不需要改变树中的原有的节点组织结构，插入一个节点的代价与查找一个不存在的数据的代价完全相同。


总结：

*	最好时间复杂度O(logN)
*	最坏时间复杂度O(N)
*	插入删除操作算法简单，时间复杂度与查找差不多

### 最坏时间过长改进方案（后续会跟进学习）：

1.	SBT
2.	AVL
3.	Red-Black 

### 应用：

*	Linux寄存器cache查询（[regcache_lookup_reg](https://github.com/mirrors/linux-2.6/blob/10d0c9705e80bbd3d587c5fad24599aabaca6688/drivers/base/regmap/regcache.c#L570)）就用了二叉查找树的结构。
*	C++ STL,C#,Java set和map的搜索方法就是使用的BST。


------------

## 任务：

实现一个二叉查找树，要求实现以下方法：

	typedef int KEY_TYPE;
	typedef struct Node{
		KEY_TYPE key;
		struct Node* lchild;
		struct Node* rchild;
	}Node;


*	create  创建二叉查找树
*	insert	插入一个新的值到已存在的二叉查找树中
*	search	通过值查找一个节点
*	delete  通过值删除一个节点
*	inOrder 中序遍历该树

PS：参数请自行传入，函数名可改变为自己习惯的风格，但是：请保持函数顺序

任务截止日期为：2014-2-23 夜里11点30

提交方法：

*	首先请`fork`这个项目到自己的仓储中
*	`git clone`自己的仓储到本地
*	在`1-二叉树/1-二叉查找树BST/`目录下创建`自己id`的文件夹，如`daimajia`
*	在自己文件夹下书写代码，完成后`git push`到自己仓储并发起`pull request`

如果对`git`及`github`不熟悉的同学，可以在此学习：[http://www.worldhello.net/gotgithub/](http://www.worldhello.net/gotgithub/)，也可以在微信群或者teambition上发起讨论。





