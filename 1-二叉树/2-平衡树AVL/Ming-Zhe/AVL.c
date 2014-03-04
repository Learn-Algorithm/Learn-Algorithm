#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct AVLTree{
    int data;
    int height;
    struct AVL* lchild;
    struct AVL* rchild;
}AVLTree;

AVLTree* SingleRotateWithLeft(AVLTree* node);
AVLTree* SingleRotateWithRight(AVLTree* node);
AVLTree* DoubleRotateWithLeft(AVLTree* node);
AVLTree* DoubleRotateWithRight(AVLTree* node);

int Height(AVLTree* node)
{
    if (NULL == node)
        return -1;
    
    return node->height;
}

int Max(int a, int b)
{
    return (a > b ? a : b);
}

AVLTree* insert_tree(int data,AVLTree* node)
{
    if (NULL == node)
    {
        node = (AVLTree*)malloc(sizeof(AVLTree));
        node->data = data;
        node->height = 0;
        node->lchild = node->rchild = NULL;
    }
    else if (data < node->data)    /*插入到左子树中*/
    {
        node->lchild = insert_tree(data, node->lchild);
        if (Height(node->lchild) - Height(node->rchild) == 2)    /*AVL树不平衡*/
        {
            if (data < node->lchild->data)
            {
                /*插入到了左子树左边, 做单旋转*/
                node = SingleRotateWithLeft(node);
            }
            else
            {
                /*插入到了左子树右边, 做双旋转*/
                node = DoubleRotateWithLeft(node);
            }
        }
    }
    else if (data > node->data)    /*插入到右子树中*/
    {
        node->rchild = insert_tree(data, node->rchild);
        if (Height(node->rchild) - Height(node->lchild) == 2)    /*AVL树不平衡*/
        {
            if (data > node->rchild->data)
            {
                /*插入到了右子树右边, 做单旋转*/
                node = SingleRotateWithRight(node);
            }
            else
            {
                /*插入到了右子树左边, 做双旋转*/
                node = DoubleRotateWithRight(node);
            }
        }
    }
    
    node->height = Max(Height(node->lchild), Height(node->rchild)) + 1;
    
    return node;
}


void print_tree(AVLTree* root)
{
    if (NULL == root)
        return;
    
    int n = 0;
    
    print_tree(root->lchild);
    printf("[%d]Data = %d\n", ++n, root->data);
    print_tree(root->rchild);
}

int find_tree(int data, AVLTree* root)
{
    int k=1;    /*查找次数*/
    if (NULL == root)
    {
        printf("not find %d times\n", k);
        return 0;
    }
    
    if(data == root->data)
    {
        printf("find:%d times\n", k);
        return 1;
    }
    else if(data < root->data)
    {
        ++k;
        return find_tree(data, root->lchild);
    }
    else if(data > root->data)
    {
        ++k;
        return find_tree(data, root->rchild);
    }
}

//翻转开始

AVLTree* SingleRotateWithLeft(AVLTree* node)
{
    AVLTree* node1;
    
    node1 = node->lchild;
    node->lchild = node1->rchild;
    node1->rchild = node;
    
    /*结点的位置变了, 要更新结点的高度值*/
    node->height = Max(Height(node->lchild), Height(node->rchild)) + 1;
    node1->height = Max(Height(node1->lchild), node->height) + 1;
    
    return node1;
}

AVLTree* SingleRotateWithRight(AVLTree* node)
{
    AVLTree* node1;
    
    node1 = node->rchild;
    node->rchild = node1->lchild;
    node1->lchild = node;
    
    /*结点的位置变了, 要更新结点的高度值*/
    node->nHeight = Max(Height(node->lchild), Height(node->rchild)) + 1;
    node1->nHeight = Max(Height(node1->rchild), node->height) + 1;
    
    return node1;
}

AVLTree* DoubleRotateWithLeft(AVLTree* node)
{
    node->lchild = SingleRotateWithRight(node->lchild);
    
    return SingleRotateWithLeft(node);
}

AVLTree* DoubleRotateWithRight(AVLTree* node)
{
    node->rchild = SingleRotateWithLeft(node->rchild);
    
    return SingleRotateWithRight(node);
}


int main()
{
    int i,j;
    AVLTree* root = NULL;
    
    srand((int)time(NULL));
    
    for (i = 0; i < 10; ++i)
    {
        j = rand();
        printf("%d\n", j);
        root = Insert(j, root);
    }
    
    PrintTree(root);
    
    return 0;
}

















