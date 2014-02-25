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
```c++
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

![BST](./img/bst.png "本文使用的BST")

###3.1 创建BST

代码：

```cpp
void create_bst(Tree &T)
{
    KEY_TYPE key;
    T = NULL;
    cout<<"输入要创建的树节点(end whith -1 )：";
    while(true)
    {
        cin>>key;
        if ( -1 == key)
        {
            break;
        }
        insert_bst(T,key);
    }
}
```  
>从输入获取节点的值，动态生成节点。	

###3.2 插入BST

代码：

```cpp
void insert_bst(Tree &T, KEY_TYPE key)
{
    if (T == NULL)
    {
        if ((T = (Tree)malloc(sizeof(Node))) == NULL)
        {
            cout<<"创建节点失败！"<<endl;
            exit(1);
        }
        cout<<"创建根点："<<key<<endl;
        T->key = key;
        T->lchild = NULL;
        T->rchild = NULL;
    }
    else
    {
        if (key < T->key)
        {
            cout<<"插入左节点："<<key<<endl;
            insert_bst(T->lchild, key);
        }
        else if (key > T->key)
        {
            cout<<"插入右节点："<<key<<endl;
            insert_bst(T->rchild, key);
        }
        else
        {
            cout<<"节点已存在，无需重复插入！"<<endl;
        }
    }
}  
```
向BST中插入节点的步骤：	
>1. 如果T为空，则将节点key作为根节点插入，否则2  
>2. 如果`key < T->key`，将key插入T左节点，否则3  
>3. 如果`key > T->key`，将key插入T右节点，否则4  
>4. 节点已经存在，不重复插入。  

###3.3 查找BST

代码：  

```cpp  
void search_bst(Tree T, KEY_TYPE key)
{
    if (NULL == T)
    {
        cout<<"节点为空，查找失败！"<<endl;
    }
    else
    {
        if (key < T->key)
        {
            cout<<"在左子树中查找："<<key<<endl;
            search_bst(T->lchild, key);
        }
        else if (key > T->key)
        {
            cout<<"在右子树中查找："<<key<<endl;
            search_bst(T->rchild, key);
        }
        else
        {
            cout<<"------------------------查找成功！BST中存在节点："<<key<<endl;
        }
    }
}
```
在BST中查找节点步骤：  
>1. 如果T为空，查找失败，否则2
>2. 如果key小于T的key值，查找左子树，否则3
>3. 如果key大于T的key值，查找右子树，否则4
>4. 查找成功。

###3.4 删除BST

删除BST节点的三种情况演示可以参考[这里][1]  

代码：  

```cpp  
void delete_bst(Tree &T, KEY_TYPE key)
{
    if (NULL == T)
    {
        return;
    }
    else
    {
        if (key == T->key)
        {
            delete_node(T);
            cout<<"------------------------节点"<<key<<"，删除成功！"<<endl;
        }
        else if (key < T->key)
        {
            delete_bst(T->lchild,key);
        }
        else
        {
            delete_bst(T->rchild,key);
        }
    }
}
void delete_node(Tree &T)
{
    if(NULL == T->lchild)         //左子树为空，右子树上升
    {
        Tree q = T;
        T = T->rchild;
        free(q);
    }
    else if(NULL == T->rchild)   //右子树为空则，左子树上升
    {
        Tree q = T;
        T = T->lchild;
        free(q);
    }
    else                        //左右子树均不空
    {
        Tree temp = T;
        Tree f = T->rchild;     //定位到待删节点的右子树
        Tree s = T->lchild;     //定位到待删节点的左子树
        
        T = T->rchild;          //待删除的节点的右节点上升

        while(f->lchild)        //查找右子树的最小节点
        {
            f = f->lchild;
        }

        f -> lchild = s;        //将待删节点的左子树接到其右子树的最小节点上

        free(temp);             //删除待删节点
    }
}
```  
<p id='del'></p>
删除BST节点步骤：  
>1. 如果待删除节点为叶节点，直接删除，否则2  
>2. 如果待删节点只有左子树（右子树），则待删节点父节点直接指向其左子树（右子树）。即，左子树（右子树）上升，替换待删节点位置。否则3  
>3. 如果待删节点左右子树均存在，则将其右子树的根节点上升，替换待删节点位置；其左子树接在待删节点右子树最小节点上，即，左子树的左叶子节点上。    
  
###3.5 中序遍历BST  

```cpp
void in_order(Tree T)
{
    if (T != NULL)
    {
        in_order(T->lchild);
        cout<<T->key<<" "  ;
        in_order(T->rchild);
    }
}
```  
>二叉树中序递归遍历，你懂的，不解释～

##4 代码测试
主函数：
```cpp
int main(void)
{
    Tree T;
    KEY_TYPE key;
    int flag;

    //创建二叉搜索树
    create_bst(T);
    cout<<"------------------------BST创建成功！"<<endl;

    while (true)
    {
        cout<<"\n选项：[0].退出   [1].查找节点    [2].删除节点    [3].中序遍历BST"<<endl;
        cout<<"输入：";
        cin>>flag;

        if (0 == flag)
        {
            break;
        }

        switch(flag)
        {
            case 1:
            {
                cout<<"请输入你要查找的节点：";
                cin>>key;
                search_bst(T,key);
                break;
            }
            case 2:
            {
                cout<<"请输入你要删除的节点：";
                cin>>key;
                delete_bst(T,key);
                break;
            }
            case 3:
            {
                cout<<"------------------------中序遍历BST结果：";
                in_order(T);
                cout<<endl;
                break;
            }
            default:
            {
                cout<<"------------------------请输入正确选项！"<<endl;
                break;
            }

        }


    }

    return 0;
}
```

测试结果：  
```bash
➜  kehr git:(master) ✗ > ./bst
输入要创建的树节点(end whith -1 )：6 3 7 2 4 10 1 5 8 9 -1
创建根点：6
插入左节点：3
创建根点：3
插入右节点：7
创建根点：7
插入左节点：2
插入左节点：2
创建根点：2
插入左节点：4
插入右节点：4
创建根点：4
插入右节点：10
插入右节点：10
创建根点：10
插入左节点：1
插入左节点：1
插入左节点：1
创建根点：1
插入左节点：5
插入右节点：5
插入右节点：5
创建根点：5
插入右节点：8
插入右节点：8
插入左节点：8
创建根点：8
插入右节点：9
插入右节点：9
插入左节点：9
插入右节点：9
创建根点：9
------------------------BST创建成功！

