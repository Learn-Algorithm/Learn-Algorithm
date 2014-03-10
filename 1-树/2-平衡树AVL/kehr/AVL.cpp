/*************************************************************************
 * @File Name:    AVL.cpp
 * @Author:       kehr
 * @Mail:         kehr.china@gmail.com
 * @Created Time: Thu 27 Feb 2014 05:35:55 PM CST
 * @Copyright:    GPL 2.0 applies
 * @Description:  「第一期」第三题：平衡二叉树（AVL）                   
 ************************************************************************
 * Note:
 *
 * 这一期代码做的很纠结。几乎看完了所有人的代码（类实现的除外 d(╯﹏╰)b）,
 * 只有「代码家」的实现让我看的最清楚，也表达了我最想实现的东西。这里代码
 * 参考「代码家」的代码做的。
 *
 */

#include <stdlib.h>
#include <stdio.h>

typedef int KEY_TYPE;
typedef struct AVL{
    KEY_TYPE key;
    int height;
    struct AVL* lchild;
    struct AVL* rchild;
}AVLNode,*AVLTree;

void RR_Rotate(AVLTree &T);                     // 右右，左旋转
void LL_Rotate(AVLTree &T);                     // 左左，右旋转
void LR_Rotate(AVLTree &T);                     // 左右，先右旋转，再左旋转
void RL_Rotate(AVLTree &T);                     // 右左，先左旋转，再右旋转

void InOrder(AVL* T);                           // 中序遍历
void Create(AVLTree &T);                        // 创建AVL
void delete_node(AVLTree &T);                   // 删除节点
void Delete(AVLTree &T, KEY_TYPE key);          // 删除节点
void Insert(AVLTree &root, KEY_TYPE key);       // 插入节点

int getMax(int a, int b);                       // 获取最大值
int getHeight(AVLTree T);                       // 获取树高

int main (void)
{
    AVLTree T = NULL;

    printf("\n创建AVL树....\n\n");
    Create(T);

    printf ("\n中序遍历结果：");
    InOrder(T);

    while (true)
    {
        KEY_TYPE key;
        char flag;

        printf ("\n\n请输入要删除的节点：");
        scanf ("%d",&key);
        Delete (T,key);
        
        printf ("\n中序遍历结果：");
        InOrder(T);

        getchar();
        printf ("\n\n需要插入节点么？(y/n):");
        scanf ("%c",&flag);
        if ('y' == flag || 'Y' == flag)
        {
            printf ("\n请输入插入的节点:");
            scanf ("%d",&key);
            Insert(T,key);
        }

        printf ("\n中序遍历结果：");
        InOrder(T);
    }
    return 0;
}

int getMax(int a, int b)
{
    return (a>b?a:b);
}

int getHeight(AVLTree T)
{
    return (NULL == T?-1:T->height);
}

void Create(AVLTree &T)
{
    KEY_TYPE key;
 
    printf("Please enter your node (end with EOF):");
 
    while (scanf ("%d",&key) != EOF)
    {
        Insert (T,key);
    }
}

void Delete(AVLTree &T, KEY_TYPE key)
{
 
    if (NULL == T)
    {
        printf("树为空！\n");
        return;
    }
    else
    {
        if (key == T->key)
        {
            delete_node(T);
        }
        else if (key < T->key)
        {
            Delete(T->lchild, key);
        }
        else
        {
            Delete(T->rchild,key);
        }
    }

    if(NULL == T)
    {
        printf ("节点已删除！\n");
        return;
    }

   T->height = getMax(getHeight(T->lchild),getHeight(T->rchild)) + 1;
    
   if(getHeight(T->lchild) - getHeight(T->rchild) == 2)                               // 左高
    {
        if (getHeight(T->lchild->lchild) > getHeight(T->lchild->rchild))              // 判断左子树属于，左左类型，还是左右类型
        {
            LL_Rotate(T);
        }
        else
        {
            LR_Rotate(T);
        }
    }
    else if(getHeight(T->lchild) - getHeight(T->rchild) == -2)                        // 右高
    {
        if (getHeight(T->rchild->rchild) > getHeight(T->rchild->lchild))              // 判断右子树属于，右右类型，还是右左类型
        {
            RR_Rotate(T);
        }
        else
        {
            RL_Rotate(T);
        }
    }
}

