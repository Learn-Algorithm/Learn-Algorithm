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
    else if (data < node->data)    
    {
        node->lchild = insert_tree(data, node->lchild);
        if (Height(node->lchild) - Height(node->rchild) == 2)   
        {
            if (data < node->lchild->data)
            {
                node = SingleRotateWithLeft(node);
            }
            else
            {
                node = DoubleRotateWithLeft(node);
            }
        }
    }
    else if (data > node->data)    
    {
        node->rchild = insert_tree(data, node->rchild);
        if (Height(node->rchild) - Height(node->lchild) == 2)    
        {
            if (data > node->rchild->data)
            {
                node = SingleRotateWithRight(node);
            }
            else
            {
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

//翻转开始

AVLTree* SingleRotateWithLeft(AVLTree* node)
{
    AVLTree* node1;
    
    node1 = node->lchild;
    node->lchild = node1->rchild;
    node1->rchild = node;
    
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

















