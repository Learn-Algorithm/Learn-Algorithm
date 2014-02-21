/*************************************************************************
 * @File Name:    bst.cpp
 * @Author:       kehr
 * @Mail:         kehr.china@gmail.com
 * @Created Time: Wed 19 Feb 2014 08:28:03 PM CST
 * @Copyrchild:    GPL 2.0 applies
 * @Description:  「第一期」第二题：二叉查找树（BST）
 ************************************************************************
 * @keyStructure:
 *
 * typedef int KEY_TYPE;
 * typedef struct Node{
 *
 *     KEY_TYPE key;
 *         struct Node* lchild;
 *             struct Node* rchild;
 * }Node;
 *
 * @Function:
 *
 * create 创建二叉查找树
 * insert 插入一个新的值到已存在的二叉查找树中
 * search 通过值查找一个节点
 * delete 通过值删除一个节点
 * inOrder 中序遍历该树
 *
 ************************************************************************/
#include <stdlib.h>
#include <iostream>
using namespace std;

typedef int KEY_TYPE;

typedef struct Node{
    KEY_TYPE key;
    struct Node* lchild;
    struct Node* rchild;
}Node,*Tree;

void create_bst(Tree &T);
void insert_bst(Tree &T, KEY_TYPE key);
void search_bst(Tree T, KEY_TYPE key);
void delete_bst(Tree &T, KEY_TYPE key);
void delete_node(Tree &T);
void in_order(Tree T);

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

void in_order(Tree T)
{
    if (T != NULL)
    {
        in_order(T->lchild);
        cout<<T->key<<" "  ;
        in_order(T->rchild);

    }
}
