# 平衡树AVL

###为什么需要平衡树？

平衡树是一种改进的二叉查找树，一般的[二叉查找树](https://github.com/Learn-Algorithm/Learn-Algorithm/blob/master/1-%E4%BA%8C%E5%8F%89%E6%A0%91/1-%E4%BA%8C%E5%8F%89%E6%9F%A5%E6%89%BE%E6%A0%91BST/README.md)有两个特性：

1、	树中每个节点左右子树高度大致相同时，树高为logN,则平均查找长度与logN成正比，查找的平均时间复杂度在O(logN)数量级上

2、 	当先后插入的关键字有序时，BST退化成单支树结构，此时树高N，平均查找长度为(N+1)/2，平均复杂度在O(N)数量级上

为了维持查找树较好的查找和插入速度，缩短所用时间，我们需要对特性2进行改进，使之不要退化成单支树结构，争取使左右树高大致相同。

AVL就是对第二点进行的改进，通过不断调整子树的高度使之不出现单支的情况，维持在O(logN)的优良特性上。

### 算法背景

AVL树得名于它的发明者G.M. Adelson-Velsky和E.M. Landis，他们在1962年的论文《An algorithm for the organization of information》中发表了它。

### 算法细节

AVL树规定：

1.	AVL树的任何两个子树的高度最大差别为1（即:使左右子树高度大致相同）

### 算法特性

查找、插入和删除在平均和最坏情况下都是O（log n）

### 算法核心方法

对不平衡的树（子树高度差大于1）进行旋转来维持平衡

Google: <https://www.google.com.hk/#q=avl%E6%A0%91&safe=strict>

最好先看下维基百科：<http://zh.wikipedia.org/wiki/AVL%E6%A0%91>

### 此次任务：

1.	实现一个AVL树
2.	寻找真实项目中AVL树的使用案例，写在一个README.md中，同时README.md中可以附上自己在算法实现中发现的一些问题以及自己踩到的坑。大家分享出来，相互学习，以后多多留意！

数据结构和必须实现的方法：
	
	typedef int KEY_TYPE;
	typedef struct AVL{
		KEY_TYPE key;
		int height;
		struct AVL* lchild;
		struct AVL* rchild;
	}AVL;

	AVL* RR_Rotate(AVL* k2);
	AVL* LL_Rotate(AVL* k2);
	AVL* LR_Rotate(AVL* k3);
	AVL* RL_Rotate(AVL* k3);
	
	AVL* Insert(AVL* root, KEY_TYPE key);
	AVL* Delete(AVL* root, KEY_TYPE key);
	void InOrder(AVL* root);

完成时间：2014年3月2日 晚上11:30之前

下一期预告：红黑树