void delete_node(AVLTree &T)
{
    if(NULL == T->lchild)            // 左子树为空，右子树上升
    {
        AVLTree q = T;
        T = T->rchild;
        free(q);
    }
    else if(NULL == T->rchild)      // 右子树为空则，左子树上升
    {
        AVLTree q = T;
        T = T->lchild;
        free(q);
    }
    else                            // 左右子树均不空
    {
        AVLTree temp = T;
        AVLTree f = T->rchild;      // 定位到待删节点的右子树
        AVLTree s = T->lchild;      // 定位到待删节点的左子树

        T = T->rchild;              // 待删除的节点的右节点上升

        while(f->lchild)            // 查找右子树的最小节点
        {
            f = f->lchild;
        }

        f -> lchild = s;            // 将待删节点的左子树接到其右子树的最小节点上

        free(temp);                 // 删除待删节点
    }
}
void Insert(AVLTree &T, KEY_TYPE key)
{

    if (NULL == T)                                // 如果树为空，则创建根节点 
    {
        if (NULL == (T = (AVLTree)malloc(sizeof(AVL))))
        {
            printf ("无法创建节点，程序退出。\n");
            exit(1);
        }
        T->key = key;
        T->lchild = NULL;
        T->rchild = NULL;
        T->height = 0;
    }
    else
    {
        if( key > T->key)
        {
            Insert (T->rchild, key);
        }
        else if (key < T->key)
        {
            Insert (T->lchild, key);
        }
        else
        {
            printf ("节点已存在，无需重复插入！\n");
            return ;
        }

        T->height = getMax (getHeight(T->lchild), getHeight(T->rchild)) + 1;        // 调整树高

        //--------------------------------------------------------------------------回溯调整树平衡

        if(getHeight(T->lchild) - getHeight(T->rchild) == 2)                        // 左高
        {
            if (key < T->lchild->key)
            {
                LL_Rotate(T);
            }
            else
            {
                LR_Rotate(T);
            }
        }
        else if(getHeight(T->lchild) - getHeight(T->rchild) == -2)                 // 右高
        {
            if (key < T->rchild->key)
            {
                RL_Rotate(T);
            }
            else
            {
                RR_Rotate(T);
            }
        }
    }
}

void InOrder(AVL* T)
{
    if (NULL != T)
    {
        InOrder(T->lchild);
        printf("%d ",T->key);
        InOrder(T->rchild);
    }
}

void RR_Rotate(AVLTree &T)
{
    AVLTree temp;

    temp = T->rchild;
    T->rchild = temp->lchild;
    temp->lchild = T;

    T->height = getMax(getHeight(T->lchild), getHeight(T->rchild)) + 1;
    temp->height = getMax(getHeight(temp->lchild), getHeight(temp->rchild)) + 1;

    T = temp;                // 调整树根
    printf("右子树增高，左旋转\n");
}

void LL_Rotate(AVLTree &T)
{
    AVLTree temp;

    temp = T->lchild;
    T->lchild = temp->rchild;
    temp->rchild = T;

    T->height = getMax(getHeight(T->lchild), getHeight(T->rchild)) + 1;
    temp->height = getMax(getHeight(temp->lchild), getHeight(temp->rchild)) + 1;

    T = temp;

    printf("左子树增高，右旋转\n");
}

void LR_Rotate(AVLTree &T)
{
    RR_Rotate(T->lchild);   // 调整左子树，转换成为LL_Rotate的情况
    LL_Rotate(T);
}

void RL_Rotate(AVLTree &T)
{
    LL_Rotate(T->rchild);  // 调整右子树，转换成为RR_Rotate的情况
    RR_Rotate(T);
}
