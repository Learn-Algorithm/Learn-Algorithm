//
//  main.cpp
//  AVLTree
//
//  Created by Ming-Zhe on 14-3-2.
//  Copyright (c) 2014年 Ming-Zhe. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct AVL{
    int data;
    int height;
    struct AVL* lchild;
    struct AVL* rchild;
}AVL,*AVLTree;

void SingleRotateWithLeft(AVLTree& node);
void SingleRotateWithRight(AVLTree& node);
void DoubleRotateWithLeft(AVLTree& node);
void DoubleRotateWithRight(AVLTree& node);

int Height(const AVLTree& node)
{
    if (NULL == node)
        return -1;
    
    return node->height;
}

int Max(int a, int b)
{
    return (a > b ? a : b);
}

void insert_tree(int data,AVLTree &node)
{
    if (node == NULL)
    {
        node = (AVL*)malloc(sizeof(AVL));
        node->data = data;
        node->height = 0;
        node->lchild = node->rchild = NULL;
        printf("test01\n");
        return;
    }
    else if (data < node->data)
    {
        insert_tree(data, node->lchild);
    }
    else if (data > node->data)
    {
        insert_tree(data, node->rchild);
    }
    
    node->height = Max(Height(node->lchild), Height(node->rchild)) + 1;
    
    if (Height(node->lchild) - Height(node->rchild) == 2)
    {
        if (node->lchild->data > data)
        {
            SingleRotateWithLeft(node);
        }
        else
        {
            DoubleRotateWithLeft(node);
        }
    }
    else if (Height(node->rchild) - Height(node->lchild) == 2)
    {
        if (node->rchild->data < data)
        {
            SingleRotateWithRight(node);
        }
        else
        {
            DoubleRotateWithRight(node);
        }
    }
}

void delete_node(AVLTree& root, int data)
{
    if (root == NULL) {
        printf("NULL to delete\n");
        return;
    }
    if (root->data == data) {
        AVLTree node = root;
        
        printf("begin to delete\n");
        if (root->lchild == NULL && root->rchild == NULL)
        {
            root = NULL;
        }
        else if(root->rchild != NULL && root->lchild != NULL)
        {
            AVLTree loop = root->rchild;
            while (loop->lchild != NULL) {
                loop = loop->lchild;
            }
            root->data = loop->data;
            delete_node(root->rchild, loop->data);
        }
        else
        {
            if (root->lchild == NULL) {
                root = root->rchild;
            }
            else
            {
                root = root->lchild;
            }
        }
        free(node);
    }
    else if (root->data < data)
    {
        delete_node(root->rchild, data);
    }
    else
    {
        delete_node(root->lchild, data);
    }
    
    if (root == NULL) {
        return;
    }
    
    root->height = Max(Height(root->lchild), Height(root->rchild)) + 1;
    
    if (Height(root->lchild) - Height(root->rchild) == 2)
    {
        if (Height(root->lchild->lchild) > Height(root->lchild->rchild))
        {
            SingleRotateWithLeft(root);
        }
        else
        {
            DoubleRotateWithLeft(root);
        }
    }
    if (Height(root->rchild) - Height(root->lchild) == 2)
    {
        if (Height(root->rchild->rchild) > Height(root->rchild->lchild))
        {
            SingleRotateWithRight(root);
        }
        else
        {
            DoubleRotateWithRight(root);
        }
    }
    
}


void print_tree(AVLTree root)
{
    if (root != NULL)
    {
        print_tree(root->lchild);
        printf("Data = %d\n",root->data);
        print_tree(root->rchild);
    }
    
}

//翻转开始

void SingleRotateWithLeft(AVLTree& node)
{
    AVLTree node1;
    
    node1 = node->lchild;
    node->lchild = node1->rchild;
    node1->rchild = node;
    
    node->height = Max(Height(node->lchild), Height(node->rchild)) + 1;
    node1->height = Max(Height(node1->lchild), node->height) + 1;
    
    node = node1;
    printf("LL\n");
}

void SingleRotateWithRight(AVLTree& node)
{
    AVLTree node1;
    
    node1 = node->rchild;
    node->rchild = node1->lchild;
    node1->lchild = node;
    
    node->height = Max(Height(node->lchild), Height(node->rchild)) + 1;
    node1->height = Max(Height(node1->rchild), node->height) + 1;
    
    node = node1;
    printf("RR\n");
}

void DoubleRotateWithLeft(AVLTree& node)
{
    SingleRotateWithRight(node->lchild);
    SingleRotateWithLeft(node);
}

void DoubleRotateWithRight(AVLTree& node)
{
    SingleRotateWithLeft(node->rchild);
    SingleRotateWithRight(node);
}


int main()
{
    AVLTree root = NULL;
    
    insert_tree(2, root);
    insert_tree(4, root);
    insert_tree(6, root);
    insert_tree(5, root);
    printf("insert over\n");
    print_tree(root);
    
    delete_node(root, 5);
    
    printf("after\n");
    print_tree(root);
    
    return 0;
}



