选项：[0].退出   [1].查找节点    [2].删除节点    [3].中序遍历BST
输入：1
请输入你要查找的节点：10
在右子树中查找：10
在右子树中查找：10
------------------------查找成功！BST中存在节点：10

选项：[0].退出   [1].查找节点    [2].删除节点    [3].中序遍历BST
输入：2
请输入你要删除的节点：3
------------------------节点3，删除成功！

选项：[0].退出   [1].查找节点    [2].删除节点    [3].中序遍历BST
输入：3
------------------------中序遍历BST结果：1 2 4 5 6 7 8 9 10 

选项：[0].退出   [1].查找节点    [2].删除节点    [3].中序遍历BST
输入：0
➜  kehr git:(master) ✗ > 

```  

##5 小结  

参照[维基百科][2]，代码整体写下来比较顺，但是还是存在一些问题。

删除BST节点部分，[百科][3]上包括书上的，读起来都比较拗口,自己简单的描述了一下,大致就是这个步骤。而且实现起来也有不同的版本。个人觉得百科上的代码要好一些，指针的指向变化比较明确。我写的与之不同，对于`T = T->lchild`这一句理解的还有问题，但是照着思路写出代码后，程序是能够正常运行的。      

自己写的代码，自己不理解感觉很难过。各位，求讨论！[我的blog][4]

[1]: http://jpkc.lit.edu.cn/ds/admin/UploadFiles/20129215473684.avi "删除节点视频"
[2]: http://zh.wikipedia.org/wiki/%E4%BA%8C%E5%85%83%E6%90%9C%E5%B0%8B%E6%A8%B9 "wikipedia abou BST"
[3]:http://zh.wikipedia.org/wiki/%E4%BA%8C%E5%85%83%E6%90%9C%E5%B0%8B%E6%A8%B9#.E5.9C.A8.E4.BA.8C.E5.8F.89.E6.9F.A5.E6.89.BE.E6.A0.91.E5.88.A0.E9.99.A4.E7.BB.93.E7.82.B9.E7.9A.84.E7.AE.97.E6.B3.95 "维基百科，BST删除节点"  
[4]: http://ikehr.com 
