//
//  main.c
//  BST  二叉树查找
//
//  Created by Willard Lin on 14-2-17.
//  Copyright (c) 2014年 Willard Lin. All rights reserved.
//



#include <stdio.h>
#include <malloc/malloc.h>
#include <stdlib.h>
/*
 create 创建二叉查找树
 insert 插入一个新的值到已存在的二叉查找树中
 search 通过值查找一个节点
 delete 通过值删除一个节点
 inOrder 中序遍历该树
 */

#define ARRAY_MAX 16

typedef int KEY_TYPE;
typedef struct Node{
    KEY_TYPE key;
    struct Node* lchild;
    struct Node* rchild;
}Node;
Node *initNode();
Node *create(int *array,int count);
void insertNode(Node *node, int data);
Node *search(Node *node,int data);
int  delete(Node *node,int data);
void inOrder(Node *node);
int main(int argc, const char * argv[])
{
    int array[ARRAY_MAX] = {4,3,5,1,2,6,7,8,20,90,7,5,31,54,50,60};
    int count = sizeof(array) / sizeof(int);
    
    //创建二叉树
    Node *tree = create(array,count);
    inOrder(tree);
    printf("\n");
    //添加数据
    insertNode(tree, 79);
    insertNode(tree, 1001);
    
    
    Node *searchNode = search(tree,5);
    printf("searchNode:%p\n",searchNode);
    Node *searchNode2 = search(tree,200);
    printf("searchNode:%p\n",searchNode2);
    inOrder(tree);
    printf("\n");
    int deleteSucess = delete(tree,1001);
    printf("deleteSucess:%d\n",deleteSucess);
    
    inOrder(tree);
    printf("\n");
    return 0;
}

//创建二叉树
Node *create(int *array,int count)
{
    Node *node = initNode();
    int i = 0;
    for (i = 0; i<count; i++)
    {
        insertNode(node,array[i]);
    }
    return node;
}

//初始化二叉树
Node *initNode()
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

//插入数据
static int count = 0;
void insertNode(Node *node, int data)
{
    if (node != NULL && count == 0)
    {
        node->key = data;
        count++;
        return;
    }
    if (node != NULL && data < node->key && node->lchild == NULL)
    {
        Node *p = (Node *)malloc(sizeof(Node));
        p->key = data;
        p->lchild = NULL;
        p->rchild = NULL;
        node->lchild = p;
        return;
    }
    if (node != NULL && node->key <= data && node->rchild == NULL)
    {
        Node *p = (Node *)malloc(sizeof(Node));
        p->key = data;
        p->lchild = NULL;
        p->rchild = NULL;
        node->rchild = p;
        return;
    }
    if(data < node->key)
    {
        insertNode(node->lchild, data);
    }
    else
    {
        insertNode(node->rchild, data);
    }
}

//查找结点
Node *search(Node *node,int data)
{
    Node *p = node;
    if (p == NULL)
    {
        return NULL;
    }
    else if(p->key < data)
    {
        return p = search(p->rchild,data);
    }
    else if(p->key > data)
    {
        return p = search(p->lchild,data);
    }
    else if(p->key == data)
    {
        return node;
    }
    else
    {
        return NULL;
    }
}

int delete(Node *node,int data)
{
    Node *p = search(node, data);
    if (p == NULL)
    {
        return 0;
    }
    else if (p->key == data && p->lchild != NULL && p->rchild != NULL)
    {
        node = p->lchild;
        node->rchild = p->rchild;
        free(p);
        return 1;
    }
    else if(p->key == data && p->lchild != NULL && p->rchild == NULL)
    {
        node = p->lchild;
        free(p);
        return 1;
    }
    else if(p->key == data && p->lchild == NULL && p->rchild != NULL)
    {
        node = p->rchild;
        free(p);
        return 1;
    }
    else if(p->key == data && p->lchild == NULL && p->rchild == NULL)
    {
        node = p->lchild;
        node = p->rchild;
        p = NULL;
        free(p);
        return 1;
    }
    return 0;
}

Node *findMax(Node* T)
{
    if(T->rchild == NULL)
        return T;
    else
        return findMax(T->rchild);
}
Node *findMin(Node* T)
{
    if(T->lchild == NULL)
        return T;
    else
        return findMin(T->lchild);
}

void inOrder(Node *node)
{
    if (node != NULL)
    {
        inOrder(node->lchild);
        printf("%6d",node->key);
        inOrder(node->rchild);

    }
}
