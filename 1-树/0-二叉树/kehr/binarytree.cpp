/*************************************************************************
 * @File Name:    binarytree.cpp
 * @Author:       kehr
 * @Mail:         kehr.china@gmail.com
 * @Created Time: Wed 12 Feb 2014 
 * @Copyright:    GPL 2.0 applies
 * @Description:  实现二叉树的基本操作,C++实现。广度优先搜索使用STL队列实现
 *
 *  1. CreateBiTree(BiTree &T) 按先序次序输入二叉树中节点的值,空格字符表示空树 最终创建二叉树
 *  2. PreOrderTraverse(BiTree T) 先序遍历树,输出节点中的字符
 *  3. InOrderTraverse(BiTree T) 中序遍历二叉树,输出节点中的字符
 *  4. PostOrderTraverse(BiTree T) 后序遍历儿二叉树,输出节点中的字符
 *  5. LevelOrderTraverse(BiTree T) 层序遍历二叉树,输出节点中的值 
 *  6. Data Structure:
 *  typedef struct BiTNode
 *  { 
 *      char item; 
 *      struct BiTNode lChild,rChild; 
 *  }BiTNode,*BiTree;
 *      
 *************************************************************************/
#include <stdlib.h>
#include <iostream>
#include <queue>

using namespace std;

//定义树节点
typedef struct BiTNode
{
    char item;
    struct BiTNode *lChild,*rChild;
}BiTNode,*BiTree;

void CreateBiTree(BiTree &T);           //创建二叉树
void PreOrderTraverse(BiTree T);        //先序遍历
void InOrderTraverse(BiTree T);         //中序遍历
void PostOrderTraverse(BiTree T);       //后序遍历
void LevelOrderTraverse(BiTree T);      //广度优先遍历


int main()
{
    BiTree tree;
    cout << "创建二叉树：";
    CreateBiTree(tree);
    cout << "\n-------------------" << endl;
    
    cout << "先序遍历： ";
    PreOrderTraverse(tree);
    cout << "\n-------------------" << endl;
    
    cout << "中序遍历： ";
    InOrderTraverse(tree);
    cout << "\n-------------------" << endl;
    
    cout << "后序遍历： ";
    PostOrderTraverse(tree);
    cout << "\n-------------------" << endl;

    cout << "广度优先遍历遍历： ";
    LevelOrderTraverse(tree);
    cout << "\n-------------------" << endl;




    return 0;
}

void CreateBiTree(BiTree &T)
{
    char citem;
    
    cin.get(citem);

    if (' ' == citem)
    {
        cout << "\n该节点为空！" << endl;
        T = NULL;
    }
    else
    {
        if ((T = (BiTree)malloc(sizeof(BiTNode))) == NULL)
        {
            cout << "Memory allocation failure !" << endl;
            exit(1);
        }
        T->item = citem;
        CreateBiTree(T->lChild);
        cout << "\n创建左子树：" << citem << endl;
        
        CreateBiTree(T->rChild);
        cout << "\n创建右子树:" << citem << endl;
    }

}
void PreOrderTraverse(BiTree T)
{

    if(T != NULL )
    {
        cout << T->item << " ";
        PreOrderTraverse(T->lChild); // 遍历左子树
        PreOrderTraverse(T->rChild);// 遍历右子树
    }
}
void InOrderTraverse(BiTree T)
{

    if(T != NULL )
    {
        InOrderTraverse(T->lChild);
        cout << T->item << " ";
        InOrderTraverse(T->rChild);
    }
}
void PostOrderTraverse(BiTree T)
{

    if(T != NULL)
    {
        PostOrderTraverse(T->lChild);
        PostOrderTraverse(T->rChild);
        cout << T->item << " ";
    }
}
void LevelOrderTraverse(BiTree T)
{

    queue<BiTree> nodes;        //使用STL队列实现
    BiTree node;
 
    nodes.push(T);              //存放树根
 
    while (!nodes.empty())
    {
        node = nodes.front();   //获取队首元素节点
        cout << node->item << " ";
     
        nodes.pop();            //删除对首元素节点
        
        if (node->lChild)       //左节点入队
        {
            nodes.push(node->lChild);
        }
     
        if (node->rChild)       //右节点入队
        {
            nodes.push(node->rChild);
        }
     
    }
}
