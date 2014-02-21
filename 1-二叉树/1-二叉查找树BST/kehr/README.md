#<center>二叉查找树</center>
---

##1 介绍
二叉查找树（Binary Search Tree），也称有序二叉树（ordered binary tree）,排序二叉树（sorted binary tree），是指一棵空树或者具有下列性质的二叉树：  
>1. 若任意节点的左子树不空，则左子树上所有结点的值均小于它的根结点的值；    
>2. 任意节点的右子树不空，则右子树上所有结点的值均大于它的根结点的值；  
>3. 任意节点的左、右子树也分别为二叉查找树。  
>4. 没有键值相等的节点（no duplicate nodes）。  

##2 任务
实现一个二叉查找树，要求实现以下方法：
```cpp
	typedef int KEY_TYPE;
	typedef struct Node{
		KEY_TYPE key;
		struct Node* lchild;
		struct Node* rchild;
	}Node;
```

*	create  创建二叉查找树
*   	insert	插入一个新的值到已存在的二叉查找树中
*	search	通过值查找一个节点
*	delete  通过值删除一个节点
*	inOrder 中序遍历该树
##3 实现
<center><img src="./img/bst.png"/></center>

实现案例：可以参考![这里](http://jpkc.lit.edu.cn/ds/admin/UploadFiles/20129215473684.avi)
>###3.1 创建BST

>###3.2 插入BST

>###3.3 查找BST

>###3.4 删除BST

>###3.5 中序遍历BST  

##4 小结